#include <Lists.h>
#include <json/json.h>
#include "ModuleManager.h"

class Prefs
{
public:
	Prefs(ModuleManager* moduleManager);
	static Json::Value Data;
	
	static void Save();
	void ShowWindow();
	void Update();
	void HandleEvent(EventRecord* event);
	DialogPtr GetWindow();
private:
	ModuleManager* _manager;
	DialogPtr _dialog;
	ListHandle _allAccounts;
	ListHandle _userAccounts;
	static Json::Value Get();
	static bool GetPrefsSpec(FSSpec *theSpec);
	ListHandle MyCreateVerticallyScrollingList(WindowPtr myWindow,
		Rect myRect,
		int columnsInList,
		int myLDEF,
		short cellWidth,
		short cellHeight);
	void MyDrawListBorder(ListHandle myList);
	void MyAddItemsFromStringList(ListHandle myList);
	void MyAddItemsFromIconList(ListHandle myList);
};