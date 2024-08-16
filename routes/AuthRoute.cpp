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

        std::string sql = "SELECT id, name, avatar, points FROM users WHERE id = " + std::to_string(userId) + ";";
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

        std::string sql = "UPDATE users SET name = " + userId + " WHERE id = " + userId + ";";
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