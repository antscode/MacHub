#include <Dialogs.h>
#include <machttp/HttpClient.h>
#include <Timer.h>
#include "Facebook.h"
#include "Util.h"
#include <json/json.h>


bool poll = false, pollComplete = false;
UnsignedWide lastPoll;
UnsignedWide now;
double pollInterval = (5 * 1000000);
double lastPollTime = 0, currentTime;
std::string accessToken = "246689145865793|e94f495fbf957ec7832a41bb8d274609";
std::string code;

Facebook::Facebook()
{
}

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

	TextSize(10);
	MoveTo(10, 10);

	DrawString("\pContacting Facebook, please wait...");

	HttpClient httpClient("https://graph.facebook.com");

	// Set the lowest cipher suite that the server accepts to maximise performance
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/v2.6/device/login",
		"access_token=" + accessToken + "&scope=user_posts");

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(response.Content.c_str(), root);

	code = root["code"].asString();
	std::string userCode = root["user_code"].asString();

	EraseRect(&PrefsDialog->portRect);
	TextSize(10);
	MoveTo(10, 10);

	DrawString("\pVisit ");

	ForeColor(blueColor);
	DrawString("\pfacebook.com/device ");

	ForeColor(blackColor);
	DrawString("\pon your smartphone and enter this code:");

	MoveTo(50, 50);
	TextSize(24);

	const char* cUserCode = userCode.c_str();
	char* pUserCode = (char*)Util::CtoPStr((char*)cUserCode);
	DrawString((ConstStr255Param)pUserCode);
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
	MacSetPort(PrefsDialog);

	HttpClient httpClient("https://graph.facebook.com");
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/v2.6/device/login_status",
		"access_token=" + accessToken + "&code=" + code);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(response.Content.c_str(), root);

	if (root.isMember("access_token"))
	{
		// Save access token to prefs
		// TODO

		std::string userAccessToken = root["access_token"].asString();
		response = httpClient.Get("/v2.3/me?fields=name,picture&access_token=" + userAccessToken);

		parsingSuccessful = reader.parse(response.Content.c_str(), root);

		std::string userName = root["name"].asString();
		std::string message = userName + " is connected.";

		Rect pictRect;
		PicHandle picture;
		int successIcon = 132;
		if (!Util::HasColour())
		{
			successIcon = 133;
		}

		picture = GetPicture(successIcon);
		pictRect = (**(picture)).picFrame;

		MacSetRect(&pictRect, 20, 20, 52, 52);
		DrawPicture(picture, &pictRect);

		TextSize(10);
		MoveTo(20, 72);

		const char* cMsg = message.c_str();
		char* pMsg = (char*)Util::CtoPStr((char*)cMsg);
		DrawString((ConstStr255Param)pMsg);



		/*DialogItemType type;
		Handle itemH;
		Rect box;

		GetDialogItem(dialogPtr, 1, &type, &itemH, &box);
		SetControlTitle((ControlHandle)itemH, "\pContinue");*/

	}
	else if (root.isMember("error"))
	{
		const Json::Value error = root["error"];

		int resCode = error["code"].asInt();

		if (resCode != 31) // 31 = not yet confirmed by user
		{
			// Something went wrong
		}
	}
}