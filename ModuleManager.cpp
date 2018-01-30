#include <Windows.h>
#include "ModuleManager.h"

void ModuleManager::Init()
{
	for (std::vector<std::unique_ptr<Module>>::iterator it = Modules.begin(); it != Modules.end(); ++it)
	{
		(*it)->Init();
	}
}

void ModuleManager::HandleEvent(EventRecord *eventPtr)
{
	switch (eventPtr->what)
	{
		case mouseDown:
			HandleMouseDown(eventPtr);
			break;

		case updateEvt:
			HandleUpdate(eventPtr);
			break;
	}
}

void ModuleManager::HandleMouseDown(EventRecord *eventPtr)
{
	WindowPtr windowPtr;
	FindWindow(eventPtr->where, &windowPtr);

	if (!IsDialogEvent(eventPtr))
	{
		//
	}
	else
	{
		for (std::vector<std::unique_ptr<Module>>::iterator it = Modules.begin(); it != Modules.end(); ++it)
		{
			if (windowPtr == (*it)->PrefsDialog)
			{
				(*it)->HandlePrefsDialogEvent(eventPtr);
				break;
			}
		}
	}
}

void ModuleManager::HandleUpdate(EventRecord *eventPtr)
{
	WindowPtr windowPtr = (WindowPtr)eventPtr->message;
	DialogRef dialogRef;
	SInt16    itemHit;

	if (!IsDialogEvent(eventPtr))
	{
		Update(windowPtr);
	}
	else
	{
		for (std::vector<std::unique_ptr<Module>>::iterator it = Modules.begin(); it != Modules.end(); ++it)
		{
			if (windowPtr == (*it)->PrefsDialog)
			{
				(*it)->UpdatePrefsDialog();
				break;
			}
		}
	}
}

void ModuleManager::Update(WindowPtr windowPtr)
{
	BeginUpdate(windowPtr);
	MacSetPort(windowPtr);
	MacFillRect(&(windowPtr->portRect), &qd.black);

	short fontNum;
	GetFNum("\pSF Pro Display", &fontNum);

	if (fontNum != 0)
		TextFont(fontNum);

	for (std::vector<std::unique_ptr<Module>>::iterator it = Modules.begin(); it != Modules.end(); ++it)
	{
		(*it)->Update();
	}

	ForeColor(whiteColor);
	TextSize(48);

	short strWidth;
	strWidth = StringWidth("\p8:20 pm");


	MoveTo(qd.screenBits.bounds.right - strWidth - 20, 80);
	DrawString("\p8:20 pm");
	ForeColor(blackColor);
	EndUpdate(windowPtr);
}