#ifndef _FACEBOOK_
#define _FACEBOOK_

#include "Module.h"
#include "OAuthModule.h"

class Facebook : public OAuthModule
{
public:
	virtual std::string GetId();
	virtual std::string GetName();
	virtual void Init();
	virtual void Update();

protected:
	virtual AuthData GetAuthData();
	virtual OAuthResponse QueryUserCode(AuthData authData);

private:
	std::string _accessToken = "246689145865793|e94f495fbf957ec7832a41bb8d274609";
	
};

#endif // _FACEBOOK_