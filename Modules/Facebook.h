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
	virtual void AuthDataRequest();
	virtual void AuthDataResponse(HttpResponse response);
	virtual void UserCodeRequest();
	virtual void UserCodeResponse(HttpResponse response);
	
private:
	std::string _userAccessToken;
	virtual void UsernameResponse(HttpResponse response);
};

#endif // _FACEBOOK_