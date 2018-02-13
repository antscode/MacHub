#include <Dialogs.h>
#include <string.h>
#include <json/json.h>
#include "Facebook.h"
#include "../Util.h"
#include "../Prefs.h"
#include "../Keys.h"
#include "../Comms.h"

using namespace std::placeholders;

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

void Facebook::AuthDataRequest()
{
	// Set the lowest cipher suite that the server accepts to maximise performance
	Comms::Http.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	Comms::Http.Post("https://graph.facebook.com/v2.6/device/login",
		"access_token=" + Keys::FacebookAccessToken + "&scope=user_posts",
		std::bind(&Facebook::AuthDataResponse, this, _1));
}

void Facebook::AuthDataResponse(HttpResponse response)
{
	AuthData authData;
	authData.Status = Error;
	authData.ErrorMsg = "";

	if (response.Success)
	{
		Json::Value root;
		Json::Reader reader;
		bool parseSuccess = reader.parse(response.Content.c_str(), root);

		if (parseSuccess)
		{
			if (root.isMember("code"))
			{
				authData.Status = Success;
				authData.Code = root["code"].asString();
				authData.UserCode = root["user_code"].asString();
				authData.Url = "facebook.com/device";
			}
			else if (root.isMember("error"))
			{
				authData.ErrorMsg = "Facebook returned error: " + root["error"].asString() + ".";
			}
		}
	}
	else
	{
		authData.ErrorMsg = GetResponseErrorMsg(response);
	}

	DisplayAuthData(authData);
}

void Facebook::UserCodeRequest()
{
	Comms::Http.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	Comms::Http.Post("https://graph.facebook.com/v2.6/device/login_status",
		"access_token=" + Keys::FacebookAccessToken + "&code=" + _authData.Code,
		std::bind(&Facebook::UserCodeResponse, this, _1));
}

void Facebook::UserCodeResponse(HttpResponse response)
{
	OAuthResponse authResponse;
	authResponse.Status = Error;
	authResponse.ErrorMsg = "";

	if (response.Success)
	{
		Json::Value root;
		Json::Reader reader;
		bool parseSuccess = reader.parse(response.Content.c_str(), root);

		if (parseSuccess)
		{
			if (root.isMember("access_token"))
			{
				// Save access token to prefs
				_userAccessToken = root["access_token"].asString();

				// Get FB username to save to prefs
				Comms::Http.Get("https://graph.facebook.com/v2.3/me?fields=name,picture&access_token=" + _userAccessToken,
					std::bind(&Facebook::UsernameResponse, this, _1));

				return;
			}
			else if (root.isMember("error"))
			{
				const Json::Value error = root["error"];

				int resCode = error["code"].asInt();

				if (resCode == 31) // 31 = not yet confirmed by user
				{
					authResponse.Status = Incomplete;
				}
				else
				{
					authResponse.ErrorMsg = "Facebook returned error code " + std::to_string(resCode) + ".";
				}
			}
		}
	}
	else
	{
		authResponse.ErrorMsg = GetResponseErrorMsg(response);
	}

	DisplayUserCode(authResponse);
}

void Facebook::UsernameResponse(HttpResponse response)
{
	OAuthResponse authResponse;
	authResponse.Status = Error;
	authResponse.ErrorMsg = "";

	if (response.Success)
	{
		Json::Value root;
		Json::Reader reader;
		bool parseSuccess = reader.parse(response.Content.c_str(), root);

		if (parseSuccess && root.isMember("name"))
		{
			std::string username = root["name"].asString();

			authResponse.Status = Success;
			authResponse.AccessToken = _userAccessToken;
			authResponse.RefreshToken = "";
			authResponse.AccountName = username;
		}
		else if (root.isMember("error"))
		{
			const Json::Value error = root["error"];
			int resCode = error["code"].asInt();

			authResponse.ErrorMsg = "Facebook returned error code " + std::to_string(resCode) + " when gettng username.";
		}
	}
	else
	{
		authResponse.ErrorMsg = GetResponseErrorMsg(response);
	}

	DisplayUserCode(authResponse);
}