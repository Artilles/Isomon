#pragma once
#define GLFW_INCLUDE_GLU
#include "AlertMessage.h"
#include "GameFont.h"
//#include "include\database_types.h"
//#include "include\engine_types.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"


struct MONSTERACTUAL;
struct TYPE;
struct ATTACK;
struct ITEM;

class OverworldMenu
{
public:
	OverworldMenu();
	~OverworldMenu();

	void update(vector<MONSTERACTUAL> playerteamW);
	void render(vector<MONSTERACTUAL> playerteamW, int playerindexW, vector<TYPE> typesW, vector<ATTACK> attacksW, vector<ITEM> items);

	void close();

private:
	GameFont* font;
	AlertMessage* alert;

	short int _selected;
	short int _itemSelected;
	short int _infoSelected;
	short int _monsterNumber;
	int _lastKey;
	bool _monsterWindow;
	bool _itemWindow;

	void select();
	void selectItem();
	void selectInfo();
};

