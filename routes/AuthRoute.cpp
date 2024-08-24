#include "AuthRoute.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
//#include <pqxx/pqxx>
#include <jwt-cpp/jwt.h>
#include "../managers/UserManager.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "../managers/PQManager.h"

AuthRoute* AuthRoute::sInstance = nullptr;

AuthRoute* AuthRoute::Get()
{
    if (!sInstance) sInstance = new AuthRoute();
    return sInstance;
}

int sign_in(const std::string& username, const std::string& password, std::string& token)
{
    DBUser* pUser = UserManager::Get()->GetUser(username);
    if (!pUser)
    {
        return 404;
    }


    if (pUser->Password != password) return 403;

    token = jwt::create()
        .set_issuer("auth0")
        .set_type("JWS")
        .set_payload_claim("id", picojson::value(int64_t(pUser->Id)))
        .sign(jwt::algorithm::hs256{"secret"});

    delete pUser;
    return 200;
}


std::function<void(const httplib::Request &, httplib::Response &)> AuthRoute::SignUpVerify()
{
    return [](const httplib::Request& req, httplib::Response& res){
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string phone = document["phone"].GetString();
        DBUser* pUser = UserManager::Get()->GetUser(phone);
        if (pUser)
        {
            delete pUser;
            res.status = 403;
            res.set_content("", "text/plain");
            return;
        }

        bool success = true;//verify_phone_number(std::string("+374") + phone);
        if (success)
          res.status = 200;
        else
          res.status = 400;
        res.set_content("", "text/plain");
    };
}

std::function<void(const httplib::Request &, httplib::Response &)> AuthRoute::ChangePassword()
{
    return [](const httplib::Request& req, httplib::Response& res){
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string phone = document["phone"].GetString();
        std::string password = document["password"].GetString();
        std::string code = document["code"].GetString();
        DBUser* pUser = UserManager::Get()->GetUser(phone);
        if (!pUser)
        {
            res.status = 404;
            res.set_content("", "text/plain");
            return;
        }

        bool success = false;
        if (success) 
        {
          if (UserManager::Get()->ChangePassword(phone, password))
            res.status = 200;
          else 
            res.status = 400;
        }
        else
          res.status = 400;
        res.set_content("", "text/plain");
    };
}

std::function<void(const httplib::Request &, httplib::Response &)> AuthRoute::SignInForgot()
{
    return [](const httplib::Request& req, httplib::Response& res){
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string phone = document["phone"].GetString();
        DBUser* pUser = UserManager::Get()->GetUser(phone);
        if (!pUser)
        {
            res.status = 404;
            res.set_content("", "text/plain");
            return;
        }

        bool success = false;
        if (success)
          res.status = 200;
        else
          res.status = 400;
        res.set_content("", "text/plain");
    };
}

std::function<void(const httplib::Request &, httplib::Response &)> AuthRoute::SignUpV2()
{
     return [](const httplib::Request& req, httplib::Response& res){
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string username = document["username"].GetString();
        std::string pwd = document["password"].GetString();

        DBUser* pUser = UserManager::Get()->GetUser(username);
        if (pUser)
        {
            delete pUser;
            res.status = 403;
            res.set_content("", "text/plain");
            return;
        }

		std::string firstName = document["name"].GetString();
        int userId = UserManager::Get()->CreateUser(username, pwd, firstName);

        std::string token;
        int status = sign_in(username, pwd, token);
		if (!token.size())
		{
            res.status = status;
			return;
		}

        res.status = 200;
        res.set_content(token, "text/plain");
    };
}

std::function<void(const httplib::Request &, httplib::Response &)> AuthRoute::SignIn()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");


        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string username = document["username"].GetString();
        std::string pwd = document["password"].GetString();

        std::string token;
        int status = sign_in(username, pwd, token);
       // res.set_header("Access-Control-Allow-Origin", "*");
		if (!token.size())
		{
      res.status = status;
			return;
		}
        res.status = 200;
        res.set_content(token, "text/plain");
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::SignInGoogleWithEmail()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string email = document["email"].GetString();
        std::string name = document["name"].GetString();

        int userId;
        DBUser* pUser = UserManager::Get()->GetUserByEmail(email);
        if (pUser)
        {
            userId = pUser->Id;
            delete pUser;
        }
        else
        {
            userId = UserManager::Get()->CreateUser(email, name);
            if (userId < 0)
            {
                res.status = 403;
                res.set_content("Error", "text/plain");
                return;
            }
        }

        std::string token = jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_payload_claim("id", picojson::value(int64_t(userId)))
            .set_payload_claim("auth_type", picojson::value("google"))
            .sign(jwt::algorithm::hs256{ "secret" });

        res.status = 200;
        res.set_content(token, "text/plain");
        return;

    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::Me()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();

        std::string sql = "SELECT id, name, avatar, points, email FROM users WHERE id = " + std::to_string(userId) + ";";
        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch leagues: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        char* temp = (char*)calloc(4096, sizeof(char));
        for (int i = 0; i < nrows; ++i)
        {
            int id = atoi(PQgetvalue(ret, i, 0));
            rapidjson::Value v;
            v.SetInt(id);
            document.AddMember("id", v, allocator);

            strcpy(temp, PQgetvalue(ret, i, 1));
            std::string name = temp;
            v.SetString(name.c_str(), name.size(), allocator);
            document.AddMember("name", v, allocator);

            strcpy(temp, PQgetvalue(ret, i, 2));
            std::string ava = temp;
            v.SetString(ava.c_str(), ava.size(), allocator);
            document.AddMember("avatar", v, allocator);

            int points = atoi(PQgetvalue(ret, i, 3));
            document.AddMember("points", points, allocator);

            strcpy(temp, PQgetvalue(ret, i, 4));
            std::string email = temp;
            v.SetString(email.c_str(), email.size(), allocator);
            document.AddMember("email", v, allocator);
        }

        free(temp);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);

    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::GetUser()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        auto userId = req.get_param_value("user_id");


        std::string sql = "SELECT id, name, avatar, points FROM users WHERE id = " + (userId) + ";";
        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch leagues: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        char* temp = (char*)calloc(4096, sizeof(char));
        for (int i = 0; i < nrows; ++i)
        {
            int id = atoi(PQgetvalue(ret, i, 0));
            rapidjson::Value v;
            v.SetInt(id);
            document.AddMember("id", v, allocator);

            strcpy(temp, PQgetvalue(ret, i, 1));
            std::string name = temp;
            v.SetString(name.c_str(), name.size(), allocator);
            document.AddMember("name", v, allocator);

            strcpy(temp, PQgetvalue(ret, i, 2));
            std::string ava = temp;
            v.SetString(ava.c_str(), ava.size(), allocator);
            document.AddMember("avatar", v, allocator);

            int points = atoi(PQgetvalue(ret, i, 3));
            document.AddMember("points", points, allocator);
        }

        free(temp);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::GetStats()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int userId = decoded.get_payload_claim("id").as_int();

        // SQL query to fetch points from users table and aggregated prediction stats excluding pending predictions
        std::string sql = "SELECT u.points, "
            "COUNT(p.status) AS total_predictions, " // Total predictions excluding pending
            "COUNT(CASE WHEN p.status = 1 THEN 1 END) AS winner_predicted, " // Winner predicted
            "COUNT(CASE WHEN p.status = 2 THEN 1 END) AS score_predicted, " // Score predicted
            "COUNT(CASE WHEN p.status = 3 THEN 1 END) AS failed " // Failed predictions
            "FROM users u LEFT JOIN predicts p ON p.user_id = u.id "
            "WHERE u.id = " + std::to_string(userId) + " AND p.status <> 0 "
            "GROUP BY u.points;";

        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch user points and prediction stats: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;  // Internal Server Error
            return;
        }

        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        if (PQntuples(ret) > 0)
        {
            document.AddMember("points", atoi(PQgetvalue(ret, 0, 0)), allocator);
            document.AddMember("total_predictions", atoi(PQgetvalue(ret, 0, 1)), allocator);
            document.AddMember("winner_predicted", atoi(PQgetvalue(ret, 0, 2)), allocator);
            document.AddMember("score_predicted", atoi(PQgetvalue(ret, 0, 3)), allocator);
            document.AddMember("failed", atoi(PQgetvalue(ret, 0, 4)), allocator);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        res.set_content(buffer.GetString(), "application/json");
        res.status = 200;  // OK

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);
    };
}

#define STB_IMAGE_IMPLEMENTATION 1
#define STB_IMAGE_WRITE_IMPLEMENTATION 1
#include "../stlplus/file_system.hpp"
#include "ImageUtils.h"
#include "../stb_image/stb_image_write.h"
#include "../stb_image/stb_image.h"
#include <webp/decode.h>
std::string generateRandomFilename() 
{
    int length = 15;
    // Characters that can be part of the filename
    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    int stringLength = sizeof(alphanum) - 1;
    std::string filename;
    filename.reserve(length);

    // Random number generation
    std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr))); // Seed with the current time
    std::uniform_int_distribution<> distribution(0, stringLength - 1);

    for (int i = 0; i < length; ++i) {
        filename += alphanum[distribution(generator)];
    }

    return filename;
}


void Upload(void* data, int size, std::string fullPath, EImageContentType contentType) {
    int w, h, c;
    unsigned char* d = nullptr;
    if (contentType == EImageContentType::Webp)
    {
        c = 3;
        d = WebPDecodeRGB((const uint8_t*)data, size, &w, &h);
    }
    else
        d = stbi_load_from_memory((unsigned char*)data, size, &w, &h, &c, 0);

    /*int nw = 400;
    int nh = int(400.f * h / w);
    unsigned char* dd = new unsigned char[nw* nh * c];
    avir :: CImageResizer<> ImageResizer( 8 );
    ImageResizer.resizeImage( d, w, h, 0, dd, nw, nh, c, 0 );*/

    WebPSave(d, w, h, c, fullPath);

    // stbi_write_jpg(fullPath.c_str(), nw, nh, c, dd, 100);
    stbi_image_free(d);
    // delete[] dd;
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::MeUploadAvatar()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int uid = decoded.get_payload_claim("id").as_int();
        std::string userId = std::to_string(uid);
        httplib::MultipartFormData image_file = req.get_file_value("image_file");
        if (!image_file.content.size())
        {
            res.status = 200;
            return;
        }

        std::string dataDir = "data";
        // std::string dataDir = "/var/www/data";
        if (!stlplus::folder_exists(dataDir)) stlplus::folder_create(dataDir);
        std::string usersDir = dataDir + "/users";
        if (!stlplus::folder_exists(usersDir)) stlplus::folder_create(usersDir);
        std::string userDir = usersDir + "/" + userId;
        if (!stlplus::folder_exists(userDir)) stlplus::folder_create(userDir);
        //        std::string carDir = userDir + "/" + carId;
        //        if (!stlplus::folder_exists(carDir)) stlplus::folder_create(carDir);
        std::string filename = userDir + "/" + generateRandomFilename() + ".webp";
        //        std::ofstream ofs(filename, std::ios::binary);
        //        ofs << image_file.content;

        EImageContentType ct = EImageContentType::Jpeg;
        if (image_file.content_type == std::string("image/webp")) ct = EImageContentType::Webp;
        Upload((unsigned char*)image_file.content.c_str(), image_file.content.size(), filename, ct);
            
        std::string sql = "UPDATE users SET avatar = '" + filename + "' WHERE id = " + userId + ";";
        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* pgres = PQexec(pg, sql.c_str());
        if (PQresultStatus(pgres) != PGRES_COMMAND_OK)
        {
            char* err = PQerrorMessage(pg);
            fprintf(stderr, "Error: Failed to set user cover: %s", PQerrorMessage(pg));
            PQclear(pgres);

            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }
        PQclear(pgres);

        ConnectionPool::Get()->releaseConnection(pg);

        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::MeSetName()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());
        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int uid = decoded.get_payload_claim("id").as_int();
        std::string userId = std::to_string(uid);

        std::string name = document["name"].GetString();
        PGconn* pg = ConnectionPool::Get()->getConnection();

        std::string sql = "UPDATE users SET name = '" + name + "' WHERE id = " + userId + ";";
        PGresult* pgres = PQexec(pg, sql.c_str());
        if (PQresultStatus(pgres) != PGRES_COMMAND_OK)
        {
            char* err = PQerrorMessage(pg);
            fprintf(stderr, "Error: Failed to set user name: %s", PQerrorMessage(pg));
            PQclear(pgres);

            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }
        PQclear(pgres);

        ConnectionPool::Get()->releaseConnection(pg);      
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::MeDelete()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int uid = decoded.get_payload_claim("id").as_int();
        std::string userId = std::to_string(uid);

        PGconn* pg = ConnectionPool::Get()->getConnection();

        std::string sql = "DELETE FROM users WHERE id = " + userId + ";";
        PGresult* pgres = PQexec(pg, sql.c_str());
        if (PQresultStatus(pgres) != PGRES_COMMAND_OK)
        {
            char* err = PQerrorMessage(pg);
            fprintf(stderr, "Error: Failed to delete user: %s", PQerrorMessage(pg));
            PQclear(pgres);

            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }
        PQclear(pgres);

        sql = "DELETE FROM predicts WHERE user_id = " + userId + ";";
        pgres = PQexec(pg, sql.c_str());
        if (PQresultStatus(pgres) != PGRES_COMMAND_OK)
        {
            char* err = PQerrorMessage(pg);
            fprintf(stderr, "Error: Failed to delete user: %s", PQerrorMessage(pg));
            PQclear(pgres);

            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }
        PQclear(pgres);

        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::MeDeleteAvatar()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int uid = decoded.get_payload_claim("id").as_int();
        std::string userId = std::to_string(uid);
        
        std::string sql = "UPDATE users SET avatar = '' WHERE id = " + userId + ";";
        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* pgres = PQexec(pg, sql.c_str());
        if (PQresultStatus(pgres) != PGRES_COMMAND_OK)
        {
            char* err = PQerrorMessage(pg);
            fprintf(stderr, "Error: Failed to set user cover: %s", PQerrorMessage(pg));
            PQclear(pgres);

            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }
        PQclear(pgres);

        ConnectionPool::Get()->releaseConnection(pg);

        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::MeAddFcmToken()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);

        int userId = decoded.get_payload_claim("id").as_int();

        rapidjson::Document d;
        d.Parse(req.body.c_str());
        if (!d.HasMember("fcm_token") || !d.HasMember("os"))
        {
            res.status = 404;
            res.set_content("ERROR", "text/plain");
            return;
        }

        std::string fcmToken = d["fcm_token"].GetString();
        std::string os = d["os"].GetString();
        std::string lang = d["lang"].GetString();

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT COUNT(*) FROM fcm_tokens where user_id = " + std::to_string(userId)
            + " AND token = '" + fcmToken + "';";

        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "SELECT failed: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 200;
            return;
        }
        char* temp = (char*)calloc(256, sizeof(char));
        strcpy(temp, PQgetvalue(ret, 0, 0));
        bool exists = atoi(temp) > 0;
        PQclear(ret);
        free(temp);
        if (exists)
        {
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 200;
            return;
        }
        
        sql = "INSERT INTO fcm_tokens (user_id, token, os, lang) VALUES (" + std::to_string(userId)
            + ",'" + fcmToken
            + "','" + os
            + "','" + lang
            + "');";
        ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Failed to add fcm token: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            return;
        }

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);

        res.status = 200;
        res.set_content("OK", "text/plain");
    };
}

#include <rapidjson/filereadstream.h>
#include <cpr/cpr.h>
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

std::string createJwtToken() 
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

std::string requestAccessToken(const std::string& jwt_token)
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

bool sendPushNotification(const std::string& access_token, const std::string fcm_token, const std::string& title, const std::string& msg)
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

std::string ReadFile(const std::string& filename) 
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotification() {
    return [this](const httplib::Request& req, httplib::Response& res) {

        PGconn* pg = ConnectionPool::Get()->getConnection();
        std::string sql = "SELECT * FROM fcm_tokens;";
        PGresult* ret = PQexec(pg, sql.c_str());

        if (PQresultStatus(ret) != PGRES_TUPLES_OK)
        {
            fprintf(stderr, "Failed to fetch settings: %s", PQerrorMessage(pg));
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }

        int nrows = PQntuples(ret);
        if (!nrows) 
        {
            ConnectionPool::Get()->releaseConnection(pg);
            PQclear(ret);
            res.status = 200;
            return;
        }
        std::string jwt_token = createJwtToken();
        if (!jwt_token.size()) 
        {
            res.status = 500;
            return;
        }

        std::string access_token = requestAccessToken(jwt_token);
        if (!access_token.size())
        {
            res.status = 500;
            return;
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

            bool ret = sendPushNotification(access_token, token, t, m);
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
        res.status = 200;
    };
}
