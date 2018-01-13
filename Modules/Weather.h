#include <string>

#ifndef _MODULE_
#include "Module.h"
#endif

class Weather : public Module
{
public:
	Weather();
	virtual std::string GetId();
	virtual std::string GetName();
	virtual void Init();
	virtual void Update();
	virtual void ShowPrefsDialog();
	virtual void HandlePrefsDialogEvent(EventRecord *eventPtr);

private:
	std::string GetWeatherIcon(std::string condition);
	Boolean ConditionMatch(std::string condition, std::string matchTo);
		
	bool _parseSuccess;
	std::string _temp;
	std::string _condition;
};