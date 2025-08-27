#include "AuthRoute.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
//#include <pqxx/pqxx>
#undef min
#undef max
#include <jwt-cpp/jwt.h>
#include "../managers/UserManager.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "../managers/PQManager.h"
#include "CachedTable.h"

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
        .set_payload_claim("auth_type", picojson::value("username"))
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

std::string generateGuestUsername(size_t length = 20) {
    const std::string charset =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::random_device rd;  // Non-deterministic random source
    std::mt19937 gen(rd()); // Mersenne Twister RNG
    std::uniform_int_distribution<> dist(0, charset.size() - 1);

    std::string username;
    username.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        username += charset[dist(gen)];
    }

    return username;
}

std::string generateRandomPlayerName(size_t suffixLength = 6) {
    const std::string charset =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, charset.size() - 1);

    std::string suffix;
    suffix.reserve(suffixLength);

    for (size_t i = 0; i < suffixLength; ++i) {
        suffix += charset[dist(gen)];
    }

    return "Player-" + suffix;
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::SignUpGuest()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        std::string userOS = "";
        rapidjson::Document document;
        if (req.body.size() > 0) 
        {
            document.Parse(req.body.c_str());
            if (document.HasMember("userOS")) userOS = document["userOS"].GetString();
        }
        std::string username = generateGuestUsername();
        std::string name = generateRandomPlayerName();
        int userId = UserManager::Get()->CreateGuestUser(username, name, userOS);

        std::string token = jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_payload_claim("id", picojson::value(int64_t(userId)))
            .set_payload_claim("auth_type", picojson::value("username"))
            .sign(jwt::algorithm::hs256{ "secret" });

        res.status = 200;
        res.set_content(token, "text/plain");
        return;
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

        std::string token = jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_payload_claim("id", picojson::value(int64_t(userId)))
            .set_payload_claim("auth_type", picojson::value("username"))
            .sign(jwt::algorithm::hs256{ "secret" });

        res.status = 200;
        res.set_content(token, "text/plain");
        return;
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

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::LinkGoogleWithEmail()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string email = document["email"].GetString();
        std::string name = document["name"].GetString();

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int guestUserId = decoded.get_payload_claim("id").as_int();

        int googleUserId = -1;
        DBUser* pUser = UserManager::Get()->GetUserByEmail(email);
        int numActions = 0;
        int numGoogleActions = 0;
        if (pUser)
        {
            PGconn* pConn = ConnectionPool::Get()->getConnection();
            googleUserId = pUser->Id;
            std::string sql =
                "SELECT SUM(count) AS total FROM ("
                "SELECT COUNT(*) AS count FROM predicts WHERE user_id = " + std::to_string(guestUserId) +
                " UNION ALL "
                "SELECT COUNT(*) FROM bets WHERE user_id = " + std::to_string(guestUserId) +
                ") AS all_counts;";

            PGresult* sqlRes = PQexec(pConn, sql.c_str());
            numActions = atoi(PQgetvalue(sqlRes, 0, 0));
            PQclear(sqlRes);

            sql =
                "SELECT SUM(count) AS total FROM ("
                "SELECT COUNT(*) AS count FROM predicts WHERE user_id = " + std::to_string(googleUserId) + " UNION ALL "
                "SELECT COUNT(*) FROM bets WHERE user_id = " + std::to_string(googleUserId) + " UNION ALL "
                "SELECT COUNT(*) FROM predicts_24_25 WHERE user_id = " + std::to_string(googleUserId) +
                ") AS all_counts;";

            sqlRes = PQexec(pConn, sql.c_str());
            numGoogleActions = atoi(PQgetvalue(sqlRes, 0, 0));
            PQclear(sqlRes);
            ConnectionPool::Get()->releaseConnection(pConn);

            delete pUser;
            if (numActions > 0 && numGoogleActions > 0) 
            {
                res.status = 403;
                res.set_content("", "text/plain");
                return;
            }
        }
      
        int userId = UserManager::Get()->LinkGuestUserGoogle(guestUserId, googleUserId, email, name, numActions, numGoogleActions);
       
        if (userId < 0)
        {
            res.status = 403;
            res.set_content("Error", "text/plain");
            return;
        }
        
        token = jwt::create()
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

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::LinkUserWithUsername()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string username = document["username"].GetString();
        std::string name = document["name"].GetString();
        std::string password = document["password"].GetString();

        std::string token = req.get_header_value("Authentication");
        auto decoded = jwt::decode(token);
        int guestUserId = decoded.get_payload_claim("id").as_int();

        DBUser* pUser = UserManager::Get()->GetUser(username);
        if (pUser)
        {
            delete pUser;
            res.status = 403;
            res.set_content("", "text/plain");
            return;
        }

        int userId = UserManager::Get()->LinkGuestUserUsername(guestUserId, username, name, password);

        if (userId < 0)
        {
            res.status = 403;
            res.set_content("Error", "text/plain");
            return;
        }

        token = jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_payload_claim("id", picojson::value(int64_t(userId)))
            .set_payload_claim("auth_type", picojson::value("username"))
            .sign(jwt::algorithm::hs256{ "secret" });

        res.status = 200;
        res.set_content(token, "text/plain");
        return;

    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::SignInWithTelegramBot()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        std::string tgUsername = document["tg_username"].GetString();
        long long tgId = document["tg_id"].GetFloat();
        std::string name = document["name"].GetString();

        int userId;
        DBUser* pUser = UserManager::Get()->GetUserByTelegramId(tgId);
        if (pUser)
        {
            if (pUser->TelegramCode == 0) 
            {
                UserManager::Get()->CreateTelegramUserCode(pUser->Id);
            }

            userId = pUser->Id;
            delete pUser;
        }
        else
        {
            userId = UserManager::Get()->CreateTelegramUser(tgUsername, tgId, name);
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
            .set_payload_claim("auth_type", picojson::value("telegram"))
            .sign(jwt::algorithm::hs256{ "secret" });

        res.status = 200;
        res.set_content(token, "text/plain");
        return;

    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::SignInWithTelegramCode()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        rapidjson::Document document;
        document.Parse(req.body.c_str());

        int tgCode = document["tg_code"].GetInt();
        DBUser* pUser = UserManager::Get()->GetUserByTelegramCode(tgCode);
        if (!pUser)
        {
            res.status = 403;
            res.set_content("Error", "text/plain");
            return;
        }
        int userId = pUser->Id;

        std::string token = jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_payload_claim("id", picojson::value(int64_t(userId)))
            .set_payload_claim("auth_type", picojson::value("telegram_code"))
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
        std::string authType = decoded.get_payload_claim("auth_type").as_string();

        std::string sql = "SELECT id, name, avatar, points, email, league, tg_code, username, balance, is_guest FROM users WHERE id = " + std::to_string(userId) + ";";
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
        if (!nrows) 
        {
            PQclear(ret);
            res.status = 500;  // Internal Server Error
            ConnectionPool::Get()->releaseConnection(pg);
            return;
        }
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        char* temp = (char*)calloc(4096, sizeof(char));
        int league = -1;
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

            league = atoi(PQgetvalue(ret, i, 5));
            document.AddMember("league", league, allocator);

            v.SetString(authType.c_str(), authType.size(), allocator);
            document.AddMember("authType", v, allocator);

            if (authType == "telegram") 
            {
                int code = atoi(PQgetvalue(ret, i, 6));
                document.AddMember("tgCode", code, allocator);
            }

            strcpy(temp, PQgetvalue(ret, i, 7));
            std::string username = temp;
            v.SetString(username.c_str(), username.size(), allocator);
            document.AddMember("username", v, allocator);

            float balance = atof(PQgetvalue(ret, i, 8));
            document.AddMember("balance", balance, allocator);

            int isGuest = atof(PQgetvalue(ret, i, 9));
            document.AddMember("isGuest", isGuest, allocator);
        }

        int pos = CachedTable::Get()->GetPosition(userId, league);
        document.AddMember("position", pos, allocator);
        int bbpos = CachedTable::Get()->GetBeatBetPosition(userId);
        document.AddMember("beatBetPosition", bbpos, allocator);
        free(temp);

        {
            std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + std::to_string(userId) + ";";
            PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

            if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                PQclear(awardsRes);
            }
            else
            {
                int awardCount = PQntuples(awardsRes);
                rapidjson::Value awards(rapidjson::kArrayType);

                for (int j = 0; j < awardCount; ++j)
                {
                    rapidjson::Value awardObj(rapidjson::kObjectType);

                    int place = atoi(PQgetvalue(awardsRes, j, 0));
                    char* season = PQgetvalue(awardsRes, j, 1);
                    int league = atoi(PQgetvalue(awardsRes, j, 2));

                    awardObj.AddMember("place", place, allocator);

                    rapidjson::Value seasonVal;
                    seasonVal.SetString(season, allocator);
                    awardObj.AddMember("season", seasonVal, allocator);
                    awardObj.AddMember("league", league, allocator);

                    awards.PushBack(awardObj, allocator);
                }

                document.AddMember("awards", awards, allocator);
                PQclear(awardsRes);
            }

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

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::GetUser()
{
    return [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        auto userId = req.get_param_value("user_id");


        std::string sql = "SELECT id, name, avatar, points, league, balance FROM users WHERE id = " + (userId) + ";";
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
        int league = -1;
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

            league = atoi(PQgetvalue(ret, i, 4));
            document.AddMember("league", league, allocator);

            float balance = atof(PQgetvalue(ret, i, 5));
            document.AddMember("balance", balance, allocator);
        }

        int pos = CachedTable::Get()->GetPosition(atoi(userId.c_str()), league);
        document.AddMember("position", pos, allocator);

        {
            std::string awardsQuery = "SELECT place, season, league FROM awards WHERE user_id = " + userId + ";";
            PGresult* awardsRes = PQexec(pg, awardsQuery.c_str());

            if (PQresultStatus(awardsRes) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "Failed to fetch awards: %s", PQerrorMessage(pg));
                PQclear(awardsRes);
            }
            else
            {
                int awardCount = PQntuples(awardsRes);
                rapidjson::Value awards(rapidjson::kArrayType);

                for (int j = 0; j < awardCount; ++j)
                {
                    rapidjson::Value awardObj(rapidjson::kObjectType);

                    int place = atoi(PQgetvalue(awardsRes, j, 0));
                    char* season = PQgetvalue(awardsRes, j, 1);
                    int league = atoi(PQgetvalue(awardsRes, j, 2));

                    awardObj.AddMember("place", place, allocator);

                    rapidjson::Value seasonVal;
                    seasonVal.SetString(season, allocator);
                    awardObj.AddMember("season", seasonVal, allocator);
                    awardObj.AddMember("league", league, allocator);

                    awards.PushBack(awardObj, allocator);
                }

                document.AddMember("awards", awards, allocator);
                PQclear(awardsRes);
            }

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

        auto userId = req.get_param_value("user_id");
        auto leagueId = req.get_param_value("league_id");

        // Start constructing the SQL query
        std::string sql = "SELECT u.points, "
            "COUNT(CASE WHEN p.status <> 0 THEN 1 END) AS total_predictions, "
            "COUNT(CASE WHEN p.status = 1 OR p.status = 2 OR p.status = 5 THEN 1 END) AS winner_predicted, "
            "COUNT(CASE WHEN p.status = 2 THEN 1 END) AS score_predicted, "
            "COUNT(CASE WHEN p.status = 3 THEN 1 END) AS failed "
            "FROM users u "
            "LEFT JOIN predicts p ON p.user_id = u.id "
            "LEFT JOIN matches m ON p.match_id = m.id "
            "WHERE u.id = " + (userId);

        // If leagueId is provided and is not -1, add it to the query
        if (!leagueId.empty() && leagueId != "-1") {
            sql += " AND m.league = " + leagueId;
        }

        // Finish the query with the GROUP BY clause
        sql += " GROUP BY u.points;";

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

#include "../anvir/avir.h"
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

    int nw = 400;
    int nh = int(400.f * h / w);
    unsigned char* dd = new unsigned char[nw* nh * c];
    avir::CImageResizer<> ImageResizer( 8 );
    ImageResizer.resizeImage( d, w, h, 0, dd, nw, nh, c, 0 );

 //   WebPSave(d, w, h, c, fullPath);

    stbi_write_jpg(fullPath.c_str(), nw, nh, c, dd, 100);
    stbi_image_free(d);
    delete[] dd;
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
        std::string rname = generateRandomFilename();
        std::string filename = userDir + "/" + rname + ".jpg";
        //        std::ofstream ofs(filename, std::ios::binary);
        //        ofs << image_file.content;

        EImageContentType ct = EImageContentType::Jpeg;
        if (image_file.content_type == std::string("image/webp")) ct = EImageContentType::Webp;
        Upload((unsigned char*)image_file.content.c_str(), image_file.content.size(), filename, ct);
            
        std::string dbFilename = std::string("data") + "/users" + "/" + userId + "/" + rname + ".jpg";
        std::string sql = "UPDATE users SET avatar = '" + dbFilename + "' WHERE id = " + userId + ";";
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

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::MeMoveToLeague()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        int userId = -1;
        std::string token = req.get_header_value("Authentication");
        if (token.size())
        {
            auto decoded = jwt::decode(token);
            userId = decoded.get_payload_claim("id").as_int();
        }
        if (userId <= 0) 
        {
            res.status = 500;
            res.set_content("ERROR", "text/plain");
            return;
        }
        
        rapidjson::Document d;
        d.Parse(req.body.c_str());
        if (!d.HasMember("league"))
        {
            res.status = 500;
            res.set_content("ERROR", "text/plain");
            return;
        }
        int league = d["league"].GetInt();
        std::string sql = "UPDATE users SET league = " + std::to_string(league) + " WHERE id = " + std::to_string(userId) + ";";

        PGconn* pg = ConnectionPool::Get()->getConnection();
        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Failed move to league: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            res.set_content("OK", "text/plain");
            return;
        }
            
        ConnectionPool::Get()->releaseConnection(pg);
        res.status = 200;
        res.set_content("OK", "text/plain");
        return;     
    };
}


std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::MeAddFcmToken()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        int userId = -1;
        std::string token = req.get_header_value("Authentication");
        if (token.size())
        {
            auto decoded = jwt::decode(token);
            userId = decoded.get_payload_claim("id").as_int();
        }
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
        if (userId != -1)
        {
            std::string sql = "SELECT COUNT(*) FROM fcm_tokens where user_id = " + std::to_string(userId)
                + " AND token = '" + fcmToken + "';";

            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "SELECT failed: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 200;
                res.set_content("OK", "text/plain");
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
                res.set_content("OK", "text/plain");
                return;
            }
            else
            {
                std::string sql = "SELECT id FROM fcm_tokens where token = '" + (fcmToken)+"';";
                PGresult* ret = PQexec(pg, sql.c_str());
                if (PQresultStatus(ret) != PGRES_TUPLES_OK)
                {
                    fprintf(stderr, "SELECT failed: %s", PQerrorMessage(pg));
                    PQclear(ret);
                    ConnectionPool::Get()->releaseConnection(pg);
                    res.status = 200;
                    res.set_content("OK", "text/plain");
                    return;
                }

                bool tokenExists = PQntuples(ret) > 0;
                if (tokenExists)
                {
                    PQclear(ret);
                    sql = "UPDATE fcm_tokens SET user_id = " + std::to_string(userId) + " WHERE token = '" + fcmToken + "';";
                    ret = PQexec(pg, sql.c_str());
                    if (PQresultStatus(ret) != PGRES_COMMAND_OK)
                    {
                        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(pg));
                        PQclear(ret);
                        ConnectionPool::Get()->releaseConnection(pg);
                        res.status = 200;
                        res.set_content("OK", "text/plain");
                        return;
                    }

                    PQclear(ret);
                    ConnectionPool::Get()->releaseConnection(pg);
                    res.status = 200;
                    res.set_content("OK", "text/plain");
                    return;
                }
            }
        }
        else
        {
            std::string sql = "SELECT id FROM fcm_tokens where token = '" + (fcmToken)+"';";
            PGresult* ret = PQexec(pg, sql.c_str());
            if (PQresultStatus(ret) != PGRES_TUPLES_OK)
            {
                fprintf(stderr, "SELECT failed: %s", PQerrorMessage(pg));
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 200;
                res.set_content("OK", "text/plain");
                return;
            }
            bool exists = PQntuples(ret) > 0;
            if (exists)
            {
                PQclear(ret);
                ConnectionPool::Get()->releaseConnection(pg);
                res.status = 200;
                res.set_content("OK", "text/plain");
                return;
            }
        }

        std::string sql = "INSERT INTO fcm_tokens (user_id, token, os, lang) VALUES (" + std::to_string(userId)
            + ",'" + fcmToken
            + "','" + os
            + "','" + lang
            + "');";

        PGresult* ret = PQexec(pg, sql.c_str());
        if (PQresultStatus(ret) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "Failed to add fcm token: %s", PQerrorMessage(pg));
            PQclear(ret);
            ConnectionPool::Get()->releaseConnection(pg);
            res.status = 500;
            res.set_content("OK", "text/plain");
            return;
        }

        PQclear(ret);
        ConnectionPool::Get()->releaseConnection(pg);

        res.status = 200;
        res.set_content("OK", "text/plain");
    };
}

#include "../managers/PNManager.h"
std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotification() 
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendWeekStartedNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotificationCL()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendCLStartedNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotificationNL()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendNLStartedNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotificationUpdate()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendUpdateNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotificationQuest()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendQuestNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotificationElClasico()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendElClasicoNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotificationSerieA()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendSerieANotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotificationMatch()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendMatchNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotificationPreview()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendPreviewNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendNotificationLeague2()
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendLeague2Notification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserPredictionSendNotification()
{
    return [this](const httplib::Request& req, httplib::Response& res) {

        bool b = PNManager::SendWeekStartedNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}

std::function<void(const httplib::Request&, httplib::Response&)> AuthRoute::UserSendSpecialMatchNotification() 
{
    return [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "*");
        res.set_header("Access-Control-Allow-Headers", "*");

        bool b = PNManager::SendSpecialMatchNotification();
        if (b) res.status = 200;
        else res.status = 500;
        res.status = 200;
    };
}
