#ifndef _FACEBOOK_
#define _FACEBOOK_
#endif

#ifndef _MODULE_
#include "Module.h"
#endif

class Facebook : public Module
{
public:
	Facebook();
	virtual std::string GetId();
	virtual std::string GetName();
	virtual void Init();
	virtual void Update();
	virtual void ShowPrefsDialog();
	virtual void HandlePrefsDialogEvent(EventRecord *eventPtr);
private:
	void CheckUserCode();
};