#include <string>
#include <Events.h>

#ifndef _MODULE_
#define _MODULE_

class Module
{
public:
	DialogPtr PrefsDialog = 0;
	virtual std::string GetId() = 0;
	virtual std::string GetName() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void ShowPrefsDialog() = 0;
	virtual void UpdatePrefsDialog() = 0;
	virtual void HandlePrefsDialogEvent(EventRecord *eventPtr) = 0;
};

#endif // _MODULE_ 