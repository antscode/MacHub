#ifndef _OAUTHMODULE_
#define _OAUTHMODULE_

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
	struct AuthData
	{
		std::string Code;
		std::string UserCode;
		std::string Url;
	};

	enum OAuthStatus
	{
		Success,
		Incomplete,
		Error
	};

	struct OAuthResponse
	{
		std::string AccessToken;
		std::string RefreshToken;
		std::string AccountName;
		OAuthStatus Status;
	};

	virtual AuthData GetAuthData() = 0;
	virtual OAuthResponse QueryUserCode(AuthData authData) = 0;

private:
	enum UIState
	{
		PleaseWait,
		EnterCode
	};

	UIState _uiState;
	AuthData _authData;
	void UpdateUI();
	void CheckUserCode();
	void EraseStatusText();
};

#endif //_OAUTHMODULE_