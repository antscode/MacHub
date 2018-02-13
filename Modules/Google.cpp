#include <Dialogs.h>
#include <string.h>
#include <json/json.h>
#include "Google.h"
#include "../Util.h"
#include "../Prefs.h"
#include "../Keys.h"
#include "../Comms.h"

using namespace std::placeholders;

std::string Google::GetId()
{
	return "google";
}

std::string Google::GetName()
{
	return "Google";
}

void Google::Init()
{
	// TODO
}

void Google::Update()
{
	// TODO
}

void Google::AuthDataRequest()
{
	// Set the lowest cipher suite that the server accepts to maximise performance
	Comms::Http.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);
	
	Comms::Http.Post("https://accounts.google.com/o/oauth2/device/code",
		"client_id=" + Keys::GoogleClientId + "&scope=email%20profile",
		std::bind(&Google::AuthDataResponse, this, _1));
}

void Google::AuthDataResponse(HttpResponse response)
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
			if (root.isMember("device_code"))
			{
				authData.Status = Success;
				authData.Code = root["device_code"].asString();
				authData.UserCode = root["user_code"].asString();
				authData.Url = "google.com/device";
			}
			else if (root.isMember("error"))
			{
				authData.ErrorMsg = "Google returned error: " + root["error"].asString() + ".";
			}
		}
	}
	else
	{
		authData.ErrorMsg = GetResponseErrorMsg(response);
	}

	DisplayAuthData(authData);
}

void Google::UserCodeRequest()
{
	Comms::Http.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	Comms::Http.Post("https://www.googleapis.com/oauth2/v4/token",
		"client_id=" + Keys::GoogleClientId +
		"&client_secret=" + Keys::GoogleClientSecret +
		"&code=" + _authData.Code +
		"&grant_type=http://oauth.net/grant_type/device/1.0",
		std::bind(&Google::UserCodeResponse, this, _1));
}

void Google::UserCodeResponse(HttpResponse response)
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
				_accessToken = root["access_token"].asString();
				_refreshToken = "";

				if (root.isMember("refresh_token"))
				{
					_refreshToken = root["refresh_token"].asString();
				}

				// Get Google username to save to prefs
				Comms::Http.Get("https://www.googleapis.com/oauth2/v1/userinfo?access_token=" + _accessToken,
					std::bind(&Google::UsernameResponse, this, _1));

				return;
			}
			else if (root.isMember("error"))
			{
				std::string error = root["error"].asString();

				if (error == "authorization_pending")
				{
					authResponse.Status = Incomplete;
				}
				else
				{
					authResponse.ErrorMsg = "Google returned error " + error + ".";
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

void Google::UsernameResponse(HttpResponse response)
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
			authResponse.AccessToken = _accessToken;
			authResponse.RefreshToken = _refreshToken;
			authResponse.AccountName = username;
		}
		else if (root.isMember("error"))
		{
			std::string error = root["error"].asString();
			authResponse.ErrorMsg = "Google returned error " + error + " when getting username.";
		}
	}
	else
	{
		authResponse.ErrorMsg = GetResponseErrorMsg(response);
	}

	DisplayUserCode(authResponse);
}