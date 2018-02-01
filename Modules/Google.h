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

private:
	std::string _clientId = "1058897383021-6a2n66spcg7vdh0be3pdpo1m2s42crjk.apps.googleusercontent.com";
	
};

#endif //_GOOGLE_