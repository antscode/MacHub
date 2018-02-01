#include <Dialogs.h>
#include <string.h>
#include <machttp/HttpClient.h>
#include <json/json.h>
#include "Facebook.h"
#include "../Util.h"
#include "../Prefs.h"

std::string Facebook::GetId()
{
	return "facebook";
}

std::string Facebook::GetName()
{
	return "Facebook";
}

void Facebook::Init()
{
	// TODO
}

void Facebook::Update()
{
	// TODO
}

void Facebook::ShowPrefsDialog()
{
	PrefsDialog = GetNewDialog(129, 0, (WindowPtr)-1);
	MacSetPort(PrefsDialog);

	_uiState = PleaseWait;
	UpdateUI();

	HttpClient httpClient("https://graph.facebook.com");

	// Set the lowest cipher suite that the server accepts to maximise performance
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/v2.6/device/login",
		"access_token=" + _accessToken + "&scope=user_posts");

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(response.Content.c_str(), root);

	_code = root["code"].asString();
	_userCode = root["user_code"].asString();

	_uiState = EnterCode;
	UpdateUI();
}

void Facebook::UpdateUI()
{
	MacSetPort(PrefsDialog);

	switch (_uiState)
	{
		case PleaseWait:
			Util::FrameDefaultButton(PrefsDialog, 2, false);

			TextSize(0);
			MoveTo(10, 20);
			EraseStatusText();

			DrawString("\pContacting Facebook, please wait...");
			UpdateDialog(PrefsDialog, PrefsDialog->visRgn);
			break;

		case EnterCode:
			Util::FrameDefaultButton(PrefsDialog, 2, true);

			MoveTo(10, 20);
			EraseStatusText();

			DrawString("\pVisit ");

			ForeColor(blueColor);
			DrawString("\pfacebook.com/device ");

			ForeColor(blackColor);

			Point curPos;
			GetPen(&curPos);
			int maxWidth = PrefsDialog->portRect.right - curPos.h;

			Util::DrawTextToWidth("on your smartphone and enter this code:", maxWidth, 15, 10);

			GetPen(&curPos);
			TextSize(24);

			std::string userCode = _userCode.c_str();
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

void Facebook::UpdatePrefsDialog()
{
	BeginUpdate(PrefsDialog);
	UpdateUI();
	EndUpdate(PrefsDialog);
}

void Facebook::HandlePrefsDialogEvent(EventRecord *eventPtr)
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

void Facebook::CheckUserCode()
{
	_uiState = PleaseWait;
	UpdateUI();

	HttpClient httpClient("https://graph.facebook.com");
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/v2.6/device/login_status",
		"access_token=" + _accessToken + "&code=" + _code);

	Json::Value root;
	Json::Reader reader;
	bool parseSuccess = reader.parse(response.Content.c_str(), root);

	if (parseSuccess && root.isMember("access_token"))
	{
		// Save access token to prefs
		std::string userAccessToken = root["access_token"].asString();

		// Get FB username to save to prefs
		response = httpClient.Get("/v2.3/me?fields=name,picture&access_token=" + userAccessToken);
		parsingSuccessful = reader.parse(response.Content.c_str(), root);
		std::string username = root["name"].asString();

		Json::Value fbAccount;

		fbAccount["type"] = "facebook";
		fbAccount["name"] = username;
		fbAccount["access_token"] = userAccessToken;

		Prefs::Data["accounts"].append(fbAccount);
		Prefs::Save();

		DisposeDialog(PrefsDialog);
	}
	else if (root.isMember("error"))
	{
		const Json::Value error = root["error"];

		int resCode = error["code"].asInt();

		if (resCode == 31) // 31 = not yet confirmed by user
		{
			NoteAlert(130, nil);
		}
		else
		{
			StopAlert(131, nil);
		}

		_uiState = EnterCode;
		UpdateUI();
	}
}

void Facebook::EraseStatusText()
{
	Rect rect;
	MacSetRect(&rect,
		PrefsDialog->portRect.left,
		PrefsDialog->portRect.top,
		PrefsDialog->portRect.right,
		PrefsDialog->portRect.bottom - 40);

	EraseRect(&rect);
}