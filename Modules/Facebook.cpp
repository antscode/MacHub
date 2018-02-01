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

OAuthModule::AuthData Facebook::GetAuthData()
{
	AuthData authData;

	HttpClient httpClient("https://graph.facebook.com");

	// Set the lowest cipher suite that the server accepts to maximise performance
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/v2.6/device/login",
		"access_token=" + _accessToken + "&scope=user_posts");

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(response.Content.c_str(), root);

	authData.Code = root["code"].asString();
	authData.UserCode = root["user_code"].asString();
	authData.Url = "facebook.com/device";

	return authData;
}

OAuthModule::OAuthResponse Facebook::QueryUserCode(AuthData authData)
{
	OAuthResponse authResponse;

	HttpClient httpClient("https://graph.facebook.com");
	httpClient.SetCipherSuite(MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA);

	HttpResponse response = httpClient.Post("/v2.6/device/login_status",
		"access_token=" + _accessToken + "&code=" + authData.Code);

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