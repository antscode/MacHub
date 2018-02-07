#include <Dialogs.h>
#include <string.h>
#include <machttp/HttpClient.h>
#include <json/json.h>
#include "Google.h"
#include "../Util.h"
#include "../Prefs.h"
#include "../Keys.h"

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

OAuthModule::AuthData Google::GetAuthData()
{
	AuthData authData;
	authData.Status = Error;
	authData.ErrorMsg = "";

	HttpClient httpClient("https://accounts.google.com");

	// Set the lowest cipher suite that the server accepts to maximise performance
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/o/oauth2/device/code",
		"client_id=" + Keys::GoogleClientId + "&scope=email%20profile");

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

	return authData;
}

OAuthModule::OAuthResponse Google::QueryUserCode(AuthData authData)
{
	OAuthResponse authResponse;
	authResponse.Status = Error;
	authResponse.ErrorMsg = "";

	HttpClient httpClient("https://www.googleapis.com");
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/oauth2/v4/token",
		"client_id=" + Keys::GoogleClientId +
		"&client_secret=" + Keys::GoogleClientSecret +
		"&code=" + authData.Code +
		"&grant_type=http://oauth.net/grant_type/device/1.0");

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
				std::string accessToken = root["access_token"].asString();
				std::string refreshToken = "";

				if (root.isMember("refresh_token"))
				{
					refreshToken = root["refresh_token"].asString();
				}

				// Get Google username to save to prefs
				response = httpClient.Get("/oauth2/v1/userinfo?access_token=" + accessToken);

				if (response.Success)
				{
					parseSuccess = reader.parse(response.Content.c_str(), root);

					if (parseSuccess && root.isMember("name"))
					{
						std::string username = root["name"].asString();

						authResponse.Status = Success;
						authResponse.AccessToken = accessToken;
						authResponse.RefreshToken = refreshToken;
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

	return authResponse;
}