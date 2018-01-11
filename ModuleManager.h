#include <Dialogs.h>
#include <string>
#include <vector>
#include <memory>
#include "Module.h"

#ifndef _MODULE_MANAGER_
#define _MODULE_MANAGER_
class ModuleManager
{
public:
	std::vector<std::unique_ptr<Module>> Modules;
	void Init();
	void HandleEvent(EventRecord *eventPtr);
private:
	void HandleMouseDown(EventRecord *eventPtr);
	void HandleUpdate(EventRecord *eventPtr);
	void Update(WindowPtr windowPtr);
};
#endif // _MODULE_MANAGER_ 
