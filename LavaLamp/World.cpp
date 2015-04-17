#pragma once
#pragma comment(lib, "winmm.lib") 

#include "include\World.h"
#include "include\MenuState.h"
#define _WIN32_WINNT _WIN32_WINNT_WINXP // Windows XP compatibility macro
#pragma pack(1)   //proper Endian switch
#include <time.h>
#include <stdlib.h>  
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include "include\GLFW\glfw3.h"
#include "database_types.h"
#include "engine_types.h"
#include <windows.h>    
#include "include\GameWindow.h"

int _pauseSelected = 0;
double typesMatchW[12][12] = {
{.5, .5, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1},
{2, .5, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{.5, 2, .5, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, .5, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, .5, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, .5, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, .5, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, .5, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, .5, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, .5, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, .5, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, .5, 0, 1, 1, 1, 1, 1, 1, 1, 1}
};
double enTypOne = 1, enTypeTwo = 1;
double plTypOne = 1, plTypeTwo = 1;


using namespace std;

#pragma region variables
void loadItems();
void selectionUpW();
void selectionDownW();
void selectionLeftW();
void selectionRightW();
void selectW();
void evolve();
void handlePlayerW();
void handleEnemyW();
int _currentSelectionW;
bool caught = false;
int _currentColumnW = 0;
int menuindexW = 0;
int _currentSelectionItemW = 0;
bool musicW = false;
char lW[3];
char attW[15];
char buff[2];
int attchW;
int eattchW;
void attacksSelected();
bool playerlosesW = false;
bool enemylosesW = false;
int attackcountW = 0;
int _lastKeyW = 0;

int frametempW = 0;
int attacktempW = 0;
bool attackingW = false;
bool battlestartW = false;
bool battleoverW = false;
GameFont* fontW;
bool enterW = false;
bool playerMissed = false;
bool enemyMissed = false;
bool run = false;
vector<ITEM> items;
vector<ITEM> itemsHave;

//	bool battlestartW = false;

//Varibales
vector<INDEX> indexesW;
vector<SPECIES> speciesW;
vector<MONSTER> monstersW;
vector<ATTACK> attacksW;
vector<EFFECT> effectsW;
vector<TAMER> tamersW;
vector<MOVESET> movesetsW;
vector<TYPE> typesW;
vector<EVOLUTION> evolutionsW;
vector<CONDITION> conditionsW;
vector<MONSTERACTUAL> playerteamW;
vector<MONSTERACTUAL> enemyteamW;
vector<MONSTERACTUAL> playertotalTeamW;
vector<ENCOUNTER> encountersW;
vector<ENCOUNTERACTUAL> encounterActualsW;
int loadallW();
int loadIndexW();
int loadSpcW();
int loadMstW();
int loadAttW();
int loadEffW();
int loadTmrW();
int loadMvsetW();
int loadTypW();
int loadEvoW();
int loadCndW();
int loadEncW();
void loadPlayer();
bool wild = false;
char*  tamername = "-";
char*  tamerclass = "-";
bool battle;
void loadTamerBattle(int t); //tamerid
void loadWildBattle(int s, int r); //setid, randomnumber
void enemywinsW();
void playerwinsW();
void levelupW();
void reassign(int i);
bool updateBattle();
int playerindexW = 0;
int enemyindexW = 0;
int playerdudesW = 0;
int enemydudesW = 0;
int startingplayerW = 0;
int startingenemyW = 0;
int eattchWran = 0;
Entity* entityW;
Entity* entity2W;
int screenCounter;

// Storage String

char* party0 = "-";
char* party1 = "-";
char* party2 = "-";
int party0ID;
int party1ID;
int party2ID;

int playerAccBuffW = 0;
int playerSpeedBuffW = 0;
int playerDefBuffW = 0;
int playerAttackBuffW = 0;
int enemyAccBuffW = 0;
int enemySpeedBuffW = 0;
int enemyDefBuffW = 0;
int enemyAttackBuffW = 0;


#pragma endregion variables
bool itemmenu = false;


// Static Variable Declarations
#pragma region Static Variables
bool World::_isPaused;
#pragma endregion

void World::setCurrent(int x)
{
	playerindexW = x;
}
string displayHPLVL(int id)
{
	string s = "";
	for (int i = 0; i < playerteamW.size(); i++)
	{
		if (playerteamW[i].mst_id == id)
		{
			ostringstream q;
			q << " " << playerteamW[i].currenthp << "/" << playerteamW[i].hp << "  lvl" << playerteamW[i].mst_level;
			s.append(q.str());
		}
	}
	return s;
}

World::World(void)
{
	loadallW();
	fontW->createFont("Arial 20", "resource/fonts/arial.ttf", 18, 0);
	srand(time(0));
	// Not in a battle
	battle = false;

	// To move world
	camera = new Camera();

	// To create girl
	player = new Player();

	// To draw world (tiles)
	tileManager = new TileManager();

	// Create a 100x100 tile set
	tileManager->createTileSet(100, 100);

	pauseMenu = new OverworldMenu();

	_isPaused = false;
}

World::~World(void)
{
}


void World::update(double currentTime)
{

#pragma region world
	GLFWwindow* window = glfwGetCurrentContext();

	if (!battle && !battlestartW&& !caught)
	{
		camera->update(currentTime);
		player->update(currentTime);
		//tileManager->update(currentTime);

		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		{
			glTranslatef(1.0f, 0, 0);
			//player->dir++;
		}

		// Pause Game
		if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS && _lastKeyW != GLFW_KEY_BACKSPACE)
		{
			if (!_isPaused)
				_isPaused = true;
			else
			{
				pauseMenu->close();
				_isPaused = false;
			}
			_lastKeyW = GLFW_KEY_BACKSPACE;
		}

		if (!_isPaused)
		{
			// player code
			if (!player->moving && !tileManager->moving)
			{
				if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
				{
					player->dir = 3;
				}
				else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
				{
					player->dir = 1;
				}
				else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
				{
					player->dir = 2;
				}
				else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
				{
					player->dir = 0;
				}
				if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS
					&& (player->tileNumber > 0)
					&& (strcmp(tileManager->_tileList[player->tileNumber - 1]._model, "none") == 0))
				{
					if (player->ScreenX > 0)
					{
						player->moveX = -0.01f;
						player->ScreenX--;
					}
					else
					{
						tileManager->moveX = -0.005f;
					}
				}
				else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS
					&& (player->tileNumber < 9999)
					&& (strcmp(tileManager->_tileList[player->tileNumber + 1]._model, "none")) == 0)
				{
					if (player->ScreenX < 3)
					{
						player->moveX = 0.01f;
						player->ScreenX++;
					}
					else
					{
						tileManager->moveX = 0.005f;
					}
				}
				else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS
					&& (player->tileNumber > 99)
					&& strcmp(tileManager->_tileList[player->tileNumber - 100]._model, "none") == 0)
				{
					if (player->ScreenY < 3)
					{
						player->moveZ = -0.01f;
						player->ScreenY++;
					}
					else
					{
						tileManager->moveZ = -0.005f;
					}
				}
				else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS
					&& (player->tileNumber < 9900)
					&& strcmp(tileManager->_tileList[player->tileNumber + 100]._model, "none") == 0)
				{
					if (player->ScreenY > 0)
					{
						player->moveZ = 0.01f;
						player->ScreenY--;
					}
					else
					{
						tileManager->moveZ = 0.005f;
					}
				}
			}
		}
		else
		{
			pauseMenu->update(playerteamW);
		}

		if (player->moveX != 0 || player->moveZ != 0)
		{
			player->moving = true;
			player->x += player->moveX;
			player->z += player->moveZ;
			player->moveDist += player->moveX + player->moveZ;
			if (player->moveX > 0)
			{
				player->GlobalX++;
				//player->LocalX++;
			}
			if (player->moveX<0)
			{
				player->GlobalX--;
				//player->LocalX--;
			}
			if (player->moveZ>0)
			{
				player->GlobalY++;
				//player->LocalY++;			
			}
			if (player->moveZ <0)
			{
				player->GlobalY--;
				//player->LocalY--;
			}
			if (player->moveDist > player->tileDist || player->moveDist < -player->tileDist)
			{
				player->moving = false; player->moveX = 0; player->moveZ = 0; player->moveDist = 0;
				//loadWildBattle(tileManager->_tileList[player->tileNumber + 100]._encounters, rand() % 100 + 1);
				loadWildBattle(tileManager->_tileList[player->tileNumber]._encounters, rand() % 100 + 1);				
			}
		}
		// tiles
		if (tileManager->moveX != 0 || tileManager->moveZ != 0)
		{
			tileManager->moving = true;
			tileManager->x += tileManager->moveX;
			tileManager->z += tileManager->moveZ;
			tileManager->moveDist += tileManager->moveX + tileManager->moveZ;
			if (tileManager->moveX > 0)
			{
				player->GlobalX++;
				//player->x;
			}
			if (tileManager->moveX<0)
			{
				player->GlobalX--;
				//player->x--;
			}
			if (tileManager->moveZ>0)
			{
				player->GlobalY++;
				//player->z++;
			}
			if (tileManager->moveZ <0)
			{
				player->GlobalY--;
				//player->z--;
			}
			if (tileManager->moveDist > tileManager->tileDist || tileManager->moveDist < -tileManager->tileDist)
			{
				tileManager->moving = false; tileManager->moveX = 0; tileManager->moveZ = 0; tileManager->moveDist = 0;
				loadWildBattle(tileManager->_tileList[player->tileNumber]._encounters, rand() % 100 + 1);
			}

		}

		//debug code

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			loadWildBattle(1, rand() % 100 + 1);
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			loadWildBattle(2, rand() % 100 + 1);
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			loadWildBattle(3, rand() % 100 + 1);
		}
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		{
			loadWildBattle(4, rand() % 100 + 1);
		}
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		{
			loadTamerBattle(5);
		}
		if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		{
			loadTamerBattle(2);
		}
		if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		{
			loadTamerBattle(3);
		}
		if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		{
			loadTamerBattle(4);
		}

	}
#pragma endregion world
	if (battlestartW && !battleoverW && !caught)
	{
		//run initial battle code #battlecode
		screenCounter--;
		if (screenCounter <= 0)
		{
			battle = true;
			battlestartW = false;
			string x = playerteamW[playerindexW].spc_model;
			string y = enemyteamW[enemyindexW].spc_model;
			entityW = new Entity(x);
			entity2W = new Entity(y);
			run = false;
		}
	}
	if (!battlestartW && battleoverW && !battle)
	{
		screenCounter--;
		if (screenCounter <= 0)
		{
			battleoverW = false;
			battle = false;
			battlestartW = false;
			playerlosesW = false;
			enemylosesW = false;
			run = false;
			caught = false;
		}

	}
	if (battle)
	{
		//updatebattle
		//loadBattle(1);
		updateBattle();
	}

	// Key Reset0
	if (_lastKeyW != -1)
	{
		if (glfwGetKey(window, _lastKeyW) == GLFW_RELEASE)
			_lastKeyW = -1;
	}
}


bool updateBattle()
{

	//entityW->update(currentTimeW);
	//entity2W->update(currentTimeW);

//	entityW->update();
//	entity2W->update();
	party0 = playerteamW[0].mst_nickname;
	(playerteamW.size() > 1) ? party1 = playerteamW[1].mst_nickname : party1 = "-";
	(playerteamW.size() > 2) ? party2 = playerteamW[2].mst_nickname : party2 = "-";
	party0ID = playerteamW[0].mst_id;
	(playerteamW.size() > 1) ? party1ID = playerteamW[1].mst_id : party1ID = -1;
	(playerteamW.size() > 2) ? party2ID = playerteamW[2].mst_id : party2ID = -1;



	GLFWwindow* window = glfwGetCurrentContext();
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !enterW)
	{
		selectW();
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && _lastKeyW != GLFW_KEY_UP)
	{
		_lastKeyW = GLFW_KEY_UP;
		selectionUpW();
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && _lastKeyW != GLFW_KEY_DOWN)
	{
		_lastKeyW = GLFW_KEY_DOWN;
		selectionDownW();
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && _lastKeyW != GLFW_KEY_LEFT)
	{
		_lastKeyW = GLFW_KEY_LEFT;
		selectionLeftW();
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && _lastKeyW != GLFW_KEY_RIGHT)
	{
		_lastKeyW = GLFW_KEY_RIGHT;
		selectionRightW();
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		enterW = true;
	}
	else
	{
		enterW = false;
	}

	return true;
}


void loadTamerBattle(int t)
{
	wild = false;
	//playerdudesW = playerteamW.size();
	enemyteamW.clear();
	itemsHave.clear();
	for(int i = 0; i < items.size(); i++)
	{
		if(items[i].count>=1)
		{
			itemsHave.push_back(items[i]);
		}
	}
	battle = false;
	battlestartW = false;
	//get tamer id
	int one = tamersW[t].mst_1;
	int two = tamersW[t].mst_2;
	int three = tamersW[t].mst_3;
	tamername = tamersW[t].tmr_name;
	tamerclass = tamersW[t].tmr_title;
	MONSTERACTUAL monactual;
	//get 3 monsters from the tmr_mst_1, etc
	if (one > 0)
	{
		cout << "you loaded: " << monstersW[one - 1].mst_nickname << " the " << speciesW[monstersW[one - 1].spc_id - 1].spc_name << endl << endl;

		monactual.attack = (speciesW[monstersW[one - 1].spc_id - 1].spc_attack * 2 * monstersW[one - 1].mst_level / 100) + 5;
		monactual.defence = (speciesW[monstersW[one - 1].spc_id - 1].spc_defence * 2 * monstersW[one - 1].mst_level / 100) + 5;
		monactual.speed = (speciesW[monstersW[one - 1].spc_id - 1].spc_speed * 2 * monstersW[one - 1].mst_level / 100) + 5;
		monactual.hp = (speciesW[monstersW[one - 1].spc_id - 1].spc_hp * 2 * monstersW[one - 1].mst_level / 100) + 5;
		monactual.currenthp = monactual.hp;
		monactual.mst_id = monstersW[one - 1].mst_id;
		monactual.mst_level = monstersW[one - 1].mst_level;
		strcpy(monactual.mst_nickname, monstersW[one - 1].mst_nickname);
		//monactual.mst_nickname = monsters[one].mst_nickname;
		monactual.typ_1 = speciesW[monstersW[one - 1].spc_id - 1].typ_1;
		monactual.typ_2 = speciesW[monstersW[one - 1].spc_id - 1].typ_2;
		monactual.att_1 = monstersW[one - 1].mst_attack1;
		monactual.att_2 = monstersW[one - 1].mst_attack2;
		monactual.att_3 = monstersW[one - 1].mst_attack3;
		monactual.att_4 = monstersW[one - 1].mst_attack4;
		monactual.cool_1 = 0;
		monactual.cool_2 = 0;
		monactual.cool_3 = 0;
		monactual.cool_4 = 0;
		monactual.spc_id = monstersW[one - 1].spc_id;
		strcpy(monactual.spc_model, speciesW[monstersW[one - 1].spc_id - 1].spc_model);
		//monactual.spc_model = species[monsters[one].spc_id].spc_model;
		strcpy(monactual.spc_name, speciesW[monstersW[one - 1].spc_id - 1].spc_name);
		//monactual.spc_name = species[monsters[one].spc_id].spc_name;
		monactual.mst_xp = (4 * monactual.mst_level *monactual.mst_level*monactual.mst_level) / 5;
		enemyteamW.push_back(monactual);
		startingenemyW++;
	}
	if (two > 0)
	{
		cout << "you loaded: " << monstersW[two - 1].mst_nickname << " the " << speciesW[monstersW[two - 1].spc_id - 1].spc_name << endl << endl;

		monactual.attack = (speciesW[monstersW[two - 1].spc_id - 1].spc_attack * 2 * monstersW[two - 1].mst_level / 100) + 5;
		monactual.defence = (speciesW[monstersW[two - 1].spc_id - 1].spc_defence * 2 * monstersW[two - 1].mst_level / 100) + 5;
		monactual.speed = (speciesW[monstersW[two - 1].spc_id - 1].spc_speed * 2 * monstersW[two - 1].mst_level / 100) + 5;
		monactual.hp = (speciesW[monstersW[two - 1].spc_id - 1].spc_hp * 2 * monstersW[two - 1].mst_level / 100) + 5;
		monactual.currenthp = monactual.hp;
		monactual.mst_id = monstersW[two - 1].mst_id;
		monactual.mst_level = monstersW[two - 1].mst_level;
		strcpy(monactual.mst_nickname, monstersW[two - 1].mst_nickname);
		//monactual.mst_nickname = monsters[two].mst_nickname;
		monactual.typ_1 = speciesW[monstersW[two - 1].spc_id - 1].typ_1;
		monactual.typ_2 = speciesW[monstersW[two - 1].spc_id - 1].typ_2;
		monactual.att_1 = monstersW[two - 1].mst_attack1;
		monactual.att_2 = monstersW[two - 1].mst_attack2;
		monactual.att_3 = monstersW[two - 1].mst_attack3;
		monactual.att_4 = monstersW[two - 1].mst_attack4;
		monactual.cool_1 = 0;
		monactual.cool_2 = 0;
		monactual.cool_3 = 0;
		monactual.cool_4 = 0;
		monactual.spc_id = monstersW[two - 1].spc_id;
		strcpy(monactual.spc_model, speciesW[monstersW[two - 1].spc_id - 1].spc_model);
		//monactual.spc_model = species[monsters[two].spc_id].spc_model;
		strcpy(monactual.spc_name, speciesW[monstersW[two - 1].spc_id - 1].spc_name);
		//monactual.spc_name = species[monsters[two].spc_id].spc_name;
		monactual.mst_xp = (4 * monactual.mst_level *monactual.mst_level*monactual.mst_level) / 5;
		enemyteamW.push_back(monactual);
		startingenemyW++;
	}
	if (three > 0)
	{
		cout << "you loaded: " << monstersW[three - 1].mst_nickname << " the " << speciesW[monstersW[three - 1].spc_id - 1].spc_name << endl << endl;

		monactual.attack = (speciesW[monstersW[three - 1].spc_id - 1].spc_attack * 2 * monstersW[three - 1].mst_level / 100) + 5;
		monactual.defence = (speciesW[monstersW[three - 1].spc_id - 1].spc_defence * 2 * monstersW[three - 1].mst_level / 100) + 5;
		monactual.speed = (speciesW[monstersW[three - 1].spc_id - 1].spc_speed * 2 * monstersW[three - 1].mst_level / 100) + 5;
		monactual.hp = (speciesW[monstersW[three - 1].spc_id - 1].spc_hp * 2 * monstersW[three - 1].mst_level / 100) + 5;
		monactual.currenthp = monactual.hp;
		monactual.mst_id = monstersW[three - 1].mst_id;
		monactual.mst_level = monstersW[three - 1].mst_level;
		strcpy(monactual.mst_nickname, monstersW[three - 1].mst_nickname);
		//monactual.mst_nickname = monsters[three].mst_nickname;
		monactual.typ_1 = speciesW[monstersW[three - 1].spc_id - 1].typ_1;
		monactual.typ_2 = speciesW[monstersW[three - 1].spc_id - 1].typ_2;
		monactual.att_1 = monstersW[three - 1].mst_attack1;
		monactual.att_2 = monstersW[three - 1].mst_attack2;
		monactual.att_3 = monstersW[three - 1].mst_attack3;
		monactual.att_4 = monstersW[three - 1].mst_attack4;
		monactual.cool_1 = 0;
		monactual.cool_2 = 0;
		monactual.cool_3 = 0;
		monactual.cool_4 = 0;
		monactual.spc_id = monstersW[three - 1].spc_id;
		strcpy(monactual.spc_model, speciesW[monstersW[three - 1].spc_id - 1].spc_model);
		//monactual.spc_model = species[monsters[three].spc_id].spc_model;
		strcpy(monactual.spc_name, speciesW[monstersW[three - 1].spc_id - 1].spc_name);
		//monactual.spc_name = species[monsters[three].spc_id].spc_name;
		monactual.mst_xp = (4 * monactual.mst_level *monactual.mst_level*monactual.mst_level) / 5;
		enemyteamW.push_back(monactual);
		startingenemyW++;
	}
	//end
	battlestartW = true;
	screenCounter = 150;
}
void loadWildBattle(int s, int r)
{
	wild = true;
	enemydudesW = 1;
	playerdudesW = startingplayerW;
	vector<int> tempAttacks;
	enemyteamW.clear();
	battle = false;
	battlestartW = false;
	itemsHave.clear();
	for(int i = 0; i < items.size(); i++)
	{
		if(items[i].count>=1)
		{
			itemsHave.push_back(items[i]);
		}
	}
	//cout << r << endl;
	//find encounter set
	///encounterset is w
	ENCOUNTERACTUAL Enc;
	for (int i = 0; i < encounterActualsW.size(); i++)
	{
		if (encounterActualsW[i].enc_id == s)
		{
			Enc = encounterActualsW[i];
		}
	}

	//generate number
	int ee = 0;
	int ea = 0;
	//get species and level
	int wspc = 0;
	//generate monster of species at level
	int wlvl = 0;
	for (int e = 0; e < Enc.species.size(); e++)
	{
		ee += Enc.species[e].enc_rate;
		if (e>0)
		{
			ea += Enc.species[e - 1].enc_rate;
		}
		if (r >= ea && r < ee)
		{
			battlestartW = true;
			wspc = Enc.species[e].spc_id - 1;
			wlvl = Enc.species[e].mst_lvl;
			cout << "battle with " << speciesW[Enc.species[e].spc_id - 1].spc_name << "Level " << wlvl << endl;
			break;
		}
	}

	//generate moveset for monster
	for (int j = 0; j < movesetsW.size(); j++)
	{
		if (movesetsW[j].mst_id == wspc + 1)
		{
			if (movesetsW[j].mv_lev <= wlvl)
			{
				tempAttacks.push_back(movesetsW[j].att_id);
			}
		}
	}




	if (battlestartW)
	{
		startingenemyW = 1;
		enemydudesW = 1;
		enemyindexW = 0;
		enemyteamW.clear();
		//cout<<"you loaded: " << monstersW[one-1].mst_nickname << " the " << speciesW[monstersW[one-1].spc_id-1].spc_name<<endl<<endl;
		MONSTERACTUAL monactual;
		monactual.attack = (speciesW[wspc].spc_attack * 2 * wlvl / 100) + 5;
		monactual.defence = (speciesW[wspc].spc_defence * 2 * wlvl / 100) + 5;
		monactual.speed = (speciesW[wspc].spc_speed * 2 * wlvl / 100) + 5;
		monactual.hp = (speciesW[wspc].spc_hp * 2 * wlvl / 100) + 5;
		monactual.currenthp = monactual.hp;
		monactual.mst_id = monstersW.size() + 1;
		monactual.mst_level = wlvl;
		strcpy(monactual.mst_nickname, speciesW[wspc].spc_name);
		//monactual.mst_nickname = monsters[one].mst_nickname;
		monactual.typ_1 = speciesW[wspc].typ_1;
		monactual.typ_2 = speciesW[wspc].typ_2;
		/*monactual.att_1 = monstersW[one-1].mst_attack1;
		monactual.att_2 = monstersW[one-1].mst_attack2;
		monactual.att_3 = monstersW[one-1].mst_attack3;
		monactual.att_4 = monstersW[one-1].mst_attack4;
		*/
		//generate moveset
		int movesetSize = tempAttacks.size();
		monactual.att_1 = 0;
		monactual.att_2 = 0;
		monactual.att_3 = 0;
		monactual.att_4 = 0;
		monactual.spc_id = wspc;
		if (movesetSize <= 4 && movesetSize > 0)
		{
			if (movesetSize > 0)
			{
				monactual.att_1 = tempAttacks[0];
			}
			if (movesetSize > 1)
			{
				monactual.att_2 = tempAttacks[1];
			}
			if (movesetSize > 2)
			{
				monactual.att_3 = tempAttacks[2];
			}
			if (movesetSize > 3)
			{
				monactual.att_4 = tempAttacks[3];
			}

		}
		else{
			int a, b, c, d;
			a = rand() % movesetSize;
			monactual.att_1 = a;
			b = rand() % movesetSize;
			if (b != a)
			{
				monactual.att_2 = b;
			}
			c = rand() % movesetSize;
			if (c != b && c != a)
			{
				monactual.att_3 = c;
			}
			d = rand() % movesetSize;
			if (d != b && d != a && d != c)
			{
				monactual.att_4 = d;
			}
		}
		monactual.cool_1 = 0;
		monactual.cool_2 = 0;
		monactual.cool_3 = 0;
		monactual.cool_4 = 0;
		strcpy(monactual.spc_model, speciesW[wspc].spc_model);
		//monactual.spc_model = species[monsters[one].spc_id].spc_model;
		strcpy(monactual.spc_name, speciesW[wspc].spc_name);
		//monactual.spc_name = species[monsters[one].spc_id].spc_name;
		monactual.mst_xp = (4 * monactual.mst_level *monactual.mst_level*monactual.mst_level) / 5;
		enemyteamW.push_back(monactual);
		//	battlestartW = true;
		screenCounter = 150;
	}


}


void World::draw()
{
#pragma region worldDraw
	if (!battle)
	{
		glPushMatrix();

		camera->render();

		glScalef(2.2, 2.2, 2.2);
		glPushMatrix();
		tileManager->draw(player->GlobalX / 20, (player->GlobalY) / 20);
		//std::cout << (player->GlobalY - 1) / 20 << " ";
		//glTranslatef(-tileManager->moveX,0,tileManager->moveZ);
		glPopMatrix();
		glScalef(.5, .5, .5);

		player->draw();

		glPopMatrix();

		// Paused Menu
		if (_isPaused)
		{
			pauseMenu->render(playerteamW, playerindexW, typesW, attacksW, itemsHave);
		}
	}
#pragma endregion worldDraw
#pragma region BattleDraw
	if (battle && !battlestartW)
	{

		int windowSizeX = 0;
		int windowSizeY = 0;
		glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
		float scaleX = (float)(2.0f / windowSizeX);
		float scaleY = (float)(2.0f / windowSizeY);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		glRotatef(45.f, 0.f, 1.f, 0.f);
		glRotatef(-45.f, 1.f, 0.f, 0.f);

		// PLayer
		glBegin(GL_QUADS);
		glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
		glVertex2d(-22, -21);
		glVertex2d(-22, -10);
		glVertex2d(4, -10);
		glVertex2d(4, -21);
		glEnd();


		// Enemy
		glBegin(GL_QUADS);
		glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
		glVertex2d(6, 20.5);
		glVertex2d(6, 15);
		glVertex2d(16, 15);
		glVertex2d(16, 20.5);
		glEnd();

		glColor4f(0.45f, 0.45f, 0.45f, 0.9f);
		glBegin(GL_LINES);
		glLineWidth(1.5f);
		glVertex2d(-22, -10);
		glVertex2d(-22, -21);
		glVertex2d(-22, -21);
		glVertex2d(4, -21);
		glVertex2d(4, -21);
		glVertex2d(4, -10);
		glVertex2d(4, -10);
		glVertex2d(-22, -10);
		glColor4f(0.4f, 0.4f, 0.4f, 0.6f);
		glVertex2d(-3, -10);
		glVertex2d(-3, -21);
		glEnd();


		// enemy
		glColor4f(0.45f, 0.45f, 0.45f, 0.9f);
		glBegin(GL_LINES);
		glLineWidth(1.5f);
		glVertex2d(16, 20.5);
		glVertex2d(16, 15);
		glVertex2d(16, 15);
		glVertex2d(6, 15);
		glVertex2d(6, 15);
		glVertex2d(6, 20.5);
		glVertex2d(6, 20.5);
		glVertex2d(16, 20.5);
		glEnd();

		glPopMatrix();

		string s = "Grace's ";

		fontW->drawText("Arial 20", "A BATTLE has begun!", -1 + 30 * scaleX, 1 - 55 * scaleY, .9f, 1.0f, 0.3f, scaleX, scaleY);
		s.append(playerteamW[playerindexW].mst_nickname);
		const char * trr = s.c_str();
		fontW->drawText("Arial 20", trr, -1 + 50 * scaleX, 1 - 590 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------attack buff---------------//
		s = "Att: ";
		itoa(playerAttackBuffW, buff, 10);
		s.append(buff);
		const char * bc = s.c_str();
		fontW->drawText("Arial 20", bc, -1 + 610 * scaleX, 1 - 620 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------attack---------------//
		s = "";
		s.append("Attack: ");
		itoa(playerteamW[playerindexW].attack, attW, 10);
		s.append(attW);
		const char * c = s.c_str();
		fontW->drawText("Arial 20", c, -1 + 680 * scaleX, 1 - 620 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------def buff---------------//
		s = "Def: ";
		itoa(playerDefBuffW, buff, 10);
		s.append(buff);
		const char * bbc = s.c_str();
		fontW->drawText("Arial 20", bbc, -1 + 610 * scaleX, 1 - 640 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------def---------------//
		s = "";
		s.append("Defence: ");
		itoa(playerteamW[playerindexW].defence, attW, 10);
		s.append(attW);
		const char *dc = s.c_str();
		fontW->drawText("Arial 20", dc, -1 + 680 * scaleX, 1 - 640 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------speed buff---------------//
		s = "Spd: ";
		itoa(playerSpeedBuffW, buff, 10);
		s.append(buff);
		const char * bbbc = s.c_str();
		fontW->drawText("Arial 20", bbbc, -1 + 610 * scaleX, 1 - 660 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//----------------speed-----//
		s = "";
		s.append("Speed: ");
		itoa(playerteamW[playerindexW].speed, attW, 10);
		s.append(attW);
		const char *ddc = s.c_str();
		fontW->drawText("Arial 20", ddc, -1 + 680 * scaleX, 1 - 660 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//----------acc buff---------------//
		s = "Acc: ";
		itoa(playerAccBuffW, buff, 10);
		s.append(buff);
		const char * bbbbc = s.c_str();
		fontW->drawText("Arial 20", bbbbc, -1 + 610 * scaleX, 1 - 680 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//-------------level-----------------//
		s = "";
		s.append("Level: ");
		itoa(playerteamW[playerindexW].mst_level, attW, 10);
		s.append(attW);
		const char *dddc = s.c_str();
		fontW->drawText("Arial 20", ddc, -1 + 680 * scaleX, 1 - 680 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		/*	for(int ii = 0; ii < startingplayer; ii++)
			{
			if(ii!=playerindex)
			{
			fontW->drawText("Arial 19",  playerteam[ii-1].mst_nickname, -1 + 350 * scaleX, 1 - 420+(30*ii)  * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			}*/ //bug. doesnt show up

		if (playerteamW[playerindexW].att_1 != 0)
		{
			s = "";
			if (_currentSelectionW == 0 && _currentColumnW == 0)
			{
				s = ">>";

			}
			attackcountW = 1;

			s.append(attacksW[playerteamW[playerindexW].att_1 - 1].att_name);
			//itoa(types[attacks[playerteam[playerindex].att_1-1].typ_1].typ_detail, att, 10);
			string qq = "";
			qq.append(typesW[attacksW[playerteamW[playerindexW].att_1 - 1].typ_1].typ_detail);
			qq.append(" ");
			itoa(attacksW[playerteamW[playerindexW].att_1 - 1].att_pow, attW, 10);
			qq.append(attW);
			//copy
			qq.append(" - ");
			itoa(playerteamW[playerindexW].cool_1, attW, 10);
			qq.append(attW);
			const char *dwdc = s.c_str(); //attack name
			const char *dedc = qq.c_str(); //attack stats
			fontW->drawText("Arial 20", dwdc, -1 + 50 * scaleX, 1 - 620 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			fontW->drawText("Arial 20", dedc, -1 + 220 * scaleX, 1 - 620 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			//change x * scaleX to x = 220
			//paste
		}
		if (playerteamW[playerindexW].att_2 != 0)
		{
			s = "";
			if (_currentSelectionW == 1 && _currentColumnW == 0)
			{
				s = ">>";
			}
			attackcountW = 2;
			s.append(attacksW[playerteamW[playerindexW].att_2 - 1].att_name);
			//itoa(types[attacks[playerteam[playerindex].att_1-1].typ_1].typ_detail, att, 10);
			string qq = "";
			qq.append(typesW[attacksW[playerteamW[playerindexW].att_2 - 1].typ_1].typ_detail);
			qq.append(" ");
			itoa(attacksW[playerteamW[playerindexW].att_2 - 1].att_pow, attW, 10);
			qq.append(attW);
			qq.append(" - ");
			itoa(playerteamW[playerindexW].cool_2, attW, 10);
			qq.append(attW);
			const char *dwdc = s.c_str();
			const char *dedc = qq.c_str();
			fontW->drawText("Arial 20", dwdc, -1 + 50 * scaleX, 1 - 640 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			fontW->drawText("Arial 20", dedc, -1 + 220 * scaleX, 1 - 640 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		}
		if (playerteamW[playerindexW].att_3 != 0)
		{
			s = "";
			if (_currentSelectionW == 2 && _currentColumnW == 0)
			{
				s = ">>";
			}
			attackcountW = 3;
			s.append(attacksW[playerteamW[playerindexW].att_3 - 1].att_name);
			//itoa(types[attacks[playerteam[playerindex].att_1-1].typ_1].typ_detail, att, 10);
			string qq = "";
			qq.append(typesW[attacksW[playerteamW[playerindexW].att_3 - 1].typ_1].typ_detail);
			qq.append(" ");
			itoa(attacksW[playerteamW[playerindexW].att_3 - 1].att_pow, attW, 10);
			qq.append(attW);
			qq.append(" - ");
			itoa(playerteamW[playerindexW].cool_3, attW, 10);
			qq.append(attW);
			const char *dwdc = s.c_str();
			const char *dedc = qq.c_str();
			fontW->drawText("Arial 20", dwdc, -1 + 50 * scaleX, 1 - 660 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			fontW->drawText("Arial 20", dedc, -1 + 220 * scaleX, 1 - 660 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		}
		if (playerteamW[playerindexW].att_4 != 0)
		{
			s = "";
			if (_currentSelectionW == 3 && _currentColumnW == 0)
			{
				s = ">>";
			}
			attackcountW = 4;
			s.append(attacksW[playerteamW[playerindexW].att_4 - 1].att_name);
			//itoa(types[attacks[playerteam[playerindex].att_1-1].typ_1].typ_detail, att, 10);
			string qq = "";
			qq.append(typesW[attacksW[playerteamW[playerindexW].att_4 - 1].typ_1].typ_detail);
			qq.append(" ");
			itoa(attacksW[playerteamW[playerindexW].att_4 - 1].att_pow, attW, 10);
			qq.append(attW);
			qq.append(" - ");
			itoa(playerteamW[playerindexW].cool_4, attW, 10);
			qq.append(attW);
			const char *dwdc = s.c_str();
			const char *dedc = qq.c_str();
			fontW->drawText("Arial 20", dwdc, -1 + 50 * scaleX, 1 - 680 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			fontW->drawText("Arial 20", dedc, -1 + 220 * scaleX, 1 - 680 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		}
		int teamSize = playerteamW.size();
		//the y position on the screen where do draw the first selectable monster
		int firstMon = 520;
		bool first = true;
		if(!itemmenu)
		{
			if (playerindexW == 0)
			{
				s = "";
				if (_currentSelectionW == 0 && _currentColumnW == 1)
				{
					s = ">>";
				}				
				s.append("swap to ");
				s.append(party1);
				s.append(displayHPLVL(party1ID));
				const char *mon = s.c_str();
				fontW->drawText("Arial 20", mon, -1 + 360 * scaleX, 1 - 620 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
				s = "";
				if (_currentSelectionW == 1 && _currentColumnW == 1)
				{
					s = ">>";
				}				
				s.append("swap to ");
				s.append(party2);
				s.append(displayHPLVL(party2ID));
				const char *mon1 = s.c_str();
				fontW->drawText("Arial 20", mon1, -1 + 360 * scaleX, 1 - 640 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}

			if (playerindexW == 1)
			{
				s = "";
				if (_currentSelectionW == 0 && _currentColumnW == 1)
				{
					s = ">>";
				}				
				s.append("swap to ");
				s.append(party0);
				s.append(displayHPLVL(party0ID));
				const char *mon = s.c_str();
				fontW->drawText("Arial 20", mon, -1 + 360 * scaleX, 1 - 620 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
				s = "";
				if (_currentSelectionW == 1 && _currentColumnW == 1)
				{
					s = ">>";
				}				
				s.append("swap to ");
				s.append(party2);
				s.append(displayHPLVL(party2ID));
				const char *mon1 = s.c_str();
				fontW->drawText("Arial 20", mon, -1 + 360 * scaleX, 1 - 640 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (playerindexW == 2)
			{
				s = "";
				if (_currentSelectionW == 0 && _currentColumnW == 1)
				{
					s = ">>";
				}			
				s.append("swap to ");
				s.append(party0);
				s.append(displayHPLVL(party0ID));
				const char *mon = s.c_str();
				fontW->drawText("Arial 20", mon, -1 + 360 * scaleX, 1 - 620 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
				s = "";
				if (_currentSelectionW == 1 && _currentColumnW == 1)
				{
					s = ">>";
				}			
				s.append("swap to ");
				s.append(party1);
				s.append(displayHPLVL(party1ID));
				const char *mon1 = s.c_str();
				fontW->drawText("Arial 20", mon, -1 + 360 * scaleX, 1 - 640 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}

			if (_currentSelectionW == 2 && _currentColumnW == 1)
			{
				fontW->drawText("Arial 20", ">> Items", -1 + 360 * scaleX, 1 - 660 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else{
				fontW->drawText("Arial 20", "Items", -1 + 360 * scaleX, 1 - 660 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (_currentSelectionW == 3 && _currentColumnW == 1)
			{
				fontW->drawText("Arial 20", ">> Run", -1 + 360 * scaleX, 1 - 680 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else{
				fontW->drawText("Arial 20", "Run", -1 + 360 * scaleX, 1 - 680 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
		}
		else
		{
			int e = 0;
			int y = 600-(20*e);
			for(int d = itemsHave.size()-1; d >= 0; d--)
			{	
				y = 700-(20*(e+1));
				s = "";
				//if(items[d].count> 0)
				//{
				e++;
				if(_currentSelectionItemW == d)
				{
					s.append(">>");
				}
				itoa(itemsHave[d].count, attW, 10);
				s.append (attW);
				s.append(" ");
				s.append(itemsHave[d].name);
				s.append("s");
				//	itemsHave.push_back(items[d]);
				//}
				fontW->drawText("Arial 20",s.c_str() , -1 + 360 * scaleX, 1 - y  * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			s = "";
			if(_currentSelectionItemW == itemsHave.size())
			{
				s.append(">>");
			}
			
			s.append("Back");
			fontW->drawText("Arial 20",s.c_str() , -1 + 360 * scaleX, 1 - 700  * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		}
		if (frametempW > 0)
		{
			if (attacktempW == 0)
			{
				fontW->drawText("Arial 20", attacksW[playerteamW[playerindexW].att_1 - 1].att_name, -1 + 50 * scaleX, 1 - 250 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (attacktempW == 1)
			{
				fontW->drawText("Arial 20", attacksW[playerteamW[playerindexW].att_2 - 1].att_name, -1 + 50 * scaleX, 1 - 250 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (attacktempW == 2)
			{
				fontW->drawText("Arial 20", attacksW[playerteamW[playerindexW].att_3 - 1].att_name, -1 + 50 * scaleX, 1 - 250 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (attacktempW == 3)
			{
				fontW->drawText("Arial 20", attacksW[playerteamW[playerindexW].att_4 - 1].att_name, -1 + 50 * scaleX, 1 - 250 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (playerMissed)
			{
				fontW->drawText("Arial 20", "missed", -1 + 50 * scaleX, 1 - 270 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(plTypOne * plTypeTwo == .5)
			{
				fontW->drawText("Arial 20", "not very effective", -1 + 50 * scaleX, 1 - 270 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(plTypOne * plTypeTwo == 0)
			{
				fontW->drawText("Arial 20", "immune, no damage", -1 + 50 * scaleX, 1 - 270 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(plTypOne * plTypeTwo == 2)
			{
				fontW->drawText("Arial 20", "more than effective", -1 + 50 * scaleX, 1 - 270 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (eattchWran == 0)
			{
				fontW->drawText("Arial 20", attacksW[enemyteamW[enemyindexW].att_1 - 1].att_name, -1 + 650 * scaleX, 1 - 350 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (eattchWran == 1)
			{
				fontW->drawText("Arial 20", attacksW[enemyteamW[enemyindexW].att_2 - 1].att_name, -1 + 650 * scaleX, 1 - 350 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (eattchWran == 2)
			{
				fontW->drawText("Arial 20", attacksW[enemyteamW[enemyindexW].att_3 - 1].att_name, -1 + 650 * scaleX, 1 - 350 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (eattchWran == 3)
			{
				fontW->drawText("Arial 20", attacksW[enemyteamW[enemyindexW].att_4 - 1].att_name, -1 + 650 * scaleX, 1 - 350 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (enemyMissed)
			{
				fontW->drawText("Arial 20", "missed", -1 + 650 * scaleX, 1 - 370 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(enTypOne * enTypeTwo == .5)
			{
				fontW->drawText("Arial 20", "not very effective", -1 + 650 * scaleX, 1 - 370 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(enTypOne * enTypeTwo == 0)
			{
				fontW->drawText("Arial 20", "immune, no damage", -1 + 650 * scaleX, 1 - 370 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(enTypOne * enTypeTwo == 2)
			{
				fontW->drawText("Arial 20", "very effective", -1 + 650 * scaleX, 1 - 370 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}

			frametempW--;
		}
		if (frametempW <= 0)
		{
			attackingW = false;
			frametempW = 0;
		}

		s = "";
		itoa(playerteamW[playerindexW].currenthp, attW, 10);
		s.append(attW);
		s.append("/");

		itoa(playerteamW[playerindexW].hp, attW, 10);
		s.append(attW);
		s.append(" HP");
		const char *dwdc = s.c_str();
		fontW->drawText("Arial 36", dwdc, -1 + 50 * scaleX, 1 - 140 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		s = "";
		itoa(enemyteamW[enemyindexW].currenthp, attW, 10);

		s.append(attW);
		s.append("/");
		itoa(enemyteamW[enemyindexW].hp, attW, 10);
		s.append(attW);
		s.append(" HP");
		const char *dedc = s.c_str();
		fontW->drawText("Arial 36", dedc, -1 + 1150 * scaleX, 1 - 550 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		if(wild)
		{
		s = "Wild ";
		}
		else
		{
			s = "Tamer ";
			s.append(tamername);
			s.append("'s ");
		}
		
		s.append(enemyteamW[enemyindexW].mst_nickname);
		const char * trrr = s.c_str();
		fontW->drawText("Arial 20", trrr, -1 + 910 * scaleX, 1 - 70 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//------------acc buff-------------//
		/*s = "Acc: ";
		itoa(enemyAccBuffW, buff, 10);
		s.append(buff);
		const char * cb = s.c_str();
		fontW->drawText("Arial 20", cb, -1 + 910 * scaleX, 1 - 110 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);*/
		//------level------------//
		s = "Level: ";
		itoa(enemyteamW[enemyindexW].mst_level, attW, 10);
		s.append(attW);
		const char * terr = s.c_str();
		fontW->drawText("Arial 20", terr, -1 + 910 * scaleX, 1 - 110 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//------------attack buff------------//
		/*s = "Att: ";
		itoa(enemyAttackBuffW, buff, 10);
		s.append(buff);
		const char * cbb = s.c_str();
		fontW->drawText("Arial 20", cbb, -1 + 910 * scaleX, 1 - 130 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//----------attack----------------------//
		s = "Attack: ";
		itoa(enemyteamW[enemyindexW].attack, attW, 10);
		s.append(attW);
		const char * tetr = s.c_str();
		fontW->drawText("Arial 20", tetr, -1 + 1000 * scaleX, 1 - 130 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//-------def buff--------------//
		s = "Def: ";
		itoa(enemyDefBuffW, buff, 10);
		s.append(buff);
		const char * cbbb = s.c_str();
		fontW->drawText("Arial 20", cbbb, -1 + 910 * scaleX, 1 - 150 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//----------def---------------//
		s = "Defence: ";
		itoa(enemyteamW[enemyindexW].defence, attW, 10);
		s.append(attW);
		const char * twetr = s.c_str();
		fontW->drawText("Arial 20", twetr, -1 + 1000 * scaleX, 1 - 150 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//-----------speed buff--------------//
		s = "Spd: ";
		itoa(enemySpeedBuffW, buff, 10);
		s.append(buff);
		const char * cbbbb = s.c_str();
		fontW->drawText("Arial 20", cbbbb, -1 + 910 * scaleX, 1 - 170 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//------------speed----------------//
		s = "Speed: ";
		itoa(enemyteamW[enemyindexW].speed, attW, 10);
		s.append(attW);
		const char * twetf = s.c_str();
		fontW->drawText("Arial 20", twetf, -1 + 1000 * scaleX, 1 - 170 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);*/

		//////////////////////////////////////////////////////////////////// 

		glUseProgram(0);

		glScalef(0.04, 0.04, 0.04);

		// Create the isometric view
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		float sw = .6;

		glOrtho(-1 * sw, 1 * sw, -1 * sw, 1 * sw, -200, 200);


		glRotatef(45.f, 1.f, 0.f, 0.f);
		glRotatef(-45.f, 0.f, 1.f, 0.f);

		// big close
		glPushMatrix();


		glTranslatef(0.05, 0.05, .15);
		glRotatef(170, 0, 1, 0);
		glRotatef(-13, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		glScalef(2.7, 2.7, 2.7);
		entityW->draw();
		glPopMatrix();

		// small far
		glPushMatrix();
		glTranslatef(0.2, .05, -.2);
		glRotatef(-10, 0, 0, 1);
		glRotatef(10, 0, 1, 0);
		glRotatef(80, 1, 0, 0);

		glScalef(1.6, 1.6, 1.6);
		entity2W->draw();
		glPopMatrix();
	}
#pragma endregion BattleDraw

#pragma region battletransitions
	if (!battle && battlestartW)
	{
		int windowSizeX = 0;
		int windowSizeY = 0;
		glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
		float scaleX = (float)(2.0f / windowSizeX);
		float scaleY = (float)(2.0f / windowSizeY);
		//glPushMatrix();
		//glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		fontW->drawText("Arial 36", "A BATTLE has begun!", -1 + 600 * scaleX, 1 - 350 * scaleY, .9f, 1.0f, 0.3f, scaleX, scaleY);
		//glUseProgram(0);
	}
	if(caught)
	{
		int windowSizeX = 0;
		int windowSizeY = 0;
		glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
		float scaleX = (float)(2.0f / windowSizeX);
		float scaleY = (float)(2.0f / windowSizeY);
		//glPushMatrix();
		//glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		fontW->drawText("Arial 36", "You caught a monster!", -1 + 600 * scaleX, 1 - 350 * scaleY, .9f, 1.0f, 0.3f, scaleX, scaleY);
		glUseProgram(0);

	}
	if (battleoverW && !battle && !battlestartW && !run && !caught)
	{
		if (playerlosesW)
		{
			int windowSizeX = 0;
			int windowSizeY = 0;
			glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
			float scaleX = (float)(2.0f / windowSizeX);
			float scaleY = (float)(2.0f / windowSizeY);
			//glPushMatrix();
			//glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			fontW->drawText("Arial 36", "You lost...", -1 + 600 * scaleX, 1 - 350 * scaleY, .9f, 1.0f, 0.3f, scaleX, scaleY);
			glUseProgram(0);

			for(int i = 0; i < playerteamW.size(); i++)
			{
				playerteamW[i].currenthp = playerteamW[i].hp;
				playerdudesW++;
			}
			player->Reset();
			camera->Reset();
			tileManager->Reset();
		}
		else
		{
			int windowSizeX = 0;
			int windowSizeY = 0;
			glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
			float scaleX = (float)(2.0f / windowSizeX);
			float scaleY = (float)(2.0f / windowSizeY);
			//glPushMatrix();
			//glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			fontW->drawText("Arial 36", "You won!", -1 + 600 * scaleX, 1 - 350 * scaleY, .9f, 1.0f, 0.3f, scaleX, scaleY);
			glUseProgram(0);
		}
	}
	if (run)
	{
		int windowSizeX = 0;
		int windowSizeY = 0;
		glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
		float scaleX = (float)(2.0f / windowSizeX);
		float scaleY = (float)(2.0f / windowSizeY);
		//glPushMatrix();
		//glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		fontW->drawText("Arial 20", "You ran away", -1 + 30 * scaleX, 1 - 55 * scaleY, .9f, 1.0f, 0.3f, scaleX, scaleY);
		glUseProgram(0);
		screenCounter--;		
	}
	else{
		run = false;
	}


#pragma endregion

}

void selectionDownW()
{
	if(!itemmenu)
	{
		++_currentSelectionW;
		//number of options column 1
		if (_currentSelectionW > attackcountW - 1 && _currentColumnW == 0)
		{
			_currentSelectionW = 0;
		}
		//number of options column 2
		if (_currentSelectionW == 4 && _currentColumnW == 1)
		{
			_currentSelectionW = 0;
		}
		//handle skipping dash "-" in menu
		if (_currentSelectionW == 0 && _currentColumnW == 1 && party1 == "-")
		{
			_currentSelectionW = 1;
		}
		if (_currentSelectionW == 1 && _currentColumnW == 1 && party2 == "-")
		{
			_currentSelectionW = 2;
		}
	}
	else
	{
		_currentSelectionItemW++;
		if(_currentSelectionItemW > itemsHave.size())
		{
			_currentSelectionItemW = 0;
		}
	}


}
void selectionUpW()
{

	if(!itemmenu)
	{
		--_currentSelectionW;
		//number of options column 1
		if (_currentSelectionW < 0 && _currentColumnW == 0)
		{
			_currentSelectionW = attackcountW - 1;
		}
		//number of options column 2
		if (_currentSelectionW == -1 && _currentColumnW == 1)
		{
			_currentSelectionW = 3;
		}
		//handle skipping dash "-" in menu
		if (_currentSelectionW == 1 && _currentColumnW == 1 && party2 == "-")
		{
			_currentSelectionW = 0;
			if (party1 == "-")
			{
				_currentSelectionW = 3;
			}

		}
		if (_currentSelectionW == 1 && _currentColumnW == 1 && party1 == "-")
		{
			_currentSelectionW = 3;
		}
	}
	else
	{
		_currentSelectionItemW--;
		if(_currentSelectionItemW < 0)
		{
			_currentSelectionItemW = itemsHave.size();
		}
	}

}
void selectionLeftW()
{
	if(!itemmenu)
	{
		--_currentColumnW;
		if (_currentColumnW <= -1)
		{
			_currentColumnW = 1;
		}
		if (_currentColumnW == 0)
		{
			if (attackcountW - 1 < _currentSelectionW)
			{
				_currentSelectionW = attackcountW - 1;
			}
		}

		if (_currentSelectionW == 0 && _currentColumnW == 1 && party1 == "-")
		{
			_currentSelectionW = 2;
		}
		if (_currentSelectionW == 1 && _currentColumnW == 1 && party2 == "-")
		{
			_currentSelectionW = 2;
		}
	}
}
void selectionRightW()
{
	if(!itemmenu)
	{
		++_currentColumnW;
		if (_currentColumnW >= 2)
		{
			_currentColumnW = 0;
		}
		if (_currentColumnW == 0)
		{
			if (attackcountW - 1 < _currentSelectionW)
			{
				_currentSelectionW = attackcountW - 1;
			}
		}

		if (_currentSelectionW == 0 && _currentColumnW == 1 && party1 == "-")
		{
			_currentSelectionW = 2;
		}
		if (_currentSelectionW == 1 && _currentColumnW == 1 && party2 == "-")
		{
			_currentSelectionW = 2;
		}
	}

}
void attacksSelectedW()
{
	//**change all below when working in battles**
	frametempW = 60;
	attackingW = true;
	double pSpeed = playerteamW[playerindexW].speed * (1 + (playerSpeedBuffW / 3));
	double eSpeed = enemyteamW[enemyindexW].speed * (1 + (enemySpeedBuffW / 3));
	if (pSpeed >= eSpeed)
	{
		handlePlayerW();
		handleEnemyW();
	}
	else
	{
		//enemy does damage
		//player takes damage
		//check if player dead
		//check if player out of monsters
		handleEnemyW();
		//player does damage
		//enemy takes damage
		//check if enemy dead
		//check if enemy out of monsters
		handlePlayerW();
	}
}
void handlePlayerW()
{
	plTypOne = 1, plTypeTwo = 1;
	//PLAYER HANDLE
	if (attackingW)
	{
		playerMissed = false;
		int xx = 0;
		int baseModAcc = 1 + (playerAccBuffW / 3);
		if (attchW != -1)
		{

			if ((attacksW[attchW - 1].att_acc * baseModAcc) >= (rand() % 100 + 1))
			{
				if (attacksW[attchW - 1].eff_id == 0)
				{
					/*double baseModAtt = 1 + (playerAccBuffW / 2);
					double baseModDef = 1 + (enemyDefBuffW / 2);
					double dmgRange = (rand() % 15 + 85) / 100.0;
					double att = baseModAtt * attacksW[attchW - 1].att_pow;
					double def = baseModDef * enemyteamW[enemyindexW].defence;
					//change battle formula
					//player does damage		
					xx = ((2 * playerteamW[playerindexW].mst_level * att *  (att / def)) / 50) * dmgRange;
					if (attacktempW == 4)
					{
						xx = 0;
					}
					if(enemyteamW[enemyindexW].typ_1-5>=0 && attacksW[attchW-1].typ_1-5 >= 0)
					{
						plTypOne = typesMatchW[enemyteamW[enemyindexW].typ_1-5][attacksW[attchW-1].typ_1-5];
					}
					if(playerteamW[enemyindexW].typ_2-5>=0 && attacksW[eattchW-1].typ_1-5 >= 0)
					{
						plTypeTwo = typesMatchW[enemyteamW[enemyindexW].typ_2-5][attacksW[attchW-1].typ_1-5];
					}
					xx *= plTypOne*plTypeTwo;*/
					double baseModAtt = 1 + (playerAccBuffW / 2);
					double baseModDef = 1 + (enemyDefBuffW / 2);
					double dmgRange = (rand() % 15 + 85) / 100.0;
					double att = baseModAtt * playerteamW[playerindexW].attack;
					double def = baseModDef * enemyteamW[enemyindexW].defence;
					//change battle formula
					//player does damage	
					double lvldm = 2 * playerteamW[playerindexW].mst_level / 12.0;
					double ott = (lvldm* (att / def) *attacksW[attchW - 1].att_pow) / 50.00;
					xx = (ott + 2) * dmgRange;
				}
				//do work here
				else{
					switch (attacksW[attchW - 1].eff_id)
					{
						//self buffs
					case 2:
						playerAttackBuffW += attacksW[attchW - 1].att_pow;
						break;
					case 4:
						playerDefBuffW += attacksW[attchW - 1].att_pow;
						break;
					case 6:
						playerSpeedBuffW += attacksW[attchW - 1].att_pow;
						break;
					case 8:
						playerAccBuffW += attacksW[attchW - 1].att_pow;
						break;
						//debuffs on enemy
					case 1:
						enemyAttackBuffW += attacksW[attchW - 1].att_pow;
						break;
					case 3:
						enemyDefBuffW += attacksW[attchW - 1].att_pow;
						break;
					case 5:
						enemySpeedBuffW += attacksW[attchW - 1].att_pow;
						break;
					case 7:
						enemyAccBuffW += attacksW[attchW - 1].att_pow;
						break;
					}
				}
			}
			else
			{
				playerMissed = true;
			}
		}
		//apply cooldown
		switch (attacktempW)
		{
		case 0:
			playerteamW[playerindexW].cool_1 = attacksW[playerteamW[playerindexW].att_1 - 1].att_cool;
			playerteamW[playerindexW].cool_2--;
			playerteamW[playerindexW].cool_3--;
			playerteamW[playerindexW].cool_4--;
			break;
		case 1:
			playerteamW[playerindexW].cool_2 = attacksW[playerteamW[playerindexW].att_2 - 1].att_cool;
			playerteamW[playerindexW].cool_1--;
			playerteamW[playerindexW].cool_3--;
			playerteamW[playerindexW].cool_4--;
			break;
		case 2:
			playerteamW[playerindexW].cool_3 = attacksW[playerteamW[playerindexW].att_3 - 1].att_cool;
			playerteamW[playerindexW].cool_1--;
			playerteamW[playerindexW].cool_2--;
			playerteamW[playerindexW].cool_4--;
			break;
		case 3:
			playerteamW[playerindexW].cool_4 = attacksW[playerteamW[playerindexW].att_4 - 1].att_cool;
			playerteamW[playerindexW].cool_1--;
			playerteamW[playerindexW].cool_2--;
			playerteamW[playerindexW].cool_3--;
			break;
		case 4:
			playerteamW[playerindexW].cool_1--;
			playerteamW[playerindexW].cool_2--;
			playerteamW[playerindexW].cool_3--;
			playerteamW[playerindexW].cool_4--;
			break;
		}
		if (playerteamW[playerindexW].cool_1 < 0)
		{
			playerteamW[playerindexW].cool_1 = 0;
		}
		if (playerteamW[playerindexW].cool_2 < 0)
		{
			playerteamW[playerindexW].cool_2 = 0;
		}
		if (playerteamW[playerindexW].cool_3 < 0)
		{
			playerteamW[playerindexW].cool_3 = 0;
		}
		if (playerteamW[playerindexW].cool_4 < 0)
		{
			playerteamW[playerindexW].cool_4 = 0;
		}

		//enemy takes damage
		enemyteamW[enemyindexW].currenthp -= xx;
		//check if enemy dead
		if (enemyteamW[enemyindexW].currenthp <= 0)
		{
			enemyteamW[enemyindexW].currenthp = 0;
			enemydudesW--;
			eattchWran = -1;
			attackingW = false; // end the attack loop, cant hit if dead
			//enemydead;
			levelupW();
			//check if enemy out of monsters
			if (enemydudesW <= 0)
			{
				//battle won by player
				enemylosesW = true;
				playerwinsW();
				return;
			}
			else
			{
				//HANDLE NEW DUDE
				//change index;
				//ai SELECT after
				for (int i = 0; i < startingenemyW; i++)
				{
					if (enemyteamW[i].currenthp > 0)
					{
						//change dude animation
						enemyindexW = i;
						enemyAccBuffW = 0;
						enemySpeedBuffW = 0;
						enemyDefBuffW = 0;
						enemyAttackBuffW = 0;
						entity2W->LoadModel(enemyteamW[enemyindexW].spc_model);
					}
				}
			}
		}
	}
}
void handleEnemyW()
{
	//ENEMY HANDLE
	enTypOne = 1, enTypeTwo = 1;
	enemyMissed = false;
	if (attackingW)
	{
		//enemy does damage
		int yy = 0;
		int baseModAcc = 1 + (enemyAccBuffW / 3);
		if (eattchW != -1)
		{
			if ((attacksW[eattchW - 1].att_acc * baseModAcc) >= (rand() % 100 + 1))
			{
				if (attacksW[eattchW - 1].eff_id == 0)
				{
					/*double dmgRange = (rand() % 15 + 85) / 100.0;
					//change battle formula
					//player does damage						
					double baseModAtt = 1 + (enemyAttackBuffW / 2);
					double baseModDef = 1 + (playerDefBuffW / 2);
					double att = baseModAtt * attacksW[eattchW - 1].att_pow;
					double def = baseModDef * playerteamW[playerindexW].defence;
					if (eattchW > 0)
					{
						yy = ((2 * enemyteamW[enemyindexW].mst_level * att *  (att / def)) / 50) * dmgRange;
						if(playerteamW[playerindexW].typ_1-5>=0 && attacksW[eattchW-1].typ_1-5 >= 0)
						{
						enTypOne = typesMatchW[playerteamW[playerindexW].typ_1-5][attacksW[eattchW-1].typ_1-5];
						}
						if(playerteamW[playerindexW].typ_2-5>=0 && attacksW[eattchW-1].typ_1-5 >= 0)
						{
						enTypeTwo = typesMatchW[playerteamW[playerindexW].typ_2-5][attacksW[eattchW-1].typ_1-5];
						}
						yy *= enTypOne*enTypeTwo;
					}*/
					double dmgRange = (rand() % 15 + 85) / 100.0;
					//change battle formula
					//player does damage						
					double baseModAtt = 1 + (enemyAttackBuffW / 2);
					double baseModDef = 1 + (playerDefBuffW / 2);

					double att = baseModAtt * enemyteamW[enemyindexW].attack;
					double def = baseModDef * playerteamW[playerindexW].defence;
					double lvldm = 2 * enemyteamW[enemyindexW].mst_level / 12.0;
					double ott = (lvldm* (att / def) *attacksW[eattchW - 1].att_pow) / 50.00;
					yy = (ott + 2) * dmgRange;
				}
				else
				{
					switch (attacksW[eattchW - 1].eff_id)
					{
						//self buffs
					case 2:
						enemyAttackBuffW += attacksW[eattchW - 1].att_pow;
						break;
					case 4:
						enemyDefBuffW += attacksW[eattchW - 1].att_pow;
						break;
					case 6:
						enemySpeedBuffW += attacksW[eattchW - 1].att_pow;
						break;
					case 8:
						enemyAccBuffW += attacksW[eattchW - 1].att_pow;
						break;
						//debuffs on player
					case 1:
						playerAttackBuffW += attacksW[eattchW - 1].att_pow;
						break;
					case 3:
						playerDefBuffW += attacksW[eattchW - 1].att_pow;
						break;
					case 5:
						playerSpeedBuffW += attacksW[eattchW - 1].att_pow;
						break;
					case 7:
						playerAccBuffW += attacksW[eattchW - 1].att_pow;
						break;
					}
				}
			}
			else
			{
				enemyMissed = true;
			}
		}

		//player takes damage

		//apply cooldown
		///decrease other cooldowns
		switch (eattchWran)
		{
		case 0:
			enemyteamW[enemyindexW].cool_1 = attacksW[enemyteamW[enemyindexW].att_1 - 1].att_cool;
			enemyteamW[enemyindexW].cool_2--;
			enemyteamW[enemyindexW].cool_3--;
			enemyteamW[enemyindexW].cool_4--;
			break;
		case 1:
			enemyteamW[enemyindexW].cool_2 = attacksW[enemyteamW[enemyindexW].att_2 - 1].att_cool;
			enemyteamW[enemyindexW].cool_1--;
			enemyteamW[enemyindexW].cool_3--;
			enemyteamW[enemyindexW].cool_4--;
			break;
		case 2:
			enemyteamW[enemyindexW].cool_3 = attacksW[enemyteamW[enemyindexW].att_3 - 1].att_cool;
			enemyteamW[enemyindexW].cool_2--;
			enemyteamW[enemyindexW].cool_1--;
			enemyteamW[enemyindexW].cool_4--;
			break;
		case 3:
			enemyteamW[enemyindexW].cool_4 = attacksW[enemyteamW[enemyindexW].att_4 - 1].att_cool;
			enemyteamW[enemyindexW].cool_2--;
			enemyteamW[enemyindexW].cool_3--;
			enemyteamW[enemyindexW].cool_1--;
			break;
		case 4:
			enemyteamW[enemyindexW].cool_1--;
			enemyteamW[enemyindexW].cool_2--;
			enemyteamW[enemyindexW].cool_3--;
			enemyteamW[enemyindexW].cool_4--;
			break;
		}
		//reset negative cooldowns to 0
		if (enemyteamW[enemyindexW].cool_1 < 0)
		{
			enemyteamW[enemyindexW].cool_1 = 0;
		}
		if (enemyteamW[enemyindexW].cool_2 < 0)
		{
			enemyteamW[enemyindexW].cool_2 = 0;
		}
		if (enemyteamW[enemyindexW].cool_3 < 0)
		{
			enemyteamW[enemyindexW].cool_3 = 0;
		}
		if (enemyteamW[enemyindexW].cool_4 < 0)
		{
			enemyteamW[enemyindexW].cool_4 = 0;
		}
		playerteamW[playerindexW].currenthp -= yy;
		//check if player dead
		if (playerteamW[playerindexW].currenthp <= 0)
		{
			playerteamW[playerindexW].currenthp = 0;
			playerdudesW--;
			attacktempW = -1;
			attackingW = false;
			//playerdead;
			//check if player out of monsters
			if (playerdudesW <= 0)
			{
				//battle won by enemy

				playerlosesW = true;
				enemywinsW();
				return;
			}
			else
			{
				//HANDLE NEW DUDE
				//change index;
				//player SELECT after
				//fontW->drawText(
				for (int i = 0; i < startingplayerW; i++)
				{
					if (playerteamW[i].currenthp > 0)
					{
						//change dude animation
						playerindexW = i;
						playerAccBuffW = 0;
						playerSpeedBuffW = 0;
						playerDefBuffW = 0;
						playerAttackBuffW = 0;
						entityW->LoadModel(playerteamW[playerindexW].spc_model);
					}
				}
			}

		}
	}

}
void selectW()
{
	bool valid = false;
	if(!itemmenu)
	{
		if (battle && !attackingW)
		{
			//BATTLE ROUND START
			
	#pragma region selectAttack
			//PLAYER TURN
			//SELECT ATTACK
			if (_currentColumnW == 0)
			{
				attacktempW = _currentSelectionW;

				attchW = 0;

				//everything on cooldown
				if (playerteamW[playerindexW].cool_1 > 0 && playerteamW[playerindexW].cool_2 > 0
					&& playerteamW[playerindexW].cool_3 > 0 && playerteamW[playerindexW].cool_4 > 0)
				{
					attacktempW = 4;
				}

				//check if valid

				if (attacktempW == 0)
				{
					attchW = playerteamW[playerindexW].att_1;
					valid = (playerteamW[playerindexW].cool_1 == 0);
				}
				if (attacktempW == 1)
				{
					attchW = playerteamW[playerindexW].att_2;
					valid = (playerteamW[playerindexW].cool_2 == 0);
				}
				if (attacktempW == 2)
				{
					attchW = playerteamW[playerindexW].att_3;
					valid = (playerteamW[playerindexW].cool_3 == 0);
				}
				if (attacktempW == 3)
				{
					valid = (playerteamW[playerindexW].cool_4 == 0);
					attchW = playerteamW[playerindexW].att_4;
				}
				//ENEMY TURN
				//SELECT ATTACK

				int c = 0;
				if (enemyteamW[enemyindexW].att_1 > 0)
				{
					c++;
				}
				if (enemyteamW[enemyindexW].att_2 > 0)
				{
					c++;
				}
				if (enemyteamW[enemyindexW].att_3 > 0)
				{
					c++;
				}
				if (enemyteamW[enemyindexW].att_4 > 0)
				{
					c++;
				}
				if (valid)
				{
					bool enemyvalid = false;
					//everythin on cool down
					if (enemyteamW[enemyindexW].cool_1 > 0 && enemyteamW[enemyindexW].cool_2 > 0
						&& enemyteamW[enemyindexW].cool_3 > 0 && enemyteamW[enemyindexW].cool_4 > 0)
					{
						enemyvalid = true;
						eattchW = -1;
						eattchWran = 4;
					}

					while (!enemyvalid)
					{
						eattchW = 0;
						eattchWran = rand() % c;
						if (eattchWran == 0)
						{
							enemyvalid = (enemyteamW[enemyindexW].cool_1 == 0);
							eattchW = enemyteamW[enemyindexW].att_1;
						}
						if (eattchWran == 1)
						{
							enemyvalid = (enemyteamW[enemyindexW].cool_2 == 0);
							eattchW = enemyteamW[enemyindexW].att_2;
						}
						if (eattchWran == 2)
						{
							enemyvalid = (enemyteamW[enemyindexW].cool_3 == 0);
							eattchW = enemyteamW[enemyindexW].att_3;
						}
						if (eattchWran == 3)
						{
							enemyvalid = (enemyteamW[enemyindexW].cool_4 == 0);
							eattchW = enemyteamW[enemyindexW].att_4;
						}
					}
					attacksSelectedW();
				}
				else
				{
				}
			}
	#pragma endregion selectAttack
	#pragma region selectOther
			if (_currentColumnW == 1)
			{
				if (_currentSelectionW == 0)
				{
					//swap to first mon
					if (playerindexW == 0)
					{
						if (playerteamW[1].currenthp > 0)
						{
							playerindexW = 1;
							valid = true;
							playerAccBuffW = 0;
							playerSpeedBuffW = 0;
							playerDefBuffW = 0;
							playerAttackBuffW = 0;
							entityW->LoadModel(playerteamW[playerindexW].spc_model);
						}

					}
					else if (playerindexW == 1)
					{
						if (playerteamW[0].currenthp > 0)
						{
							playerindexW = 0;
							valid = true;
							playerAccBuffW = 0;
							playerSpeedBuffW = 0;
							playerDefBuffW = 0;
							playerAttackBuffW = 0;
							entityW->LoadModel(playerteamW[playerindexW].spc_model);
						}
					}
					else if (playerindexW == 2)
					{
						if (playerteamW[0].currenthp > 0)
						{
							playerindexW = 0;
							valid = true;
							playerAccBuffW = 0;
							playerSpeedBuffW = 0;
							playerDefBuffW = 0;
							playerAttackBuffW = 0;
							entityW->LoadModel(playerteamW[playerindexW].spc_model);
						}

					}

					attchW = -1;
					attacktempW = 4;

					int c = 0;
					if (enemyteamW[enemyindexW].att_1 > 0)
					{
						c++;
					}
					if (enemyteamW[enemyindexW].att_2 > 0)
					{
						c++;
					}
					if (enemyteamW[enemyindexW].att_3 > 0)
					{
						c++;
					}
					if (enemyteamW[enemyindexW].att_4 > 0)
					{
						c++;
					}
					if (valid)
					{
						bool enemyvalid = false;
						if (enemyteamW[enemyindexW].cool_1 > 0 && enemyteamW[enemyindexW].cool_2 > 0
							&& enemyteamW[enemyindexW].cool_3 > 0 && enemyteamW[enemyindexW].cool_4 > 0)
						{
							enemyvalid = true;
							eattchW = -1;
						}

						while (!enemyvalid)
						{
							eattchW = 0;
							eattchWran = rand() % c;
							if (eattchWran == 0)
							{
								enemyvalid = (enemyteamW[enemyindexW].cool_1 == 0);
								eattchW = enemyteamW[enemyindexW].att_1;
							}
							if (eattchWran == 1)
							{
								enemyvalid = (enemyteamW[enemyindexW].cool_2 == 0);
								eattchW = enemyteamW[enemyindexW].att_2;
							}
							if (eattchWran == 2)
							{
								enemyvalid = (enemyteamW[enemyindexW].cool_3 == 0);
								eattchW = enemyteamW[enemyindexW].att_3;
							}
							if (eattchWran == 3)
							{
								enemyvalid = (enemyteamW[enemyindexW].cool_4 == 0);
								eattchW = enemyteamW[enemyindexW].att_4;
							}
						}
						attacksSelectedW();
					}


				}
				if (_currentSelectionW == 1)
				{

					//swap to second mon
					if (playerindexW == 0)
					{
						if (playerteamW[2].currenthp > 0)
						{
							playerindexW = 2;
							valid = true;
							playerAccBuffW = 0;
							playerSpeedBuffW = 0;
							playerDefBuffW = 0;
							playerAttackBuffW = 0;
							entityW->LoadModel(playerteamW[playerindexW].spc_model);
						}
					}
					else if (playerindexW == 1)
					{
						if (playerteamW[2].currenthp > 0)
						{
							playerindexW = 2;
							valid = true;
							playerAccBuffW = 0;
							playerSpeedBuffW = 0;
							playerDefBuffW = 0;
							playerAttackBuffW = 0;
							entityW->LoadModel(playerteamW[playerindexW].spc_model);
						}
					}
					else if (playerindexW == 2)
					{
						if (playerteamW[1].currenthp > 0)
						{
							playerindexW = 1;
							valid = true;
							playerAccBuffW = 0;
							playerSpeedBuffW = 0;
							playerDefBuffW = 0;
							playerAttackBuffW = 0;
							entityW->LoadModel(playerteamW[playerindexW].spc_model);
						}
					}



					attchW = -1;
					attacktempW = 4;

					int c = 0;
					if (enemyteamW[enemyindexW].att_1 > 0)
					{
						c++;
					}
					if (enemyteamW[enemyindexW].att_2 > 0)
					{
						c++;
					}
					if (enemyteamW[enemyindexW].att_3 > 0)
					{
						c++;
					}
					if (enemyteamW[enemyindexW].att_4 > 0)
					{
						c++;
					}
					if (valid)
					{
						bool enemyvalid = false;
						if (enemyteamW[enemyindexW].cool_1 > 0 && enemyteamW[enemyindexW].cool_2 > 0
							&& enemyteamW[enemyindexW].cool_3 > 0 && enemyteamW[enemyindexW].cool_4 > 0)
						{
							enemyvalid = true;
							eattchW = -1;
						}

						while (!enemyvalid)
						{
							eattchW = 0;
							eattchWran = rand() % c;
							if (eattchWran == 0)
							{
								enemyvalid = (enemyteamW[enemyindexW].cool_1 == 0);
								eattchW = enemyteamW[enemyindexW].att_1;
							}
							if (eattchWran == 1)
							{
								enemyvalid = (enemyteamW[enemyindexW].cool_2 == 0);
								eattchW = enemyteamW[enemyindexW].att_2;
							}
							if (eattchWran == 2)
							{
								enemyvalid = (enemyteamW[enemyindexW].cool_3 == 0);
								eattchW = enemyteamW[enemyindexW].att_3;
							}
							if (eattchWran == 3)
							{
								enemyvalid = (enemyteamW[enemyindexW].cool_4 == 0);
								eattchW = enemyteamW[enemyindexW].att_4;
							}
						}
						attacksSelectedW();
					}

				}
				//items
				if (_currentSelectionW == 2)
				{
					itemmenu = true;
				}
				//run
				if (_currentSelectionW == 3)
				{
					run = true;
					battleoverW = true;
					battle = false;
					screenCounter = 350;
				}

			}
	#pragma endregion

		}
	}
#pragma region itemSelect
	else
	{
		valid = true;
		const int ee = itemsHave.size();
		if(_currentSelectionItemW == itemsHave.size())
		{
			//defs back
			itemmenu = false;
		}
		else
		{
			
			int curid = itemsHave[_currentSelectionItemW].id;
			int totalid = 0;
			for(int d = 0; d < items.size(); d++)
			{
				if(items[d].id == itemsHave[_currentSelectionItemW].id)
				{
					totalid = d;
					break;
				}
			}
			if(itemsHave[_currentSelectionItemW].count > 0)
			{
				if(wild)
				{
					if(curid == 1)
					{
						//leashh
						//catch
						if(rand() % 3 == 0)
						{
							battle = false;
							caught = true;
							screenCounter = 320;
							battleoverW = true;
							itemmenu = false;
							playertotalTeamW.push_back(enemyteamW[enemyindexW]);
							if(!playerteamW.size()<3)
							{
								playerteamW.push_back(enemyteamW[enemyindexW]);
										playerdudesW++;
										startingplayerW++;
							}

						}
					}
				}
				if(curid == 2)
				{
					//heal 30%
					playerteamW[playerindexW].currenthp += playerteamW[playerindexW].hp*.3;
				}
				if(curid == 3)
				{
					//heal 60%
					playerteamW[playerindexW].currenthp += playerteamW[playerindexW].hp*.6;
				}
				if(curid == 4)
				{
					//heal 100%
					playerteamW[playerindexW].currenthp = playerteamW[playerindexW].hp;
				}
				if(curid == 5)
				{
					//cooldowns
					playerteamW[playerindexW].cool_1 = 0;
					playerteamW[playerindexW].cool_2 = 0;
					playerteamW[playerindexW].cool_3 = 0;
					playerteamW[playerindexW].cool_4 = 0;
				}
				if(curid == 6)
				{
					//revive
					for(int ii = 0; ii < playerteamW.size(); ii++)
					{
						if(playerteamW[ii].currenthp ==0)
						{
							playerteamW[ii].currenthp = playerteamW[ii].hp/3;
						}
					}
				}
				itemsHave[_currentSelectionItemW].count--;
				items[totalid].count--;
			}
			if(playerteamW[playerindexW].currenthp > playerteamW[playerindexW].hp)
			{
				playerteamW[playerindexW].currenthp = playerteamW[playerindexW].hp;
			}
			for(int dd = 0; dd < itemsHave.size(); dd++)
			{
				if(itemsHave[dd].count <=0)
				{
					itemsHave.erase(itemsHave.begin() + dd);
				}
			}
			attchW = -1;
			attacktempW = 4;

			int c = 0;
			if (enemyteamW[enemyindexW].att_1 > 0)
			{
				c++;
			}
			if (enemyteamW[enemyindexW].att_2 > 0)
			{
				c++;
			}
			if (enemyteamW[enemyindexW].att_3 > 0)
			{
				c++;
			}
			if (enemyteamW[enemyindexW].att_4 > 0)
			{
				c++;
			}
		
			bool enemyvalid = false;
			if (enemyteamW[enemyindexW].cool_1 > 0 && enemyteamW[enemyindexW].cool_2 > 0
				&& enemyteamW[enemyindexW].cool_3 > 0 && enemyteamW[enemyindexW].cool_4 > 0)
			{
				enemyvalid = true;
				eattchW = -1;
			}

			while (!enemyvalid)
			{
				eattchW = 0;
				eattchWran = rand() % c;
				if (eattchWran == 0)
				{
					enemyvalid = (enemyteamW[enemyindexW].cool_1 == 0);
					eattchW = enemyteamW[enemyindexW].att_1;
				}
				if (eattchWran == 1)
				{
					enemyvalid = (enemyteamW[enemyindexW].cool_2 == 0);
					eattchW = enemyteamW[enemyindexW].att_2;
				}
				if (eattchWran == 2)
				{
					enemyvalid = (enemyteamW[enemyindexW].cool_3 == 0);
					eattchW = enemyteamW[enemyindexW].att_3;
				}
				if (eattchWran == 3)
				{
					enemyvalid = (enemyteamW[enemyindexW].cool_4 == 0);
					eattchW = enemyteamW[enemyindexW].att_4;
				}
			}
			attacksSelectedW();
		

		}
	}
#pragma endregion itemSelect

}
//load from database
#pragma region load
int loadallW()
{
	//loadIndex();
	loadItems();
	loadSpcW();
	loadMstW();
	loadAttW();
	loadEffW();
	loadTmrW();
	loadMvsetW();
	loadTypW();
	loadEvoW();
	loadCndW();
	loadEncW();

	//loadPlayer
	loadPlayer();
	//selectMons();

	return 0;
}
int loadIndexW()
{
	INDEX sIndex;
	cout << "exporting " << "index.dat" << endl;

	//files
	fstream file_dat(("Database/index.dat"), ios::in | ios::binary); //The dat file with the bits
	fstream file_csv(("index.csv"), ios::out); //the spreadshit that displays the bits
	if (!file_dat.is_open() || !file_csv.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sIndex, sizeof(INDEX));
		indexesW.push_back(sIndex);
		++record_count;
	}
	file_dat.close();
	file_csv.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadSpcW()
{
	SPECIES sSpecies;
	cout << "exporting " << "species.dat" << endl;

	//files
	fstream file_dat(("Database/species.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sSpecies, sizeof(SPECIES));
		speciesW.push_back(sSpecies);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadMstW()
{
	MONSTER sMonster;
	cout << "exporting " << "monsters.dat" << endl;

	//files
	fstream file_dat(("Database/monsters.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sMonster, sizeof(MONSTER));
		monstersW.push_back(sMonster);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadAttW()
{
	ATTACK sAttack;
	cout << "exporting " << "attacks.dat" << endl;

	//files
	fstream file_dat(("Database/attacks.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sAttack, sizeof(ATTACK));
		attacksW.push_back(sAttack);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadEffW()
{
	EFFECT sEffect;
	cout << "exporting " << "effects.dat" << endl;

	//files
	fstream file_dat(("Database/effects.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sEffect, sizeof(EFFECT));
		effectsW.push_back(sEffect);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadTmrW()
{
	TAMER sTamer;
	cout << "exporting " << "tamers.dat" << endl;

	//files
	fstream file_dat(("Database/tamers.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sTamer, sizeof(TAMER));
		tamersW.push_back(sTamer);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadMvsetW()
{
	MOVESET sMoveset;
	cout << "exporting " << "movesets.dat" << endl;

	//files
	fstream file_dat(("Database/movesets.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sMoveset, sizeof(MOVESET));
		movesetsW.push_back(sMoveset);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadTypW()
{
	TYPE sType;
	cout << "exporting " << "types.dat" << endl;

	//files
	fstream file_dat(("Database/types.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sType, sizeof(TYPE));
		typesW.push_back(sType);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadEvoW()
{
	EVOLUTION sEvo;
	cout << "exporting " << "evolutions.dat" << endl;

	//files
	fstream file_dat(("Database/evolutions.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sEvo, sizeof(EVOLUTION));
		evolutionsW.push_back(sEvo);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadCndW()
{
	CONDITION sCnd;
	cout << "exporting " << "conditions.dat" << endl;

	//files
	fstream file_dat(("Database/conditions.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sCnd, sizeof(CONDITION));
		conditionsW.push_back(sCnd);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	return 0;
}
int loadEncW()
{
	ENCOUNTER sEnc;
	cout << "exporting " << "ecounters.dat" << endl;

	//files
	fstream file_dat(("Database/encounters.dat"), ios::in | ios::binary); //The dat file with the bits
	if (!file_dat.is_open())
	{
		return 1;
	}
	file_dat.seekg(0, ios::end);
	streamoff filesize = file_dat.tellg();
	cout << filesize << endl;
	file_dat.seekg(0, ios::beg);
	file_dat.seekg(0, ios::beg);

	int record_count = 0;

	while (file_dat.tellg() < filesize)
	{

		file_dat.read((char*)&sEnc, sizeof(ENCOUNTER));
		encountersW.push_back(sEnc);
		++record_count;
	}
	file_dat.close();
	cout << record_count << " record(s) processed." << endl;
	for (int i = 0; i < encountersW.size(); i++)
	{
		bool vecfound = false;
		int index = 0;
		//1st
		//EncounterSetW
		int ii = 0;
		for (ii = 0; ii < encounterActualsW.size(); ii++)
		{
			if (encounterActualsW[ii].enc_id == encountersW[i].enc_set)
			{
				vecfound = true;
				index = ii;
				break;
			}
		}
		if (!vecfound)
		{
			ENCOUNTERACTUAL sEncAct;
			sEncAct.enc_id = encountersW[i].enc_set;
			encounterActualsW.push_back(sEncAct);
			SPECIESSET sSpecs;
			sSpecs.enc_rate = encountersW[i].enc_rate;
			sSpecs.spc_id = encountersW[i].spc_id;
			sSpecs.mst_lvl = encountersW[i].mst_lvl;
			encounterActualsW[ii].species.push_back(sSpecs);
		}
		else
		{
			SPECIESSET sSpecs;
			sSpecs.enc_rate = encountersW[i].enc_rate;
			sSpecs.spc_id = encountersW[i].spc_id;
			sSpecs.mst_lvl = encountersW[i].mst_lvl;
			encounterActualsW[index].species.push_back(sSpecs);
		}

	}
	int total = 0;
	for (int dd = 0; dd < encounterActualsW.size(); dd++)
	{
		total = 0;
		for (int ddd = 0; ddd < encounterActualsW[dd].species.size(); ddd++)
		{
			total += encounterActualsW[dd].species[ddd].enc_rate;
		}
		encounterActualsW[dd].enc_steprate = total;
	}
	return 0;
}
void loadPlayer()
{
	MONSTERACTUAL monactual;
	playerteamW.clear();
	int one, two, three;
	one = tamersW[0].mst_1;
	two = tamersW[0].mst_2;
	three = tamersW[0].mst_3;
	if (one > 0)
	{
		cout << "you loaded: " << monstersW[one - 1].mst_nickname << " the " << speciesW[monstersW[one - 1].spc_id - 1].spc_name << endl << endl;

		monactual.attack = (speciesW[monstersW[one - 1].spc_id - 1].spc_attack * 2 * monstersW[one - 1].mst_level / 100) + 5;
		monactual.defence = (speciesW[monstersW[one - 1].spc_id - 1].spc_defence * 2 * monstersW[one - 1].mst_level / 100) + 5;
		monactual.speed = (speciesW[monstersW[one - 1].spc_id - 1].spc_speed * 2 * monstersW[one - 1].mst_level / 100) + 5;
		monactual.hp = (speciesW[monstersW[one - 1].spc_id - 1].spc_hp * 2 * monstersW[one - 1].mst_level / 100) + 5;
		monactual.currenthp = monactual.hp;
		monactual.mst_id = monstersW[one - 1].mst_id;
		monactual.mst_level = monstersW[one - 1].mst_level;
		strcpy(monactual.mst_nickname, monstersW[one - 1].mst_nickname);
		//monactual.mst_nickname = monsters[one].mst_nickname;
		monactual.typ_1 = speciesW[monstersW[one - 1].spc_id - 1].typ_1;
		monactual.typ_2 = speciesW[monstersW[one - 1].spc_id - 1].typ_2;
		monactual.att_1 = monstersW[one - 1].mst_attack1;
		monactual.att_2 = monstersW[one - 1].mst_attack2;
		monactual.att_3 = monstersW[one - 1].mst_attack3;
		monactual.att_4 = monstersW[one - 1].mst_attack4;
		monactual.cool_1 = 0;
		monactual.cool_2 = 0;
		monactual.cool_3 = 0;
		monactual.cool_4 = 0;
		strcpy(monactual.spc_model, speciesW[monstersW[one - 1].spc_id - 1].spc_model);
		//monactual.spc_model = species[monsters[one].spc_id].spc_model;
		strcpy(monactual.spc_name, speciesW[monstersW[one - 1].spc_id - 1].spc_name);
		//monactual.spc_name = species[monsters[one].spc_id].spc_name;
		monactual.mst_xp = (4 * monactual.mst_level *monactual.mst_level*monactual.mst_level) / 5;
		playerteamW.push_back(monactual);
		startingplayerW++;
		playertotalTeamW.push_back(monactual);
	}
	if (two > 0)
	{
		cout << "you loaded: " << monstersW[two - 1].mst_nickname << " the " << speciesW[monstersW[two - 1].spc_id - 1].spc_name << endl << endl;

		monactual.attack = (speciesW[monstersW[two - 1].spc_id - 1].spc_attack * 2 * monstersW[two - 1].mst_level / 100) + 5;
		monactual.defence = (speciesW[monstersW[two - 1].spc_id - 1].spc_defence * 2 * monstersW[two - 1].mst_level / 100) + 5;
		monactual.speed = (speciesW[monstersW[two - 1].spc_id - 1].spc_speed * 2 * monstersW[two - 1].mst_level / 100) + 5;
		monactual.hp = (speciesW[monstersW[two - 1].spc_id - 1].spc_hp * 2 * monstersW[two - 1].mst_level / 100) + 5;
		monactual.currenthp = monactual.hp;
		monactual.mst_id = monstersW[two - 1].mst_id;
		monactual.mst_level = monstersW[two - 1].mst_level;
		strcpy(monactual.mst_nickname, monstersW[two - 1].mst_nickname);
		//monactual.mst_nickname = monsters[two].mst_nickname;
		monactual.typ_1 = speciesW[monstersW[two - 1].spc_id - 1].typ_1;
		monactual.typ_2 = speciesW[monstersW[two - 1].spc_id - 1].typ_2;
		monactual.att_1 = monstersW[two - 1].mst_attack1;
		monactual.att_2 = monstersW[two - 1].mst_attack2;
		monactual.att_3 = monstersW[two - 1].mst_attack3;
		monactual.att_4 = monstersW[two - 1].mst_attack4;
		monactual.cool_1 = 0;
		monactual.cool_2 = 0;
		monactual.cool_3 = 0;
		monactual.cool_4 = 0;
		strcpy(monactual.spc_model, speciesW[monstersW[two - 1].spc_id - 1].spc_model);
		//monactual.spc_model = species[monsters[two].spc_id].spc_model;
		strcpy(monactual.spc_name, speciesW[monstersW[two - 1].spc_id - 1].spc_name);
		//monactual.spc_name = species[monsters[two].spc_id].spc_name;
		monactual.mst_xp = (4 * monactual.mst_level *monactual.mst_level*monactual.mst_level) / 5;
		playerteamW.push_back(monactual);
		startingplayerW++;
		playertotalTeamW.push_back(monactual);
	}
	if (three > 0)
	{
		cout << "you loaded: " << monstersW[three - 1].mst_nickname << " the " << speciesW[monstersW[three - 1].spc_id - 1].spc_name << endl << endl;

		monactual.attack = (speciesW[monstersW[three - 1].spc_id - 1].spc_attack * 2 * monstersW[three - 1].mst_level / 100) + 5;
		monactual.defence = (speciesW[monstersW[three - 1].spc_id - 1].spc_defence * 2 * monstersW[three - 1].mst_level / 100) + 5;
		monactual.speed = (speciesW[monstersW[three - 1].spc_id - 1].spc_speed * 2 * monstersW[three - 1].mst_level / 100) + 5;
		monactual.hp = (speciesW[monstersW[three - 1].spc_id - 1].spc_hp * 2 * monstersW[three - 1].mst_level / 100) + 5;
		monactual.currenthp = monactual.hp;
		monactual.mst_id = monstersW[three - 1].mst_id;
		monactual.mst_level = monstersW[three - 1].mst_level;
		strcpy(monactual.mst_nickname, monstersW[three - 1].mst_nickname);
		//monactual.mst_nickname = monsters[three].mst_nickname;
		monactual.typ_1 = speciesW[monstersW[three - 1].spc_id - 1].typ_1;
		monactual.typ_2 = speciesW[monstersW[three - 1].spc_id - 1].typ_2;
		monactual.att_1 = monstersW[three - 1].mst_attack1;
		monactual.att_2 = monstersW[three - 1].mst_attack2;
		monactual.att_3 = monstersW[three - 1].mst_attack3;
		monactual.att_4 = monstersW[three - 1].mst_attack4;
		monactual.cool_1 = 0;
		monactual.cool_2 = 0;
		monactual.cool_3 = 0;
		monactual.cool_4 = 0;
		strcpy(monactual.spc_model, speciesW[monstersW[three - 1].spc_id - 1].spc_model);
		//monactual.spc_model = species[monsters[three].spc_id].spc_model;
		strcpy(monactual.spc_name, speciesW[monstersW[three - 1].spc_id - 1].spc_name);
		//monactual.spc_name = species[monsters[three].spc_id].spc_name;
		monactual.mst_xp = (4 * monactual.mst_level *monactual.mst_level*monactual.mst_level) / 5;
		playerteamW.push_back(monactual);
		startingplayerW++;
		playertotalTeamW.push_back(monactual);
	}

}
#pragma endregion data
void enemywinsW()
{
	battle = false;
	itemmenu = false;
	battleoverW = true;
	screenCounter = 160;
}
void playerwinsW()
{
	battle = false;
	itemmenu = false;
	battleoverW = true;
	screenCounter = 160;
//	evolve();
}
void evolve()
{
	//check evolutions for each party member
	for(int i = 0; i < playerteamW.size()-1; i++)
	{
		for(int p = 0; p < evolutionsW.size()-1; p++)
		{
			if(playerteamW[i].spc_id = evolutionsW[p].mst_from)
			{
				if(playerteamW[i].mst_level >= evolutionsW[p].cnd_lvl)
				{
					switch(evolutionsW[p].cnd_id)
					{
						case 0: //evolve by level
						playerteamW[i].spc_id = evolutionsW[p].mst_to;
						reassign(i);
						break;
					}
				}
			}
		}
	}
}
void reassign(int i)
{
		playerteamW[i].attack = (speciesW[monstersW[playerteamW[i].mst_id - 1].spc_id - 1].spc_attack * 2 * monstersW[playerteamW[i].mst_id - 1].mst_level / 100) + 5;
		playerteamW[i].defence = (speciesW[monstersW[playerteamW[i].mst_id - 1].spc_id - 1].spc_defence * 2 * monstersW[playerteamW[i].mst_id - 1].mst_level / 100) + 5;
		playerteamW[i].speed = (speciesW[monstersW[playerteamW[i].mst_id - 1].spc_id - 1].spc_speed * 2 * monstersW[playerteamW[i].mst_id - 1].mst_level / 100) + 5;
		playerteamW[i].hp = (speciesW[monstersW[playerteamW[i].mst_id - 1].spc_id - 1].spc_hp * 2 * monstersW[playerteamW[i].mst_id - 1].mst_level / 100) + 5;
		//playerteamW[i].spc_model =speciesW[monstersW[playerteamW[i].mst_id - 1].spc_id - 1].spc_name;
		//playerteamW[i].spc_name = speciesW[monstersW[playerteamW[i].mst_id - 1].spc_id - 1].spc_name;
		strcpy(playerteamW[i].spc_model, speciesW[playerteamW[i].spc_id-1].spc_model);
		strcpy(playerteamW[i].spc_name, speciesW[playerteamW[i].spc_id-1].spc_name);
		playerteamW[i].typ_1 =speciesW[monstersW[playerteamW[i].mst_id - 1].spc_id - 1].typ_1 ;
		playerteamW[i].typ_2 = speciesW[monstersW[playerteamW[i].mst_id - 1].spc_id - 1].typ_2;
		entityW->LoadModel(playerteamW[i].spc_model);
}
void levelupW()
{
	int previousLvl = playerteamW[playerindexW].mst_level;
	vector<int> possibleAttack;
	int x = enemyteamW[enemyindexW].attack + enemyteamW[enemyindexW].defence + enemyteamW[enemyindexW].hp + enemyteamW[enemyindexW].speed;
	double y = (x / 3.5 / 125);
	double z = x*y;
	int zz = z *20;
	if(!wild)
	{
		zz *= 1.5;
	}
	playerteamW[playerindexW].mst_xp += zz;

	//check level
	bool leveled = false;
	int xpfornext = (4 * (playerteamW[playerindexW].mst_level + 1) *(playerteamW[playerindexW].mst_level + 1)*(playerteamW[playerindexW].mst_level + 1)) / 5;
	//xpfornext = 8;
	while (playerteamW[playerindexW].mst_xp > xpfornext)
	{
		xpfornext = (4 * (playerteamW[playerindexW].mst_level + 1) *(playerteamW[playerindexW].mst_level + 1)*(playerteamW[playerindexW].mst_level + 1)) / 5;
		//levelupanimation
		playerteamW[playerindexW].mst_level++;
		leveled = true;
	}
	if (leveled)
	{
		//xpfornext = 100;
		//playerteamW[playerindexW].mst_id - 1
		playerteamW[playerindexW].attack = (speciesW[monstersW[playerteamW[playerindexW].mst_id - 1].spc_id - 1].spc_attack * 2 * monstersW[playerteamW[playerindexW].mst_id - 1].mst_level / 100) + 5;
		playerteamW[playerindexW].defence = (speciesW[monstersW[playerteamW[playerindexW].mst_id - 1].spc_id - 1].spc_defence * 2 * monstersW[playerteamW[playerindexW].mst_id - 1].mst_level / 100) + 5;
		playerteamW[playerindexW].speed = (speciesW[monstersW[playerteamW[playerindexW].mst_id - 1].spc_id - 1].spc_speed * 2 * monstersW[playerteamW[playerindexW].mst_id - 1].mst_level / 100) + 5;
		playerteamW[playerindexW].hp = (speciesW[monstersW[playerteamW[playerindexW].mst_id - 1].spc_id - 1].spc_hp * 2 * monstersW[playerteamW[playerindexW].mst_id - 1].mst_level / 100) + 5;

		//learn new attacks
		for (int j = 0; j < movesetsW.size(); j++)
		{
			//all possible attacks for the current spc
			if (movesetsW[j].mst_id == playerteamW[playerindexW].spc_id)
			{
				//constrain to attacks between previouvs lvl and currentlvl
				if (movesetsW[j].mv_lev > previousLvl && movesetsW[j].mv_lev <= playerteamW[playerindexW].mst_level)
				{
					possibleAttack.push_back(movesetsW[j].att_id);
				}
			}
		}
		for(int jj = 0; jj < possibleAttack.size(); jj++)
		{	
			if(playerteamW[playerindexW].att_4 != 0)
			{
				// UI for choosing attack
			}
			//add attack here
			if(playerteamW[playerindexW].att_1 == 0)
			{
			}
			else if(playerteamW[playerindexW].att_2 == 0)
			{
				playerteamW[playerindexW].att_2 = possibleAttack[jj];
				continue;
			}
			else if(playerteamW[playerindexW].att_3 == 0)
			{
				playerteamW[playerindexW].att_3 = possibleAttack[jj];
				continue;
			}
			else if(playerteamW[playerindexW].att_4 == 0)
			{
				playerteamW[playerindexW].att_4 = possibleAttack[jj];
				continue;
			}
		}		
			
	}
}
void loadItems()
{
	ITEM i;
	//new item
	i.id = 1;
	strcpy(i.name, "Leash");
	i.count = 500;
	items.push_back(i);
	///
	i.id = 2;
	strcpy(i.name, "Heal 30%");
	i.count = 5;
	items.push_back(i);
	i.id = 3;
	strcpy(i.name, "Heal 60%");
	i.count = 5;
	items.push_back(i);
	i.id = 4;
	strcpy(i.name, "Heal 100%");
	i.count = 5;
	items.push_back(i);
	i.id = 5;
	strcpy(i.name, "Refresh CD");
	i.count = 5;
	items.push_back(i);
	i.id = 6;
	strcpy(i.name, "Revive ALL");
	i.count = 5;
	items.push_back(i);
	i.id = 7;
	strcpy(i.name, "Badge 1");
	i.count = 0;
	items.push_back(i);
	i.id = 8;
	strcpy(i.name, "Badge 2");
	i.count = 0;
	items.push_back(i);
	i.id = 9;
	strcpy(i.name, "Badge 3");
	i.count = 0;
	items.push_back(i);
	i.id = 10;
	strcpy(i.name, "Badge 4");
	i.count = 0;
	items.push_back(i);
	itemsHave.clear();
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].count >= 1)
		{
			itemsHave.push_back(items[i]);
		}
	}
}


void World::writeHighscore()
{
	int temp = 0;
	char* highestlvl;
	for (int i = 0; i < playerteamW.size(); i++)
	{
		if (playerteamW[i].mst_level > temp)
			temp = playerteamW[i].mst_level;
	}

	highestlvl = (char*)temp;

	FILE* file;
	file = fopen("resource\\highscore.txt", "w");
	if (file != NULL)
	{
		fprintf(file, "%d", temp);
		fclose(file);
	}
}
