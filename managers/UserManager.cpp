#include "UserManager.h"
#include <iostream>
#include "PQManager.h"

UserManager* UserManager::sInstance = nullptr;

UserManager* UserManager::Get()
{
    if (!sInstance) sInstance = new UserManager();

    return sInstance;
}



/*void UserManager::SetPsql(pqxx::connection* pPsql)
{
    mPsql = pPsql;
}*/

#include <iostream>
#include <random>
int generateRandomCode() 
{
    // Create a random device
    std::random_device rd;

    // Use a Mersenne Twister random number generator
    std::mt19937 gen(rd());

    // Define the range for 6-digit numbers (100000 to 999999)
    std::uniform_int_distribution<> distr(100000, 999999);

    // Generate and return the random number
    return distr(gen);
}

int UserManager::CreateTelegramUserCode(int id)
{
    int code = generateRandomCode();
    std::string sql = "UPDATE users set tg_code = " + std::to_string(code) +
        " WHERE id = " + std::to_string(id) + ";";


    PGconn* pg = ConnectionPool::Get()->getConnection();
    PGresult* res = PQexec(pg, sql.c_str());
    PQclear(res);
    ConnectionPool::Get()->releaseConnection(pg);
    return code;
}

int UserManager::CreateTelegramUser(const std::string& username, long long tgId, const std::string& name)
{
    std::string sql = "INSERT INTO users(tg_username, tg_id, name, points, league, tg_code) VALUES ('"
        + username + "', "
        + std::to_string(tgId) + ", '"
        + name + "', "
        + std::to_string(0) + ", "
        + std::to_string(2) + ", "
        + std::to_string(generateRandomCode()) +
        ");";

    PGconn* pg = ConnectionPool::Get()->getConnection();
    PGresult* res = PQexec(pg, sql.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "Error: Failed to create user: %s", PQerrorMessage(pg));
        PQclear(res);
        ConnectionPool::Get()->releaseConnection(pg);
        return -1;
    }

    sql = "SELECT currval('users_id_seq');";
    res = PQexec(pg, sql.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "Error: Failed to get new user id: %s", PQerrorMessage(pg));
        PQclear(res);
        ConnectionPool::Get()->releaseConnection(pg);
        return -1;
    }
    char* temp = (char*)calloc(256, sizeof(char));
    int rec_count = PQntuples(res);
    strcpy(temp, PQgetvalue(res, 0, 0));
    int id = atoi(temp);
    free(temp);
    ConnectionPool::Get()->releaseConnection(pg);
    return id;
}

int UserManager::CreateUser(const std::string& email, const std::string& name)
{
    std::string sql = "INSERT INTO users(email, name, points, league) VALUES ('"
        + email + "', '" 
		+ name + "', " 
        + std::to_string(0) + ", "
        + std::to_string(2) +
    ");";

    PGconn* pg = ConnectionPool::Get()->getConnection();
    PGresult* res = PQexec(pg, sql.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "Error: Failed to create user: %s", PQerrorMessage(pg));
		PQclear(res);
        ConnectionPool::Get()->releaseConnection(pg);
        return -1;
    }

    sql = "SELECT currval('users_id_seq');";
    res = PQexec(pg, sql.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "Error: Failed to get new user id: %s", PQerrorMessage(pg));
        PQclear(res);
        ConnectionPool::Get()->releaseConnection(pg);
        return -1;
    }
    char* temp = (char*)calloc(256, sizeof(char));
    int rec_count = PQntuples(res);
    strcpy(temp, PQgetvalue(res, 0, 0));
    int id = atoi(temp);
    free(temp);
    ConnectionPool::Get()->releaseConnection(pg);
    return id;
}

int UserManager::CreateUser(const std::string& username, const std::string& password, const std::string& name)
{
    std::string sql = "INSERT INTO users(username, password, name) VALUES ('"
        + username + "', '"
        + password + "', '"
        + name + "');";


    PGconn* pg = ConnectionPool::Get()->getConnection();
    PGresult* res = PQexec(pg, sql.c_str());
	  if (PQresultStatus(res) != PGRES_COMMAND_OK)
	  {
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "Error: Failed to create user: %s", PQerrorMessage(pg));
		    PQclear(res);
        ConnectionPool::Get()->releaseConnection(pg);
        return -1;
    }

    sql = "SELECT currval('users_id_seq');";
    res = PQexec(pg, sql.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "Error: Failed to get new user id: %s", PQerrorMessage(pg));
        PQclear(res);
        ConnectionPool::Get()->releaseConnection(pg);
        return -1;
    }
    char* temp = (char*)calloc(256, sizeof(char));
    int rec_count = PQntuples(res);
    strcpy(temp, PQgetvalue(res, 0, 0));
    int id = atoi(temp);
    free(temp);
    ConnectionPool::Get()->releaseConnection(pg);
    return id;
}
#include <cstdlib>

bool UserManager::UserAddDevice(int userId,const std::string& device, const std::string& os)
{
    PGconn* pg = ConnectionPool::Get()->getConnection();

    std::string sql = "SELECT COUNT(*) FROM devices where user_id = " + std::to_string(userId)
        + " AND device = '" + device + "';";

    PGresult* res = PQexec(pg, sql.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(pg));
        PQclear(res);
        //PQfinish(pg);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }
    char* temp = (char*)calloc(256, sizeof(char));
    strcpy(temp, PQgetvalue(res, 0, 0));
    bool exists = atoi(temp) > 0;
    PQclear(res);
    free(temp);
    if (exists) 
    {
        ConnectionPool::Get()->releaseConnection(pg);
        return true;
    }

    sql = "INSERT INTO devices (user_id, device, os) VALUES (" + std::to_string(userId) 
        + ",'" + device 
        + "','" + os 
        + "');";
    res = PQexec(pg, sql.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(pg));
        PQclear(res);
        //PQfinish(pg);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }

    PQclear(res);
    //PQfinish(pg);
    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool UserManager::ChangePassword(const std::string& phone, const std::string& password)
{
   std::string sql = "UPDATE USERS SET password = '"
            + password + "' WHERE phone = '" + phone + "';";

    PGconn* pg = ConnectionPool::Get()->getConnection();

    PGresult* res = PQexec(pg, sql.c_str());
	  if (PQresultStatus(res) != PGRES_COMMAND_OK)
	  {
      char* err = PQerrorMessage(pg);
      fprintf(stderr, "SELECT failed: %s", PQerrorMessage(pg));
		  PQclear(res);
      //PQfinish(pg);
      ConnectionPool::Get()->releaseConnection(pg);
		  //exit_nicely(conn);
		  return false;
	  }
    PQclear(res);
    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

DBUser* UserManager::GetUser(const std::string& username)
{
    std::string sql = "SELECT * FROM users WHERE username = '"
        + username 
        + "';";
      
   PGconn* pg = ConnectionPool::Get()->getConnection(); //ConnectionPool::Get()->getConnection();

    PGresult* res = PQexec(pg, sql.c_str());
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(pg));
		    PQclear(res);
        //PQfinish(pg);
        ConnectionPool::Get()->releaseConnection(pg);
		//exit_nicely(conn);
		return nullptr;
	}

	/*int field_count = PQnfields(res);
	for (int i = 0; i< field_count; i++)
	{
		fprintf(stdout, "%-40s", PQfname(res, i));
	}
	fprintf(stdout, "\n");*/

	int nt = PQntuples(res);
	if (!nt)  
  {
    ConnectionPool::Get()->releaseConnection(pg);
    return nullptr;
  }
	int nf = PQnfields(res);

	char* temp = (char*)calloc(256, sizeof(char));
	DBUser* pUser = new DBUser();
	strcpy(temp, PQgetvalue(res, 0, 0));
	pUser->Id = atoi(temp);

	strcpy(temp, PQgetvalue(res, 0, 1));
	pUser->Username = (temp);

	strcpy(temp, PQgetvalue(res, 0, 2));
	pUser->Password = (temp);

	strcpy(temp, PQgetvalue(res, 0, 3));
	pUser->Name = (temp);

    strcpy(temp, PQgetvalue(res, 0, 4));
    pUser->Avatar = (temp);

	free(temp);
    //PQfinish(pg);
   ConnectionPool::Get()->releaseConnection(pg);
    return pUser;
}

DBUser* UserManager::GetUserByEmail(const std::string& email)
{
    if (email.size() <= 0) return nullptr;
    std::string sql = "SELECT * FROM users WHERE email = '"
        + email + "';";

    PGconn* pConn = ConnectionPool::Get()->getConnection();

    PGresult* res = PQexec(pConn, sql.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0)
    {
        char* err = PQerrorMessage(pConn);
        fprintf(stderr, "Error: Failed to get user: %s", PQerrorMessage(pConn));
        PQclear(res);
        ConnectionPool::Get()->releaseConnection(pConn);
        //exit_nicely(conn);
        return nullptr;
    }

    char* temp = (char*)calloc(256, sizeof(char));
    DBUser* pUser = new DBUser();
    strcpy(temp, PQgetvalue(res, 0, 0));
    pUser->Id = atoi(temp);

    strcpy(temp, PQgetvalue(res, 0, 1));
    pUser->Username = (temp);

    strcpy(temp, PQgetvalue(res, 0, 2));
    pUser->Password = (temp);

    strcpy(temp, PQgetvalue(res, 0, 3));
    pUser->Name = (temp);

    strcpy(temp, PQgetvalue(res, 0, 4));
    pUser->Avatar = (temp);

    strcpy(temp, PQgetvalue(res, 0, 5));
    pUser->Points = atoi(temp);

    strcpy(temp, PQgetvalue(res, 0, 6));
    pUser->Email = temp;

    ConnectionPool::Get()->releaseConnection(pConn);
    free(temp);
    return pUser;
}

DBUser* UserManager::GetUserByTelegramId(long long tgId)
{
    if (tgId <= 0) return nullptr;
    std::string sql = "SELECT * FROM users WHERE tg_id = '"
        + std::to_string(tgId) + "';";

    PGconn* pConn = ConnectionPool::Get()->getConnection();

    PGresult* res = PQexec(pConn, sql.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0)
    {
        char* err = PQerrorMessage(pConn);
        fprintf(stderr, "Error: Failed to get user: %s", PQerrorMessage(pConn));
        PQclear(res);
        ConnectionPool::Get()->releaseConnection(pConn);
        //exit_nicely(conn);
        return nullptr;
    }

    char* temp = (char*)calloc(256, sizeof(char));
    DBUser* pUser = new DBUser();
    strcpy(temp, PQgetvalue(res, 0, 0));
    pUser->Id = atoi(temp);

    strcpy(temp, PQgetvalue(res, 0, 1));
    pUser->Username = (temp);

    strcpy(temp, PQgetvalue(res, 0, 2));
    pUser->Password = (temp);

    strcpy(temp, PQgetvalue(res, 0, 3));
    pUser->Name = (temp);

    strcpy(temp, PQgetvalue(res, 0, 4));
    pUser->Avatar = (temp);

    strcpy(temp, PQgetvalue(res, 0, 5));
    pUser->Points = atoi(temp);

    strcpy(temp, PQgetvalue(res, 0, 6));
    pUser->Email = temp;

    strcpy(temp, PQgetvalue(res, 0, 8));
    pUser->TelegramUsername = temp;

    strcpy(temp, PQgetvalue(res, 0, 9));
    pUser->TelegramId = atoll(temp);

    strcpy(temp, PQgetvalue(res, 0, 10));
    pUser->TelegramCode = atoll(temp);

    ConnectionPool::Get()->releaseConnection(pConn);
    free(temp);
    return pUser;
}



bool UserManager::EditUser(int id, const std::string& firstName, const std::string& phone, const std::string& whatsapp, const std::string& viber)
{
    std::string sql = "UPDATE users SET first_name='" + firstName 
        + "', phone = '" + phone 
        + "', whatsapp = '" + whatsapp
        + "', viber = '" + viber
        + "' WHERE id = "
            + std::to_string(id) + ";";

    PGconn* pg = ConnectionPool::Get()->getConnection();
    PGresult* res = PQexec(pg, sql.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "Error: Failed to edit user: %s", PQerrorMessage(pg));
        PQclear(res);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }
    PQclear(res);
    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool UserManager::MeDelete(int id)
{
    PGconn* pConn = ConnectionPool::Get()->getConnection();
    std::string sql = "DELETE FROM cars WHERE user_id = " + std::to_string(id) + ";";
    PGresult* res = PQexec(pConn, sql.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
        char* err = PQerrorMessage(pConn);
        fprintf(stderr, "Error: Failed to delete user cars: %s", PQerrorMessage(pConn));
		PQclear(res);
        ConnectionPool::Get()->releaseConnection(pConn);
		return false;
	}
    PQclear(res);

    sql = "DELETE FROM users WHERE id = " + std::to_string(id) + ";";
    res = PQexec(pConn, sql.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
        char* err = PQerrorMessage(pConn);
        fprintf(stderr, "Error: Failed to delete user: %s", PQerrorMessage(pConn));
		PQclear(res);
        ConnectionPool::Get()->releaseConnection(pConn);
		return false;
	}
    PQclear(res);

    ConnectionPool::Get()->releaseConnection(pConn);
    return true;   
}

bool UserManager::MeHandshake(int id)
{
    using namespace std::chrono;
    uint64_t ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    const std::string sql = "UPDATE users SET handshake_ts = " + std::to_string(ms) + " WHERE id = " + std::to_string(id) + ";";
    PGconn* pConn = ConnectionPool::Get()->getConnection();
    PGresult* res = PQexec(pConn, sql.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
        char* err = PQerrorMessage(pConn);
        fprintf(stderr, "Error: Failed to get user: %s", PQerrorMessage(pConn));
		PQclear(res);
        ConnectionPool::Get()->releaseConnection(pConn);
		return false;
	}
    PQclear(res);
    ConnectionPool::Get()->releaseConnection(pConn);
    return true;
}

uint64_t UserManager::UserHandshake(int id)
{
    const std::string sql = "SELECT handshake_ts FROM users WHERE id = " + std::to_string(id) + ";";
    PGconn* pConn = ConnectionPool::Get()->getConnection();
    PGresult* res = PQexec(pConn, sql.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
        char* err = PQerrorMessage(pConn);
        fprintf(stderr, "Error: Failed to get user: %s", PQerrorMessage(pConn));
		PQclear(res);
        ConnectionPool::Get()->releaseConnection(pConn);
		return 0;
	}
    bool userFound = PQntuples(res) > 0;
    if (!userFound) return -1;

    char* temp = (char*)calloc(256, sizeof(char));
	strcpy(temp, PQgetvalue(res, 0, 0));
	uint64_t ts = atoll(temp);
    PQclear(res);
    ConnectionPool::Get()->releaseConnection(pConn);
    free(temp);
    return ts;
}


DBUser* UserManager::GetUser(int id)
{
    if (id <= 0) return nullptr;
    std::string sql = "SELECT * FROM users WHERE id = "
                + std::to_string(id) + ";";

    PGconn* pConn = ConnectionPool::Get()->getConnection();//ConnectionPool::Get()->getConnection();

    PGresult* res = PQexec(pConn, sql.c_str());
	if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0)
	{
      char* err = PQerrorMessage(pConn);
      fprintf(stderr, "Error: Failed to get user: %s", PQerrorMessage(pConn));
		  PQclear(res);
      // ConnectionPool::Get()->releaseConnection(pConn);
      ConnectionPool::Get()->releaseConnection(pConn);
		  //exit_nicely(conn);
		  return nullptr;
	}

	char* temp = (char*)calloc(256, sizeof(char));
	DBUser* pUser = new DBUser();
	strcpy(temp, PQgetvalue(res, 0, 0));
	pUser->Id = atoi(temp);

	strcpy(temp, PQgetvalue(res, 0, 1));
	pUser->Username = (temp);

	strcpy(temp, PQgetvalue(res, 0, 2));
	pUser->Password = (temp);

	strcpy(temp, PQgetvalue(res, 0, 3));
	pUser->Name = (temp);

    strcpy(temp, PQgetvalue(res, 0, 4));
    pUser->Avatar = (temp);



    //ConnectionPool::Get()->releaseConnection(pConn);
    PQclear(res);
  ConnectionPool::Get()->releaseConnection(pConn);
	free(temp);
  return pUser;
}

bool UserManager::SetUserCover(int userId, const std::string& coverPath)
{
    std::string sql = "UPDATE users SET cover = '" + coverPath + "' WHERE id = " + std::to_string(userId) + ";";
    PGconn* pg = ConnectionPool::Get()->getConnection();
    PGresult* res = PQexec(pg, sql.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "Error: Failed to set user cover: %s", PQerrorMessage(pg));
        PQclear(res);
  
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }
    PQclear(res);

    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}

bool UserManager::SetUserAvatar(int userId, const std::string& avatarPath)
{
    std::string sql = "UPDATE users SET avatar = '" + avatarPath + "' WHERE id = " + std::to_string(userId) + ";";
    PGconn* pg = ConnectionPool::Get()->getConnection();
    PGresult* res = PQexec(pg, sql.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        char* err = PQerrorMessage(pg);
        fprintf(stderr, "Add car image failed: %s", PQerrorMessage(pg));
        PQclear(res);
        //PQfinish(pg);
        ConnectionPool::Get()->releaseConnection(pg);
        return false;
    }
    PQclear(res);
    //PQfinish(pg);
    ConnectionPool::Get()->releaseConnection(pg);
    return true;
}
