#ifndef _OAUTHMODULE_
#define _OAUTHMODULE_

#include <MacHTTP/HttpResponse.h>
#include "Module.h"

class OAuthModule : public Module
{
public:
	virtual std::string GetId() = 0;
	virtual std::string GetName() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void ShowPrefsDialog();
	virtual void UpdatePrefsDialog();
	virtual void HandlePrefsDialogEvent(EventRecord *eventPtr);

protected:

	enum OAuthStatus
	{
		Success,
		Incomplete,
		Error
	};

	struct AuthData
	{
		std::string Code;
		std::string UserCode;
		std::string Url;
		std::string ErrorMsg;
		OAuthStatus Status;
	};

	struct OAuthResponse
	{
		std::string AccessToken;
		std::string RefreshToken;
		std::string AccountName;
		std::string ErrorMsg;
		OAuthStatus Status;
	};

	AuthData _authData;

	virtual void AuthDataRequest() = 0;
	virtual void AuthDataResponse(HttpResponse response) = 0;
	void DisplayAuthData(AuthData authData);

	virtual void UserCodeRequest() = 0;
	virtual void UserCodeResponse(HttpResponse response) = 0;
	void DisplayUserCode(OAuthResponse response);

	std::string GetResponseErrorMsg(HttpResponse response);

private:
	enum UIState
	{
		PleaseWait,
		EnterCode
	};

	UIState _uiState;
	void UpdateUI();
	void CheckUserCode();
	void EraseStatusText();
};

#endif //_OAUTHMODULE_