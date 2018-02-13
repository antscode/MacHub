#ifndef _GOOGLE_
#define _GOOGLE_

#include "Module.h"
#include "OAuthModule.h"

class Google : public OAuthModule
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
	std::string _accessToken;
	std::string _refreshToken;
	virtual void UsernameResponse(HttpResponse response);
};

#endif //_GOOGLE_