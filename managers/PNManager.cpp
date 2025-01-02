#include "PNManager.h"
#include "PQManager.h"

#include <rapidjson/filereadstream.h>
#include <cpr/cpr.h>
#undef min
#undef max
#include <jwt-cpp/jwt.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <cpr/cpr.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include <sstream>

std::string PNManager::CreateJwtToken()
{
    // Load the service account JSON file
    std::string service_account_file = "data/service_account.json";
    std::ifstream ifs(service_account_file);
    if (!ifs.is_open()) {
        return "";
    }

    // Parse the JSON service account file
    rapidjson::Document document;
    std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    document.Parse(json.c_str());
    if (document.HasParseError()) {
        return "";
    }

    // Extract the necessary information
    std::string private_key_pem = document["private_key"].GetString();
    std::string client_email = document["client_email"].GetString();

    // Load the private key
    BIO* bio = BIO_new_mem_buf(private_key_pem.data(), private_key_pem.size());
    if (!bio) {
        return "";
    }

    EVP_PKEY* pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);
    if (!pkey) 
    {
        return "";
    }

    // Generate the JWT
    auto now = std::chrono::system_clock::now();
    auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    auto expiry_seconds = now_seconds + 3600; // 1 hour later

    jwt::builder jwt_builder = jwt::create()
        .set_issuer(client_email)
        .set_audience("https://oauth2.googleapis.com/token")
        .set_issued_at(std::chrono::system_clock::from_time_t(now_seconds))
        .set_expires_at(std::chrono::system_clock::from_time_t(expiry_seconds))
        .set_type("JWT")
        .set_algorithm("RS256")
        .set_payload_claim("scope", jwt::claim(std::string("https://www.googleapis.com/auth/firebase.messaging")));

    std::string jwt_token;
    try 
    {
        jwt_token = jwt_builder.sign(jwt::algorithm::rs256("", private_key_pem, "", ""));
        // Free the private key
        EVP_PKEY_free(pkey);
        return jwt_token;
    }
    catch (const std::exception& ex) 
    {
        fprintf(stderr, "CreateJwtToken ex: %s", ex.what());

        EVP_PKEY_free(pkey);
        return "";
    }
}

std::string PNManager::RequestAccessToken(const std::string& jwt_token)
{
    // Request an access token
    std::string token_url = "https://oauth2.googleapis.com/token";
    auto response = cpr::Post(cpr::Url{ token_url },
        cpr::Payload{ {"grant_type", "urn:ietf:params:oauth:grant-type:jwt-bearer"},
                     {"assertion", jwt_token} },
        cpr::Header{ {"Content-Type", "application/x-www-form-urlencoded"} });

    if (response.status_code != 200) {
        return "";
    }

    // Parse the access token
    rapidjson::Document token_document;
    token_document.Parse(response.text.c_str());
    if (token_document.HasParseError() || !token_document.HasMember("access_token")) {
        return "";
    }

    std::string access_token = token_document["access_token"].GetString();
    return access_token;
}

bool PNManager::SendPushNotification(const std::string& access_token, const std::string fcm_token, const std::string& title, const std::string& msg, const std::string& icon)
{
    // Prepare the notification payload
    std::string notification_url = "https://fcm.googleapis.com/v1/projects/el-torneo-bc127/messages:send";

    // Create the payload
    rapidjson::Document payload(rapidjson::kObjectType);
    auto& allocator = payload.GetAllocator();

    // Create the notification object
    rapidjson::Value notification(rapidjson::kObjectType);
    rapidjson::Value vt;
    vt.SetString(title.c_str(), allocator);
    rapidjson::Value vm;
    vm.SetString(msg.c_str(), allocator);
    notification.AddMember("title", vt, allocator);
    notification.AddMember("body", vm, allocator);
  
    // Create the message object
    rapidjson::Value message(rapidjson::kObjectType);
    rapidjson::Value v;
    v.SetString(fcm_token.c_str(), allocator);
    message.AddMember("token", v, allocator);
    message.AddMember("notification", notification, allocator);

    rapidjson::Value andNote;
    andNote.SetObject();

    rapidjson::Value android;
    android.SetObject();
    std::string ni = icon;
    if (!icon.size()) ni = "ic_notification";
    v.SetString(ni.c_str(), allocator);
    andNote.AddMember("icon", v, allocator);
    v.SetString("#37003C", allocator);
    andNote.AddMember("color", v, allocator);

    android.AddMember("notification", andNote, allocator);
    message.AddMember("android", android, allocator); // Set Android-specific settings here

      // Add the message object to the root object
    payload.AddMember("message", message, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    payload.Accept(writer);

    // Send the notification
    auto notification_response = cpr::Post(cpr::Url{ notification_url },
        cpr::Header{ {"Authorization", "Bearer " + access_token},
                    {"Content-Type", "application/json"} },
        cpr::Body{ buffer.GetString() });

    if (notification_response.status_code == 200)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static std::string ReadFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool PNManager::SendWeekStartedNotification() 
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());    

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch settings: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "week_started_title";
    std::string nMsg = "week_started_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "");
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendCLStartedNotification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch settings: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "cl_started_title";
    std::string nMsg = "cl_started_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

       bool ret = PNManager::SendPushNotification(access_token, token, t, m, "champions_league");
        // break;
       if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendNLStartedNotification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch settings: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "nl_start_title";
    std::string nMsg = "nl_start_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "nations_league");
        // break;
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendUpdateNotification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch fcm_tokens: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        fprintf(stderr, "No fcm_tokens: %s", PQerrorMessage(pg));
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        fprintf(stderr, "Failed to create jwt token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        fprintf(stderr, "Failed to create access token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "update_title";
    std::string nMsg = "update_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "");
        // break;
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendQuestNotification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch settings: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "quest_title";
    std::string nMsg = "quest_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "quest");
        // break;
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendElClasicoNotification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch tokens: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        fprintf(stderr, "No tokens: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        fprintf(stderr, "Failed to create jwt token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        fprintf(stderr, "Failed to create access token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "elclasico_title";
    std::string nMsg = "elclasico_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "laliga");
        // break;
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendSerieANotification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch tokens: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        fprintf(stderr, "No tokens: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        fprintf(stderr, "Failed to create jwt token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        fprintf(stderr, "Failed to create access token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "seriea_title";
    std::string nMsg = "seriea_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "serie_a");
        // break;
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendMatchNotification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch tokens: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        fprintf(stderr, "No tokens: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        fprintf(stderr, "Failed to create jwt token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        fprintf(stderr, "Failed to create access token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "match_title";
    std::string nMsg = "match_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "super_cup_italy");
        // break;
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendPreviewNotification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch tokens: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        fprintf(stderr, "No tokens: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        fprintf(stderr, "Failed to create jwt token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        fprintf(stderr, "Failed to create access token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "beat_bet_title";
    std::string nMsg = "beat_bet_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "");
        // break;
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendLeague2Notification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT fcm_tokens.* FROM fcm_tokens "
        "JOIN users ON fcm_tokens.user_id = users.user_id "
        "WHERE users.points <= 20 AND users.league = 1;";

    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch tokens: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        fprintf(stderr, "No tokens: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        fprintf(stderr, "Failed to create jwt token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        fprintf(stderr, "Failed to create access token: %s", PQerrorMessage(pg));

        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "league2_title";
    std::string nMsg = "league2_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "");
        // break;
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}


#include <cstdlib>
#include <ctime>
int getRandomNumber(int n) {
    return rand() % n;
}
bool PNManager::SendSpecialMatchNotification()
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
    std::string sql = "SELECT sm.*, t1.short_name AS team1_name, t2.short_name AS team2_name "
        "FROM special_matches sm "
        "JOIN matches m ON sm.match_id = m.id "
        "JOIN teams t1 ON m.team1 = t1.id "
        "JOIN teams t2 ON m.team2 = t2.id "
        "WHERE m.match_date > EXTRACT(EPOCH FROM NOW()) * 1000;";

    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch settings: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    srand(static_cast<unsigned int>(time(0)));
    int i = getRandomNumber(nrows);

    int id = atoi(PQgetvalue(ret, i, 0));
    std::string title = PQgetvalue(ret, i, 1);
    std::string stadium = PQgetvalue(ret, i, 2);
    int matchId = atoi(PQgetvalue(ret, i, 3));

    std::string team1Name = PQgetvalue(ret, i, PQfnumber(ret, "team1_name"));  // Get team1 short name
    std::string team2Name = PQgetvalue(ret, i, PQfnumber(ret, "team2_name"));  // Get team2 short name
    PQclear(ret);

    {
        sql = "SELECT * FROM fcm_tokens;";
        ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch settings: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            return false;
        }

        int nrows = PQntuples(ret);
        if (!nrows)
        {
            ConnectionPool::Get()->releaseConnection(pg);
            PQclear(ret);
            return true;
        }
        std::string jwt_token = PNManager::CreateJwtToken();
        if (!jwt_token.size())
        {
            ConnectionPool::Get()->releaseConnection(pg);
            PQclear(ret);
            return false;
        }

        std::string access_token = PNManager::RequestAccessToken(jwt_token);
        if (!access_token.size())
        {
            ConnectionPool::Get()->releaseConnection(pg);
            PQclear(ret);
            return false;
        }

        std::string filename = "data/notifications.json";
        std::string jsonString = ReadFile(filename);
        rapidjson::Document document;
        document.Parse(jsonString.c_str());

        std::string nTitle = "special_match_title";
        std::string nMsg = "special_match_msg";

        char* temp = (char*)calloc(4096, sizeof(char));
        std::vector<int> invalidTokens;
        for (int i = 0; i < nrows; ++i)
        {
            // Handle ID as integer
            int id = atoi(PQgetvalue(ret, i, 0));
            int userId = atoi(PQgetvalue(ret, i, 1));
            strcpy(temp, PQgetvalue(ret, i, 2));
            std::string token = temp;//"cHuMBtqtTFWYbCBmHMlJrs:APA91bGl1--uMCtDCW94jmpy0TsrMGiAmmYEMs1OXnIq-bnk2kCFqsC8KLB0GSgowgT7ZIUc58YOzmhkQbFbK0iqH5cM_wQwJH1FrHfF0tLbtI3LGmIeHzhvX5-vxuZPrLGv741WkV4I";
            strcpy(temp, PQgetvalue(ret, i, 3));
            std::string os = temp;
            strcpy(temp, PQgetvalue(ret, i, 4));
            std::string lang = temp;

            if (userId > 0)
            {
                sql = "SELECT id from predicts where user_id = "
                    + std::to_string(userId) + " and " + "match_id = " + std::to_string(matchId) + ";";
                PGresult* pr = PQexec(pg, sql.c_str());
                int nt = PQntuples(pr);
                if (nt > 0)
                {
                    int np = atoi(PQgetvalue(pr, 0, 0));
                    PQclear(pr);
                    if (np > 0) continue;
                }
               
            }

            std::string t = std::string(document[lang.c_str()][title.c_str()].GetString()) + " " + stadium;
            std::string m = std::string(document[lang.c_str()][nMsg.c_str()].GetString()) + " " + team1Name + " vs " + team2Name;

            bool ret = PNManager::SendPushNotification(access_token, token, t, m, title);
            // break;
            if (!ret) invalidTokens.push_back(id);
        }
        free(temp);
        PQclear(ret);

        if (invalidTokens.size())
        {
            for (auto id : invalidTokens)
            {
                sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
                ret = PQexec(pg, sql.c_str());
                PQclear(ret);
            }
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool PNManager::SendPredictionNotification(int matchId)
{
    PGconn* pg = ConnectionPool::Get()->getConnection();
   // std::string sql = "SELECT * FROM matches WHERE id = " + std::to_string(matchId) + ";";

    std::string sql = "SELECT * FROM fcm_tokens;";
    PGresult* ret = PQexec(pg, sql.c_str());

    if (PQresultStatus(ret) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Failed to fetch settings: %s", PQerrorMessage(pg));
        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    int nrows = PQntuples(ret);
    if (!nrows)
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return true;
    }
    std::string jwt_token = PNManager::CreateJwtToken();
    if (!jwt_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
        ConnectionPool::Get()->releaseConnection(pg);
        PQclear(ret);
        return false;
    }

    std::string filename = "data/notifications.json";
    std::string jsonString = ReadFile(filename);
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    std::string nTitle = "week_started_title";
    std::string nMsg = "week_started_msg";

    char* temp = (char*)calloc(4096, sizeof(char));
    std::vector<int> invalidTokens;
    for (int i = 0; i < nrows; ++i)
    {
        // Handle ID as integer
        int id = atoi(PQgetvalue(ret, i, 0));
        int userId = atoi(PQgetvalue(ret, i, 1));
        strcpy(temp, PQgetvalue(ret, i, 2));
        std::string token = temp;
        strcpy(temp, PQgetvalue(ret, i, 3));
        std::string os = temp;
        strcpy(temp, PQgetvalue(ret, i, 4));
        std::string lang = temp;

        std::string t = document[lang.c_str()][nTitle.c_str()].GetString();
        std::string m = document[lang.c_str()][nMsg.c_str()].GetString();

        bool ret = PNManager::SendPushNotification(access_token, token, t, m, "");
        if (!ret) invalidTokens.push_back(id);
    }
    free(temp);
    PQclear(ret);

    if (invalidTokens.size())
    {
        for (auto id : invalidTokens)
        {
            sql = std::string("delete from fcm_tokens where id = ") + std::to_string(id) + ";";
            ret = PQexec(pg, sql.c_str());
            PQclear(ret);
        }
    }

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}