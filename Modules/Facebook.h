#ifndef _FACEBOOK_
#define _FACEBOOK_
#endif

#ifndef _MODULE_
#include "Module.h"
#endif

class Facebook : public Module
{
public:
	virtual std::string GetId();
	virtual std::string GetName();
	virtual void Init();
	virtual void Update();
	virtual void ShowPrefsDialog();
	virtual void UpdatePrefsDialog();
	virtual void HandlePrefsDialogEvent(EventRecord *eventPtr);
private:
	enum UIState
	{
		PleaseWait,
		EnterCode
	};

	std::string _accessToken = "246689145865793|e94f495fbf957ec7832a41bb8d274609";
	std::string _code, _userCode;
	UIState _uiState;
	void UpdateUI();
	void CheckUserCode();
	void EraseStatusText();
};