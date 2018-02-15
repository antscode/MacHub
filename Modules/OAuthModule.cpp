#include <Dialogs.h>
#include <string.h>
#include <json/json.h>
#include "OAuthModule.h"
#include "../Util.h"
#include "../Prefs.h"
#include "../Comms.h"

void OAuthModule::ShowPrefsDialog()
{
	PrefsDialog = GetNewDialog(129, 0, (WindowPtr)-1);

	SetWTitle(PrefsDialog, Util::StrToPStr(GetName()));

	_uiState = PleaseWait;
	UpdateUI();

	AuthDataRequest();
}

void OAuthModule::DisplayAuthData(AuthData authData)
{
	_authData = authData;

	if (_authData.Status == Success)
	{
		_uiState = EnterCode;
		UpdateUI();
	}
	else
	{
		ParamText(Util::StrToPStr(_authData.ErrorMsg), nil, nil, nil);
		StopAlert(131, nil);

		DisposeDialog(PrefsDialog);
		PrefsDialog = 0;
	}
}

void OAuthModule::UpdateUI()
{
	MacSetPort(PrefsDialog);

	switch (_uiState)
	{
		case PleaseWait:
		{
			Util::FrameDefaultButton(PrefsDialog, 2, false);

			TextSize(0);
			MoveTo(10, 20);
			EraseStatusText();

			std::string msg = "Contacting " + GetName() + ", please wait...";
			DrawString(Util::StrToPStr(msg));

			UpdateDialog(PrefsDialog, PrefsDialog->visRgn);
			break;
		}

		case EnterCode:
		{
			Util::FrameDefaultButton(PrefsDialog, 2, true);

			MoveTo(10, 20);
			EraseStatusText();

			DrawString("\pVisit ");

			ForeColor(blueColor);
			DrawString(Util::StrToPStr(_authData.Url + " "));

			ForeColor(blackColor);

			Point curPos;
			GetPen(&curPos);
			int maxWidth = PrefsDialog->portRect.right - curPos.h;

			Util::DrawTextToWidth("on your smartphone and enter this code:", maxWidth, 15, 10);

			GetPen(&curPos);
			TextSize(24);

			std::string userCode = _authData.UserCode.c_str();
			const char* cUserCode = userCode.c_str();
			char* pUserCode = (char*)Util::CtoPStr((char*)cUserCode);

			short strWidth;
			strWidth = StringWidth((ConstStr255Param)pUserCode);
			int centrePos = (PrefsDialog->portRect.right - strWidth) / 2;

			MoveTo(centrePos, curPos.v + 34);
			DrawString((ConstStr255Param)pUserCode);
			UpdateDialog(PrefsDialog, PrefsDialog->visRgn);

			TextSize(0);
			break;
		}
	}
}

void OAuthModule::UpdatePrefsDialog()
{
	BeginUpdate(PrefsDialog);
	UpdateUI();
	EndUpdate(PrefsDialog);
}

void OAuthModule::HandlePrefsDialogEvent(EventRecord *eventPtr)
{
	short int item;
	DialogRef dialogRef;
	
	if (DialogSelect(eventPtr, &dialogRef, &item))
	{
		switch (item)
		{
			case 1:
				Comms::Http.CancelRequest();
				DisposeDialog(PrefsDialog);
				PrefsDialog = 0;
				break;

			case 2:
				CheckUserCode();
				break;
		}
	}
}

void OAuthModule::CheckUserCode()
{
	_uiState = PleaseWait;
	UpdateUI();

	UserCodeRequest();
}

void OAuthModule::DisplayUserCode(OAuthResponse response)
{
	switch (response.Status)
	{
		case Success:
		{
			Json::Value account;

			account["type"] = GetId();
			account["name"] = response.AccountName;
			account["access_token"] = response.AccessToken;

			if (response.RefreshToken != "")
			{
				account["refresh_token"] = response.RefreshToken;
			}

			Prefs::Data["accounts"].append(account);
			Prefs::Save();

			DisposeDialog(PrefsDialog);
			PrefsDialog = 0;
			break;
		}

		case Incomplete:
		{
			ParamText(Util::StrToPStr(GetName()), nil, nil, nil);
			NoteAlert(130, nil);

			_uiState = EnterCode;
			UpdateUI();
			break;
		}

		case Error:
		{
			ParamText(Util::StrToPStr(response.ErrorMsg), nil, nil, nil);
			StopAlert(131, nil);

			_uiState = EnterCode;
			UpdateUI();
			break;
		}
	}
}

void OAuthModule::EraseStatusText()
{
	Rect rect;
	MacSetRect(&rect,
		PrefsDialog->portRect.left,
		PrefsDialog->portRect.top,
		PrefsDialog->portRect.right,
		PrefsDialog->portRect.bottom - 40);

	EraseRect(&rect);
}

std::string OAuthModule::GetResponseErrorMsg(HttpResponse response)
{
	std::string err;

	if (response.Success)
	{
		err = "Server returned status code " + std::to_string(response.StatusCode) + ".";
	}
	else if (response.ErrorCode == ConnectionError)
	{
		err = "Could not connect to " + GetName() + ", please check your Internet connection.";
	}
	else
	{
		err = response.ErrorMsg;
	}

	return err;
}