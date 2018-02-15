#include <Lists.h>
#include <Quickdraw.h>
#include <Dialogs.h>
#include <Fonts.h>
#include <Resources.h>
#include <Sound.h>
#include <memory>
#include "ModuleManager.h"
#include "Prefs.h"
#include "Comms.h"
#include "Modules/Weather.h"
#include "Modules/Facebook.h"
#include "Modules/Google.h"
#include "Util.h"

void InitToolBox();
void InitModules();
void InitWindow();
void InitCustomLDEF();
void EventLoop();
void DoEvent(EventRecord *eventPtr);
void HandleMouseDown(EventRecord *eventPtr); 
void HandleInContent(EventRecord *eventPtr);
void HandleUpdate(EventRecord *eventPtr);
void HandleActivate(EventRecord *eventPtr);
void HandleOSEvt(EventRecord *eventPtr);

extern "C"
{
	extern pascal void IconListDef(short message, Boolean selected, Rect* cellRect, Cell cell, short dataOffset, short dataLen, ListHandle list);
}

WindowRef _window;
Weather _weather;
ModuleManager _manager;
Prefs _prefs(&_manager);
bool _done = false;

int main()
{
	InitToolBox();
	InitModules();
	InitWindow();
	EventLoop();
	return 0;
}

void InitToolBox()
{
	InitGraf(&qd.thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(NULL);
	InitCustomLDEF();
	InitCursor();
}

void InitModules()
{
	// Add available modules
	_manager.Modules.push_back(std::make_unique<Facebook>());
	_manager.Modules.push_back(std::make_unique<Google>());
	//_manager.Modules.push_back(std::make_unique<Weather>());
}

void InitWindow()
{
	//Rect mBarRect;
	//RgnHandle mBarRgn;
	//
	//_window = NewWindow(nil, &(qd.screenBits.bounds), "\p", true, plainDBox, (WindowPtr)-1L, false, (long)nil);

	//MacSetRect(&mBarRect,
	//	qd.screenBits.bounds.left,
	//	qd.screenBits.bounds.top,
	//	qd.screenBits.bounds.right,
	//	qd.screenBits.bounds.top + GetMBarHeight());
	//mBarRgn = NewRgn();
	//RectRgn(mBarRgn, &mBarRect);
	//MacUnionRgn(_window->visRgn, mBarRgn, _window->visRgn);
	//DisposeRgn(mBarRgn);
	//
	//_manager.Init();
	_prefs.ShowWindow();
}

void EventLoop()
{
	EventRecord event;
	int sleep = 60;

	while (_prefs.Active())
	{
		if (WaitNextEvent(everyEvent, &event, sleep, NULL))
		{
			DoEvent(&event);
		}
		else
		{
			Comms::Http.ProcessRequests();
		}
	}
}

void DoEvent(EventRecord *eventPtr)
{
	switch (eventPtr->what)
	{
		case mouseDown:
			HandleMouseDown(eventPtr);
			break;

		case updateEvt:
			HandleUpdate(eventPtr);
			break;

		case activateEvt:
			HandleActivate(eventPtr);
			break;

		case osEvt:
			HandleOSEvt(eventPtr);
			break;
	}
}

void HandleMouseDown(EventRecord *eventPtr)
{
	WindowPtr window;
	short int part;

	part = FindWindow(eventPtr->where, &window);

	switch (part)
	{
		case inContent:
			if (window != FrontWindow())
				SysBeep(10);
			else
				HandleInContent(eventPtr);
			break;

		case inDrag:
			if (window != FrontWindow())
				SysBeep(10);
			else
				DragWindow(window, eventPtr->where, &qd.screenBits.bounds);
			break;

		case inGoAway:
			if (TrackGoAway(window, eventPtr->where))
			{
				_prefs.CloseWindow();
			}
			break;
	}
}

void HandleInContent(EventRecord *eventPtr)
{
	WindowPtr windowPtr;
	FindWindow(eventPtr->where, &windowPtr);

	if (!IsDialogEvent(eventPtr))
	{
		// Temporary: Close app on main window click
		_done = true;
	}
	else
	{
		if (windowPtr == _prefs.GetWindow())
		{
			_prefs.HandleEvent(eventPtr);
		}
		else
		{
			_manager.HandleEvent(eventPtr);
		}
	}
}

void HandleUpdate(EventRecord *eventPtr)
{
	WindowPtr windowPtr = (WindowPtr)eventPtr->message;

	if (windowPtr == _prefs.GetWindow())
	{
		_prefs.Update();
	}
	else
	{
		_manager.HandleEvent(eventPtr);
	}
}

void HandleActivate(EventRecord *eventPtr)
{
	WindowPtr windowPtr = (WindowPtr)eventPtr->message;

	if (windowPtr == _prefs.GetWindow())
	{
		bool becomingActive = (eventPtr->modifiers & activeFlag) == activeFlag;
		_prefs.Activate(becomingActive);
	}
}

void HandleOSEvt(EventRecord *eventPtr)
{
	switch ((eventPtr->message >> 24) & 0x000000FF)
	{
		case suspendResumeMessage:
			bool becomingActive = (eventPtr->message & resumeFlag) == 1;
			_prefs.Activate(becomingActive);
			break;
	}
}

void InitCustomLDEF()
{
	/* The 10-byte code resource stub trick.
	*
	* The bytes in this resource are 68K machine code for
	*     move.l L1(pc), -(sp)    | 2F3A 0004
	*     rts                     | 4E75
	* L1: dc.l 0x00000000         | 0000 0000
	*
	* The application loads this resource and replaces the final four bytes
	* with the address of MyWindowDefProc.
	*/

	Handle h = GetResource('LDEF', 128);
	HLock(h);
	*(ListDefProcPtr*)(*h + 6) = &IconListDef;
}