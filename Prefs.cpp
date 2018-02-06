#include <ctype.h>
#include <string.h>
#include <Types.h>
#include <Folders.h>
#include <Files.h>
#include <Errors.h>
#include <TextUtils.h>
#include <Resources.h>
#include <Dialogs.h>
#include <Quickdraw.h>
#include <string>
#include "Prefs.h"
#include "Util.h"


void MyAddIconToList(Rect myCellRect, Rect myPlotRect, Cell myCell, ListHandle theList, PicHandle myPicHandle, int resID);

Json::Value Prefs::Data = Get();

Prefs::Prefs(ModuleManager* moduleManager)
{
	_manager = moduleManager;
}

void Prefs::ShowWindow()
{
	_dialog = GetNewDialog(128, 0, (WindowPtr)-1);
	MacSetPort(_dialog);
	SetWRefCon(_dialog, (long)this);

	// Get user item for list
	DialogItemType type;
	Handle itemH;
	Rect box;
	GetDialogItem(_dialog, 2, &type, &itemH, &box);

	_allAccounts = MyCreateVerticallyScrollingList(_dialog, box, 4, 128, 32, 32);

	MyAddItemsFromIconList(_allAccounts);

	DialogItemType type2;
	Handle itemH2;
	Rect box2;
	GetDialogItem(_dialog, 3, &type2, &itemH2, &box2);

	_userAccounts = MyCreateVerticallyScrollingList(_dialog, box2, 1, 0, 0, 0);

	MyAddItemsFromStringList(_userAccounts);

	Update(); // Remove me?
}

DialogPtr Prefs::GetWindow()
{
	return _dialog;
}

void Prefs::HandleEvent(EventRecord* eventPtr)
{
	short int item;
	DialogRef dialogRef;

	if (DialogSelect(eventPtr, &dialogRef, &item))
	{
		MacSetPort(_dialog);

		switch (item)
		{
		case 2:
			Point pt;
			GetMouse(&pt);
			if (LClick(pt, 0, _allAccounts))
			{
				Cell cell = LLastClick(_allAccounts);

				short cellIndex = cell.h; // TODO: Will fail after 4

				if (_manager->Modules.size() > cellIndex)
				{
					_manager->Modules[cellIndex]->ShowPrefsDialog();
				}
			}
			break;

		case 3:
			Point pt2;
			GetMouse(&pt2);
			if (LClick(pt2, 0, _userAccounts))
			{
				// Double clicked..
			}
			break;

		case 6:
			LDispose(_allAccounts);
			LDispose(_userAccounts);
			DisposeDialog(_dialog);
			break;
		}
	}
}

void Prefs::Update()
{
	BeginUpdate(_dialog);

	MacSetPort(_dialog);

	MyDrawListBorder(_allAccounts);


	MyDrawListBorder(_userAccounts);


	LUpdate(_dialog->visRgn, _allAccounts);
	LUpdate(_dialog->visRgn, _userAccounts);

	// Frame border default button
	DialogItemType type;
	Handle itemH;
	Rect box;

	GetDialogItem(_dialog, 6, &type, &itemH, &box);
	InsetRect(&box, -4, -4);
	PenSize(3, 3);
	FrameRoundRect(&box, 16, 16);

	// Update DITL elements
	UpdateDialog(_dialog, _dialog->visRgn);

	EndUpdate(_dialog);
}

Json::Value Prefs::Get()
{
	long theSize = 0, start = 0;
	FSSpec theSpec;
	short theFile;
	OSErr err;

	char buf[8192];
	Json::Value root;

	if (GetPrefsSpec(&theSpec)) 
	{
		if (FSpOpenDF(&theSpec, fsRdPerm, &theFile) == noErr) 
		{
			theSize = sizeof(buf);
			err = FSRead(theFile, &theSize, &buf);
				
			if (err == noErr || err == eofErr)
			{
				Json::Reader reader;
				bool parsingSuccessful = reader.parse(buf, root);
			}

			FSClose(theFile);
		}
	}

	return root;
}

void Prefs::Save()
{
	Json::StreamWriterBuilder wbuilder;
	// Configure the Builder, then ...
	std::string outputConfig = Json::writeString(wbuilder, Data);


	const char* prefs = outputConfig.c_str();
	long theSize = strlen(prefs);
	FSSpec theSpec;
	short theFile;
	OSErr theErr;

	if (GetPrefsSpec(&theSpec)) {
		theErr = FSpOpenDF(&theSpec, fsRdWrPerm, &theFile);
		if (theErr != noErr) {
			if ((theErr = FSpCreate(&theSpec, 'MHUB', 'pref', 0)) == noErr)
				theErr = FSpOpenDF(&theSpec, fsRdWrPerm, &theFile);
		}
		if (theErr == noErr) {
			if (SetEOF(theFile, 0L) == noErr) {
				if (FSWrite(theFile, &theSize, prefs) == noErr) {
					FSClose(theFile);
					return;
				}
				//else MinorError(errCantWritePrefs);
				FSClose(theFile);
			}
			//else MinorError(errCantWritePrefs);
			//FSpDelete(&theSpec);
		}
		//else MinorError(errCantWritePrefs);
	}
	//else MinorError(errCantWritePrefs);
}

bool Prefs::GetPrefsSpec(FSSpec *theSpec)
{
	Str255     prefsName = "\pMacHub Preferences";
	short vRefNum;
	long dirID;

	if (FindFolder(kOnSystemDisk, kPreferencesFolderType, kCreateFolder, &vRefNum, &dirID) == noErr) {
		FSMakeFSSpec(vRefNum, dirID, prefsName, theSpec);
		return true;
	}

	return false;
}

ListHandle Prefs::MyCreateVerticallyScrollingList(WindowPtr myWindow,
	Rect myRect,
	int columnsInList,
	int myLDEF,
	short cellWidth,
	short cellHeight)
{
	bool kDoDraw = TRUE; //{always draw list after changes}
	bool kNoGrow = FALSE; //{don't leave room for size box}
	bool kIncludeScrollBar = TRUE; //{leave room for scroll bar}
	int kScrollBarWidth = 15; //{width of vertical scroll bar}

	Rect myDataBounds; //{initial dimensions of the list}
	Point myCellSize; //{size of each cell in list}

					  // { specify dimensions of the list }
					  // {start with a list that contains no rows}

	MacSetRect(&myDataBounds, 0, 0, columnsInList, 0);

	// {let the List Manager calculate the size of a cell}
	SetPt(&myCellSize, cellWidth, cellHeight);

	// {adjust the rectangle to leave room for the scroll bar}
	myRect.right = myRect.right - kScrollBarWidth;

	// {create the list}
	return
		LNew(&myRect, &myDataBounds, myCellSize, myLDEF, myWindow,
			kDoDraw, kNoGrow, !kIncludeScrollBar,
			kIncludeScrollBar);
}

void Prefs::MyDrawListBorder(ListHandle myList)
{
	Rect myBorder; // {box for list}
	PenState myPenState; //{current status of pen}

	myBorder = (*myList)->rView; //{get view rectangle}
	GetPenState(&myPenState); //{store pen state}
	PenSize(1, 1); //{set pen to 1 pixel}
	InsetRect(&myBorder, -1, -1); //{adjust rectangle for framing}
	FrameRect(&myBorder);// {draw border}
	SetPenState(&myPenState);//{restore old pen state}
}

void Prefs::MyAddItemsFromStringList(ListHandle myList)
{
	int rowNum;
	Cell aCell;

	rowNum = (*myList)->dataBounds.bottom;

	Json::Value accounts = Prefs::Data["accounts"];

	for (int i = 0; i < accounts.size(); ++i)
	{
		std::string name =
			_manager->GetModuleName(accounts[i]["type"].asString()) +
			" (" + accounts[i]["name"].asString() + ")";

		const char* cName = name.c_str();

		LAddRow(1, rowNum, myList);
		SetPt(&aCell, 0, rowNum);
		LSetCell(cName, strlen(cName), aCell, myList);
		rowNum = rowNum + 1;
	}
}

void Prefs::MyAddItemsFromIconList(ListHandle myList)
{
	int rowNum, colNum, icons, i = 0;
	Cell aCell;

	icons = _manager->Modules.size();
	colNum = (**myList).dataBounds.right;
	rowNum = (icons + (colNum - 1)) / colNum;

	LAddRow(rowNum, 0, myList);

	for (std::vector<std::unique_ptr<Module>>::iterator it = _manager->Modules.begin(); it != _manager->Modules.end(); ++it)
	{
		aCell.v = i / colNum;
		aCell.h = i % colNum;

		std::string moduleIcon = (*it)->GetId();

		if (!Util::HasColour())
		{
			moduleIcon = "bw-" + moduleIcon;
		}

		char* pModuleIcon;
		pModuleIcon = (char *)Util::CtoPStr((char*)moduleIcon.c_str());

		Handle iconRes;
		short resID;
		ResType theResType;
		unsigned char resName[256];

		iconRes = GetNamedResource('PICT', (ConstStr255Param)pModuleIcon);
		GetResInfo(iconRes, &resID, &theResType, resName);


		PicHandle picture;
		Rect   rect;
		Rect   plotRect;

		MyAddIconToList(rect, plotRect, aCell, myList, picture, resID);

		i++;

	}
}

void MyAddIconToList(Rect myCellRect, Rect myPlotRect, Cell myCell, ListHandle theList, PicHandle myPicHandle, int resID)
{
	const int kIconWidth = 32; // width of an icon
	const int kIconHeight = 32; // height of an icon
	const int kExtraSpace = 2; // extra space on top and to left of icon

							   //CIconHandle myIcon;

							   // picture occupies entire cell rectangle
	MacSetRect(&myCellRect, 0, 0, kIconWidth + kExtraSpace, kIconHeight + kExtraSpace);

	// plot icon over portion of rectangle
	MacSetRect(&myPlotRect, kExtraSpace, kExtraSpace, kIconWidth + kExtraSpace, kIconHeight + kExtraSpace);

	// load icon from resource file
	//myIcon = GetCIcon(resID);

	Rect pictRect;
	PicHandle picture;
	picture = GetPicture(resID);

	// create the picture
	myPicHandle = OpenPicture(&myCellRect);
	DrawPicture(picture, &myPlotRect);
	ClosePicture();

	// store handle to picture as cell data
	LSetCell(&myPicHandle, sizeof(PicHandle), myCell, theList);

	// release icon resource
	//ReleaseResource((Handle)myIcon);
}