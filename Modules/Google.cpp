#include <Dialogs.h>
#include <string.h>
#include <machttp/HttpClient.h>
#include <json/json.h>
#include "Google.h"
#include "../Util.h"
#include "../Prefs.h"

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

	HttpClient httpClient("https://accounts.google.com");

	// Set the lowest cipher suite that the server accepts to maximise performance
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/o/oauth2/device/code",
		"client_id=" + _clientId + "&scope=email%20profile");

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(response.Content.c_str(), root);

	Util::DebugStr(response.Content);

	authData.Code = root["device_code"].asString();
	authData.UserCode = root["user_code"].asString();
	authData.Url = root["verification_url"].asString();

	return authData;
}

OAuthModule::OAuthResponse Google::QueryUserCode(AuthData authData)
{
	OAuthResponse authResponse;

	HttpClient httpClient("https://graph.facebook.com");
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/v2.6/device/login_status",
		"access_token=" + _clientId + "&code=" + authData.Code);

	Json::Value root;
	Json::Reader reader;
	bool parseSuccess = reader.parse(response.Content.c_str(), root);

	if (parseSuccess && root.isMember("access_token"))
	{
		// Save access token to prefs
		std::string userAccessToken = root["access_token"].asString();

		// Get FB username to save to prefs
		response = httpClient.Get("/v2.3/me?fields=name,picture&access_token=" + userAccessToken);
		parseSuccess = reader.parse(response.Content.c_str(), root);
		std::string username = root["name"].asString();

		authResponse.Status = Success;
		authResponse.AccessToken = userAccessToken;
		authResponse.RefreshToken = "";
		authResponse.AccountName = username;
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
			authResponse.Status = Error;
		}
	}

	return authResponse;
}