#include <Dialogs.h>
#include <string.h>
#include <machttp/HttpClient.h>
#include <json/json.h>
#include "OAuthModule.h"
#include "../Util.h"
#include "../Prefs.h"

void OAuthModule::ShowPrefsDialog()
{
	PrefsDialog = GetNewDialog(129, 0, (WindowPtr)-1);
	MacSetPort(PrefsDialog);

	_uiState = PleaseWait;
	UpdateUI();

	_authData = GetAuthData();

	_uiState = EnterCode;
	UpdateUI();
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
				DisposeDialog(PrefsDialog);
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

	OAuthResponse response = QueryUserCode(_authData);

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

			break;
		}

		case Incomplete:
		{
			NoteAlert(130, nil);

			_uiState = EnterCode;
			UpdateUI();
			break;
		}

		case Error:
		{
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