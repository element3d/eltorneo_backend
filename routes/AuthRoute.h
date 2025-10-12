#ifndef __AUTH_ROUTE__
#define __AUTH_ROUTE__

#include "../httplib.h"

class AuthRoute
{
public:
    static AuthRoute* Get();

    std::function<void(const httplib::Request &, httplib::Response &)> SignUpVerify();
    std::function<void(const httplib::Request &, httplib::Response &)> SignUpV2();
    std::function<void(const httplib::Request&, httplib::Response&)> SignUpGuest();

    std::function<void(const httplib::Request &, httplib::Response &)> SignIn();
    std::function<void(const httplib::Request &, httplib::Response &)> SignInForgot();
    std::function<void(const httplib::Request &, httplib::Response &)> ChangePassword();
    std::function<void(const httplib::Request &, httplib::Response &)> SignInGoogle();
    std::function<void(const httplib::Request &, httplib::Response &)> SignInGoogleWithEmail();
    std::function<void(const httplib::Request&, httplib::Response&)> LinkGoogleWithEmail();
    std::function<void(const httplib::Request&, httplib::Response&)> LinkUserWithUsername();

    std::function<void(const httplib::Request &, httplib::Response &)> SignInWithTelegramBot();
    std::function<void(const httplib::Request&, httplib::Response&)> SignInWithTelegramCode();
    std::function<void(const httplib::Request &, httplib::Response&)> Me();
    std::function<void(const httplib::Request&, httplib::Response&)> MeV2();

    std::function<void(const httplib::Request&, httplib::Response&)> MeDelete();
    std::function<void(const httplib::Request&, httplib::Response&)> GetStats();
    std::function<void(const httplib::Request&, httplib::Response&)> GetUser();
    std::function<void(const httplib::Request&, httplib::Response&)> MeUploadAvatar();
    std::function<void(const httplib::Request&, httplib::Response&)> MeDeleteAvatar();
    std::function<void(const httplib::Request&, httplib::Response&)> MeSetName();
    std::function<void(const httplib::Request&, httplib::Response&)> MeAddFcmToken();
    std::function<void(const httplib::Request&, httplib::Response&)> MeMoveToLeague();

    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotification();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotificationCL();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotificationNL();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotificationUpdate();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotificationQuest();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotificationElClasico();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotificationSerieA();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotificationMatch();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotificationPreview();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendNotificationLeague2();

    std::function<void(const httplib::Request&, httplib::Response&)> UserPredictionSendNotification();
    std::function<void(const httplib::Request&, httplib::Response&)> UserSendSpecialMatchNotification();


private:
    static AuthRoute* sInstance;
};

#endif // __AUTH_ROUTE__
