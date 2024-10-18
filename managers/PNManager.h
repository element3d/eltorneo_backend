#pragma once

#include <string>
#undef min
#undef max

class PNManager 
{
public:
	static std::string CreateJwtToken();
	static std::string RequestAccessToken(const std::string& jwt_token);
	static bool SendPushNotification(const std::string& access_token, const std::string fcm_token, const std::string& title, const std::string& msg, const std::string& icon);

	static bool SendWeekStartedNotification();
	static bool SendCLStartedNotification();
	static bool SendNLStartedNotification();
	static bool SendUpdateNotification();
	static bool SendQuestNotification();

	static bool SendPredictionNotification(int matchId);
	static bool SendSpecialMatchNotification();


};