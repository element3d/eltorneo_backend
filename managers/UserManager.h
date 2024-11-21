#ifndef __USER_MANAGER__
#define __USER_MANAGER__

#include <libpq-fe.h>
//#include <pqxx/pqxx>
#include <string>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <vector>

struct DBUser
{
    int Id;
    std::string Username;
    std::string Email;
    std::string Password;
	std::string Name;
    std::string Avatar;
    std::string TelegramUsername;
    long long TelegramId;

    int Points;

    std::string ToJson(bool addNumGolds = false)
    {
        rapidjson::Document d;
        d.SetObject();
        d.AddMember("id", rapidjson::Value(Id), d.GetAllocator());
        rapidjson::Value p;

        p.SetString(Email.c_str(), d.GetAllocator());
        d.AddMember("email", p, d.GetAllocator());

        p.SetString(Username.c_str(), d.GetAllocator());
        d.AddMember("username", p, d.GetAllocator());

		p.SetString(Name.c_str(), d.GetAllocator());
		d.AddMember("first_name", p, d.GetAllocator());

        p.SetString(Avatar.c_str(), d.GetAllocator());
        d.AddMember("avatar", p, d.GetAllocator());

        d.AddMember("points", Points, d.GetAllocator());

        rapidjson::StringBuffer buffer;
        buffer.Clear();

        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);
        return buffer.GetString();
    }
};



class UserManager
{
public:
    static UserManager* Get();

//	void SetPG(PGconn* pPG);
//    void SetPsql(pqxx::connection* pPsql);
    int CreateUser(const std::string& username, const std::string& password, const std::string& name);
    int CreateUser(const std::string& email, const std::string& name);
    int CreateTelegramUser(const std::string& username, long long tgId, const std::string& name);

    bool MeDelete(int id);
    bool MeHandshake(int id);
    DBUser* GetUser(int id);
    DBUser* GetUserByEmail(const std::string& email);
    DBUser* GetUserByTelegramId(long long tgId);

    uint64_t UserHandshake(int id);
    bool EditUser(int id, const std::string& firstName, const std::string& phone, const std::string& whatsapp, const std::string& viber);
    DBUser* GetUser(const std::string& username);
    bool ChangePassword(const std::string& phone, const std::string& password);
    bool UserAddDevice(int userId, const std::string& device, const std::string& os);

    bool SetUserAvatar(int userId, const std::string& avatarPath);
    bool SetUserCover(int userId, const std::string& coverPath);

private:
    static UserManager* sInstance;
    //pqxx::connection* mPsql = nullptr;
//	PGconn* mPG = nullptr;
};

#endif // __USER_MANAGER__
