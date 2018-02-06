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
};

#endif // _FACEBOOK_