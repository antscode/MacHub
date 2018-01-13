#include <Resources.h>
#include <Quickdraw.h>
#include <string.h>
#include <string>
#include <sstream>
#include <machttp/HttpClient.h>
#include <json/json.h>
#include "../Util.h"
#include "Weather.h"

Weather::Weather()
{

}

std::string Weather::GetId()
{
	return "weather";
}

std::string Weather::GetName()
{
	return "Weather";
}

void Weather::Init()
{
	HttpClient httpClient("http://api.wunderground.com");
	HttpResponse response = httpClient.Get("/api/dfa099805aaf8fd9/conditions/q/AU/Melbourne.json");
	
	Json::Value root;
	Json::Reader reader;
		
	_parseSuccess = reader.parse(response.Content.c_str(), root);
		
	if (_parseSuccess)
	{
		const Json::Value curObs = root["current_observation"];

		_temp = curObs.get("temp_c", "--").asString();
		_condition = curObs.get("weather", "--").asString();
	}
}

void Weather::Update()
{
	if (_parseSuccess)
	{
		std::string iconStr = GetWeatherIcon(_condition);

		if (!Util::HasColour())
		{
			iconStr = "bw-" + iconStr;
		}

		const char* icon = iconStr.c_str();

		char* pIcon;
		pIcon = (char *)Util::CtoPStr((char*)icon);

		Handle iconRes;
		short resID;
		ResType theResType;
		unsigned char resName[256];

		iconRes = GetNamedResource('PICT', (ConstStr255Param)pIcon);
		GetResInfo(iconRes, &resID, &theResType, resName);

		Rect pictRect;
		PicHandle picture;
		picture = GetPicture(resID);
		pictRect = (**(picture)).picFrame;

		MacSetRect(&pictRect, 20, 20, 101, 101);
		DrawPicture(picture, &pictRect);


		int tempInt = stoi(_temp);
		std::stringstream fmt;
		fmt << tempInt << "°";
		std::string str = fmt.str();
		const char* blah = str.c_str();

		char* cs;
		cs = (char *)Util::CtoPStr((char*)blah);

		ForeColor(whiteColor);
		TextSize(24);
		MoveTo(106, 70);
		DrawString((ConstStr255Param)cs);
		ForeColor(blackColor);
	}
}

void Weather::ShowPrefsDialog()
{
	// TODO
}

void Weather::HandlePrefsDialogEvent(EventRecord *eventPtr)
{
	// TODO
}

std::string Weather::GetWeatherIcon(std::string condition)
{
	if(ConditionMatch("Drizzle", condition))
		return "drizzle";

	if(ConditionMatch("Rain", condition))
		return "rain";

	if(ConditionMatch("Snow", condition))
		return "blowing-snow";

	if(ConditionMatch("Snow Grains", condition))
		return "blowing-snow";

	if(ConditionMatch("Ice Crystals", condition))
		return "ice";

	if(ConditionMatch("Ice Pellets", condition))
		return "ice";

	if(ConditionMatch("Hail", condition))
		return "hail";

	if(ConditionMatch("Mist", condition))
		return "fog";

	if(ConditionMatch("Fog", condition))
		return "fog";

	if(ConditionMatch("Fog Patches", condition))
		return "fog";

	if(ConditionMatch("Smoke", condition))
		return "smoke";

	if(ConditionMatch("Volcanic Ash", condition))
		return "dust";

	if(ConditionMatch("Widespread Dust", condition))
		return "dust";

	if(ConditionMatch("Sand", condition))
		return "dust";

	if(ConditionMatch("Haze", condition))
		return "haze";

	if(ConditionMatch("Spray", condition))
		return "sleet";

	if(ConditionMatch("Dust Whirls", condition))
		return "dust";

	if(ConditionMatch("Sandstorm", condition))
		return "dust";

	if(ConditionMatch("Low Drifting Snow", condition))
		return "blowing-snow";

	if(ConditionMatch("Low Drifting Widespread Dust", condition))
		return "dust";

	if(ConditionMatch("Low Drifting Sand", condition))
		return "dust";

	if(ConditionMatch("Blowing Snow", condition))
		return "blowing-snow";

	if(ConditionMatch("Blowing Widespread Dust", condition))
		return "dust";

	if(ConditionMatch("Blowing Sand", condition))
		return "dust";

	if(ConditionMatch("Rain Mist", condition))
		return "rain";

	if(ConditionMatch("Rain Showers", condition))
		return "rain";

	if(ConditionMatch("Snow Showers", condition))
		return "blowing-snow";

	if(ConditionMatch("Snow Blowing Snow Mist", condition))
		return "blowing-snow";

	if(ConditionMatch("Ice Pellet Showers", condition))
		return "ice";

	if(ConditionMatch("Hail Showers", condition))
		return "hail";

	if(ConditionMatch("Small Hail Showers", condition))
		return "hail";

	if(ConditionMatch("Thunderstorm", condition))
		return "severe-thunderstorm";

	if(ConditionMatch("Thunderstorms and Rain", condition))
		return "severe-thunderstorm";

	if(ConditionMatch("Thunderstorms and Snow", condition))
		return "severe-thunderstorm";

	if(ConditionMatch("Thunderstorms and Ice Pellets", condition))
		return "severe-thunderstorm";

	if(ConditionMatch("Thunderstorms with Hail", condition))
		return "severe-thunderstorm";

	if(ConditionMatch("Thunderstorms with Small Hail", condition))
		return "severe-thunderstorm";

	if(ConditionMatch("Freezing Drizzle", condition))
		return "drizzle";

	if(ConditionMatch("Freezing Rain", condition))
		return "rain";

	if(ConditionMatch("Freezing Fog", condition))
		return "fog";

	if (ConditionMatch("Patches of Fog", condition))
		return "fog";

	if (ConditionMatch("Shallow Fog", condition))
		return "fog";

	if (ConditionMatch("Partial Fog", condition))
		return "fog";

	if (ConditionMatch("Overcast", condition))
		return "partly-cloudy";

	if (ConditionMatch("Clear", condition))
		return "mostly-sunny";

	if (ConditionMatch("Partly Cloudy", condition))
		return "partly-cloudy";

	if (ConditionMatch("Mostly Cloudy", condition))
		return "mostly-cloudy";

	if (ConditionMatch("Scattered Clouds", condition))
		return "partly-cloudy";

	if (ConditionMatch("Small Hail", condition))
		return "hail";

	if (ConditionMatch("Squalls", condition))
		return "heavy-rain";

	if (ConditionMatch("Funnel Cloud", condition))
		return "partly-cloudy";

	return "no-report";
}

Boolean Weather::ConditionMatch(std::string condition, std::string matchTo)
{
	return (
		condition == matchTo ||
		"Light " + condition == matchTo ||
		"Heavy " + condition == matchTo);
}