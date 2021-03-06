#include <string.h>
#include <Folders.h>
#include <Resources.h>
#include <Dialogs.h>
#include <Quickdraw.h>
#include <string>
#include "Prefs.h"
#include "Util.h"
#include "IconListDef.h"

Json::Value Prefs::Data = Get();

Prefs::Prefs(ModuleManager* moduleManager)
{
	_active = true;
	_manager = moduleManager;
}

void Prefs::ShowWindow()
{
	DialogItemType type;
	Handle itemH;
	Rect box;

	_dialog = GetNewDialog(128, 0, (WindowPtr)-1);
	MacSetPort(_dialog);

	// Deactivate Add & Remove buttons by default
	GetDialogItem(_dialog, 3, &type, &itemH, &box);
	HiliteControl((ControlRef)itemH, 255);
	GetDialogItem(_dialog, 4, &type, &itemH, &box);
	HiliteControl((ControlRef)itemH, 255);

	// Initialise lists
	GetDialogItem(_dialog, 1, &type, &itemH, &box);
	_allAccounts = CreateList(_dialog, box, 4, 128, 56, 56);
	PopulateAccountList();

	GetDialogItem(_dialog, 2, &type, &itemH, &box);
	_userAccounts = CreateList(_dialog, box, 1, 0, 0, 0);
	PopulateUserAccountList();
}

DialogPtr Prefs::GetWindow()
{
	return _dialog;
}

void Prefs::HandleEvent(EventRecord* eventPtr)
{
	short int item;
	DialogRef dialogRef;
	DialogItemType type;
	Handle itemH;
	Rect box;
	Point pt;

	if (DialogSelect(eventPtr, &dialogRef, &item))
	{
		MacSetPort(_dialog);

		switch (item)
		{
			case 1:
			{
				// All Accounts List
				GetMouse(&pt);

				// Deactivate any user account selection
				LSetSelect(false, LLastClick(_userAccounts), _userAccounts);
				GetDialogItem(_dialog, 4, &type, &itemH, &box);
				HiliteControl((ControlRef)itemH, 255);

				// Activate cell & add account button
				bool dblClick = LClick(pt, 0, _allAccounts);
				Cell cell = LLastClick(_allAccounts);
				short cellIndex = (cell.v * _allAccountColumns) + cell.h;
				GetDialogItem(_dialog, 3, &type, &itemH, &box);

				if (cellIndex < _manager->Modules.size() &&
					!UserAccountExists(_manager->Modules[cellIndex]->GetId()))
				{
					HiliteControl((ControlRef)itemH, 0);

					if (dblClick)
					{
						_manager->Modules[cellIndex]->ShowPrefsDialog();
					}
				}
				else
				{
					HiliteControl((ControlRef)itemH, 255);
				}
				break;
			}

			case 2:
			{
				// User Accounts List
				GetMouse(&pt);

				// Deactivate any account selection
				LSetSelect(false, LLastClick(_allAccounts), _allAccounts);
				GetDialogItem(_dialog, 3, &type, &itemH, &box);
				HiliteControl((ControlRef)itemH, 255);

				// Activate cell & remove account button
				bool dblClick = LClick(pt, 0, _userAccounts);
				Cell cell = LLastClick(_userAccounts);
				short cellIndex = cell.v;
				GetDialogItem(_dialog, 4, &type, &itemH, &box);

				if (cellIndex < Prefs::Data["accounts"].size())
				{
					HiliteControl((ControlRef)itemH, 0);
				}
				else
				{
					HiliteControl((ControlRef)itemH, 255);
				}
				break;
			}

			case 3:
			{
				// Add Account button
				Cell cell = LLastClick(_allAccounts);
				short cellIndex = (cell.v * _allAccountColumns) + cell.h;
				_manager->Modules[cellIndex]->ShowPrefsDialog();
				break;
			}

			case 4:
			{
				// Remove Account button
				if (NoteAlert(134, nil) == 1)
				{
					Cell cell = LLastClick(_userAccounts);
					short cellIndex = cell.v;
					RemoveAccount(cellIndex);
				}

				GetDialogItem(_dialog, 4, &type, &itemH, &box);
				HiliteControl((ControlRef)itemH, 255);
				break;
			}
		}
	}
}

void Prefs::CloseWindow()
{
	LDispose(_allAccounts);
	LDispose(_userAccounts);
	DisposeDialog(_dialog);
	_active = false;
}

bool Prefs::Active()
{
	return _active;
}

void Prefs::Update()
{
	MacSetPort(_dialog);

	BeginUpdate(_dialog);

	DrawListBorder(_allAccounts);
	DrawListBorder(_userAccounts);

	LUpdate(_dialog->visRgn, _allAccounts);
	LUpdate(_dialog->visRgn, _userAccounts);

	// Update DITL elements
	UpdateDialog(_dialog, _dialog->visRgn);

	EndUpdate(_dialog);
}

void Prefs::Activate(bool becomingActive)
{
	DialogItemType type;
	Handle itemH;
	Rect box;

	MacSetPort(_dialog);

	// Deactivate all selections
	LSetSelect(false, LLastClick(_userAccounts), _userAccounts);
	GetDialogItem(_dialog, 4, &type, &itemH, &box);
	HiliteControl((ControlRef)itemH, 255);

	LSetSelect(false, LLastClick(_allAccounts), _allAccounts);
	GetDialogItem(_dialog, 3, &type, &itemH, &box);
	HiliteControl((ControlRef)itemH, 255);

	if (becomingActive)
	{
		// Refresh user account list
		PopulateUserAccountList();
		InvalRect(&(*_userAccounts)->rView);
	}
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

bool Prefs::Save()
{
	FSSpec fsSpec;
	short file;
	OSErr err;

	Json::StreamWriterBuilder wbuilder;
	std::string outputConfig = Json::writeString(wbuilder, Data);
	const char* prefs = outputConfig.c_str();
	long size = strlen(prefs);

	if (GetPrefsSpec(&fsSpec)) {
		err = FSpOpenDF(&fsSpec, fsRdWrPerm, &file);
		if (err != noErr) {
			if ((err = FSpCreate(&fsSpec, 'MHUB', 'pref', 0)) == noErr)
				err = FSpOpenDF(&fsSpec, fsRdWrPerm, &file);
		}
		if (err == noErr) {
			if (SetEOF(file, 0L) == noErr) {
				if (FSWrite(file, &size, prefs) == noErr) {
					FSClose(file);
					return true;
				}

				FSClose(file);
			}
		}
	}

	ParamText("\pAn error occurred saving preferences.", nil, nil, nil);
	StopAlert(131, nil);
	return false;
}

bool Prefs::GetPrefsSpec(FSSpec *theSpec)
{
	Str255 prefsName = "\pMacHub Preferences";
	short vRefNum;
	long dirID;

	if (FindFolder(kOnSystemDisk, kPreferencesFolderType, kCreateFolder, &vRefNum, &dirID) == noErr) {
		FSMakeFSSpec(vRefNum, dirID, prefsName, theSpec);
		return true;
	}

	return false;
}

ListHandle Prefs::CreateList(
	WindowPtr windowPtr,
	Rect rect,
	int columnsInList,
	int ldef,
	short cellWidth,
	short cellHeight)
{
	bool doDraw = true;
	bool noGrow = false;
	bool includeScrollBar = true;
	int scrollBarWidth = 15;
	Rect myDataBounds;
	Point myCellSize;

	MacSetRect(&myDataBounds, 0, 0, columnsInList, 0);
	SetPt(&myCellSize, cellWidth, cellHeight);
	rect.right = rect.right - scrollBarWidth;

	return
		LNew(&rect, &myDataBounds, myCellSize, ldef, windowPtr,
			doDraw, noGrow, !includeScrollBar,
			includeScrollBar);
}

void Prefs::DrawListBorder(ListHandle myList)
{
	Rect border;
	PenState penState;

	border = (*myList)->rView;
	GetPenState(&penState);
	PenSize(1, 1);
	InsetRect(&border, -1, -1);
	FrameRect(&border);
	SetPenState(&penState);
}

void Prefs::PopulateUserAccountList()
{
	int rowNum;
	Cell aCell;

	LDelRow(0, 1, _userAccounts);

	rowNum = (*_userAccounts)->dataBounds.bottom;
	Json::Value accounts = Prefs::Data["accounts"];

	for (int i = 0; i < accounts.size(); ++i)
	{
		std::string name =
			_manager->GetModuleName(accounts[i]["type"].asString()) +
			" - " + accounts[i]["name"].asString();

		const char* cName = name.c_str();

		LAddRow(1, rowNum, _userAccounts);
		SetPt(&aCell, 0, rowNum);
		LSetCell(cName, strlen(cName), aCell, _userAccounts);
		rowNum = rowNum + 1;
	}
}

void Prefs::PopulateAccountList()
{
	int rowNum, colNum, icons, i = 0;
	
	icons = _manager->Modules.size();
	colNum = (**_allAccounts).dataBounds.right;
	rowNum = (icons + (colNum - 1)) / colNum;

	LAddRow(rowNum, 0, _allAccounts);

	for (std::vector<std::unique_ptr<Module>>::iterator it = _manager->Modules.begin(); it != _manager->Modules.end(); ++it)
	{
		ListIcon listIcon;
		Cell cell;

		cell.v = i / colNum;
		cell.h = i % colNum;

		std::string moduleIcon = (*it)->GetId();
		std::string moduleLabel = " " + (*it)->GetName() + " ";

		char* pModuleIcon;
		pModuleIcon = (char *)Util::CtoPStr((char*)moduleIcon.c_str());

		short resID;
		Str255 resName;
		ResType resType;
		Handle iconRes = GetNamedResource('ICN#', (ConstStr255Param)pModuleIcon);
		GetResInfo(iconRes, &resID, &resType, resName);

		char* pLabel;
		pLabel = (char*)Util::CtoPStr((char*)moduleLabel.c_str());

		listIcon.recourceId = resID;
		strncpy((char*)listIcon.label, pLabel, 256);

		LSetCell(&listIcon, sizeof(ListIcon), cell, _allAccounts);
		i++;
	}
}

void Prefs::RemoveAccount(short index)
{
	Json::Value removed;

	Prefs::Data["accounts"].removeIndex(index, &removed);
	Prefs::Save();
}

bool Prefs::UserAccountExists(std::string type)
{
	Json::Value accounts = Prefs::Data["accounts"];

	for (int i = 0; i < accounts.size(); ++i)
	{
		if (accounts[i]["type"].asString() == type)
		{
			return true;
		}
	}

	return false;
}