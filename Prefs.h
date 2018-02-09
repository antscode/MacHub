#include <Lists.h>
#include <json/json.h>
#include "ModuleManager.h"

class Prefs
{
public:
	Prefs(ModuleManager* moduleManager);
	static Json::Value Data;
	static bool Save();
	void ShowWindow();
	void CloseWindow();
	void Update();
	void Activate(bool becomingActive);
	void HandleEvent(EventRecord* event);
	DialogPtr GetWindow();
	bool Active();
private:
	const int _allAccountColumns = 4;
	bool _active;
	ModuleManager* _manager;
	DialogPtr _dialog;
	ListHandle _allAccounts;
	ListHandle _userAccounts;
	static Json::Value Get();
	static bool GetPrefsSpec(FSSpec *theSpec);
	ListHandle CreateList(
		WindowPtr windowPtr,
		Rect rect,
		int columnsInList,
		int ldef,
		short cellWidth,
		short cellHeight);
	void DrawListBorder(ListHandle myList);
	void PopulateAccountList();
	void PopulateUserAccountList();
	void AddIconToList(
		Rect cellRect, 
		Rect plotRect, 
		Cell cell, 
		ListHandle list, 
		PicHandle picHandle, 
		int resID);
	void RemoveAccount(short index);
	bool UserAccountExists(std::string type);
};