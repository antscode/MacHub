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
	virtual AuthData GetAuthData();
	virtual OAuthResponse QueryUserCode(AuthData authData);
};

#endif //_GOOGLE_