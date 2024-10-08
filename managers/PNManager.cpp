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
    if (!pkey) {
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
    try {
        jwt_token = jwt_builder.sign(jwt::algorithm::rs256("", private_key_pem, "", ""));
        // Free the private key
        EVP_PKEY_free(pkey);
        return jwt_token;
    }
    catch (const std::exception& ex) {
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

bool PNManager::SendPushNotification(const std::string& access_token, const std::string fcm_token, const std::string& title, const std::string& msg)
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
    //  message.AddMember("android", android, allocator); // Set Android-specific settings here

      // Add the message object to the root object
    payload.AddMember("message", message, allocator);

    // Serialize the payload to JSON string
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
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
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

        bool ret = PNManager::SendPushNotification(access_token, token, t, m);
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
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
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

        bool ret = PNManager::SendPushNotification(access_token, token, t, m);
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
        return false;
    }

    std::string access_token = PNManager::RequestAccessToken(jwt_token);
    if (!access_token.size())
    {
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

        bool ret = PNManager::SendPushNotification(access_token, token, t, m);
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