#define _WIN32_WINNT _WIN32_WINNT_WINXP // Windows XP compatibility macro
#pragma pack(1)   //proper Endian switch

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "include\FalseFightState.h"
#include "include\GameState.h"
#include "include\GLFW\glfw3.h"
#include "include\GameFont.h"
#include "database_types.h"
#include "engine_types.h"
#include "include\Entity.h"
#include <windows.h>    
#include <string>
#pragma comment(lib, "winmm.lib") 
using namespace std;

//Varibales
vector<INDEX> indexes;
vector<SPECIES> species;
vector<MONSTER> monsters;
vector<ATTACK> attacks;
vector<EFFECT> effects;
vector<TAMER> tamers;
vector<MOVESET> movesets;
vector<TYPE> types;
vector<EVOLUTION> evolutions;
vector<CONDITION> conditions;
vector<MONSTERACTUAL> playerteam;
vector<MONSTERACTUAL> enemyteam;
	
	void selectionUp();
	void selectionDown();
	void selectionLeft();
	void selectionRight();
	void select();
	void handlePlayer();
	void handleEnemy();
	Entity* currPrev;
	vector<Entity*> prevs;
	GameFont* font;
	double typesMatch[12][12] = {
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
double enTypOneF = 1, enTypeTwoF = 1;
double plTypOneF = 1, plTypeTwoF = 1;


	int _currentSelection;
	int _currentColumn;
	int menuindex = 0;
	bool music = false;
	char l[3];
	char att[15];
	char buffF[2];
	int attch;
	int eattch;
	int eattchran;
	void attacksSelected();
	bool runn = false;
int loadall();
int loadIndex();
int loadSpc();
int loadMst();
int loadAtt();
int loadEff();
int loadTmr();
int loadMvset();
int loadTyp();
int loadEvo();
int loadCnd();
int selectMons();
bool playerloses = false;
bool enemyloses = false;
bool load = true;
bool selectteams = false;
bool teamone = false;
bool teamtwo = false;
int monindex = 1;
bool enter = false;
bool battling = false;
int playerindex = 0;
int enemyindex = 0;
int playerdudes = 0;
int enemydudes = 0;
int startingplayer = 0;
int startingenemy = 0;
int attackcount = 0;
bool enemyMissedF = false;
bool playerMissedF = false;

int frametemp = 0;
int attacktemp = 0;
bool attacking = false;
bool battlestart = false;
bool battleover = false;
char* party0f = "-";
char* party1f = "-";
char* party2f = "-";
int party0IDf;
int party1IDf;
int party2IDf;

int playerAccBuff = 0;
int playerSpeedBuff = 0;
int playerDefBuff = 0;
int playerAttackBuff = 0;
int enemyAccBuff = 0;
int enemySpeedBuff = 0;
int enemyDefBuff = 0;
int enemyAttackBuff = 0;

void enemywins();
void playerwins();
//void levelupW();
//void reassign(int i);
bool updateBattle();
//int playerindex = 0;
//int enemyindex = 0;
//int playerdudes = 0;
//int enemydudes = 0;
//int startingplayer = 0;
//int startingenemy = 0;
//int eattchran = 0;
Entity* entity;
Entity* entity2;
int screenCounterF;
string displayHPLVLF(int id)
{
	string s = "";
	for (int i = 0; i < playerteam.size(); i++)
	{
		if (playerteam[i].mst_id == id)
		{
			ostringstream q;
			q << " " << playerteam[i].currenthp << "/" << playerteam[i].hp << "  lvl" << playerteam[i].mst_level;
			s.append(q.str());
		}
	}
	return s;
}

FalseFightState::FalseFightState(StateManager* manager)
	: GameState(manager)
{

}

FalseFightState::~FalseFightState(void)
{

}

FalseFightState* FalseFightState::getInstance(StateManager* manager)
{
	static FalseFightState Instance(manager);
	return &Instance;
}

void FalseFightState::enterState()
{
	_lastKey = GLFW_KEY_ENTER;
}

void FalseFightState::leaveState()
{
}

void FalseFightState::update(double currentTime)
{
	if(load)
	{
		loadall();
		string d = species[monsters[_currentSelection].spc_id-1].spc_model;
		currPrev = new Entity(d);
					

		font->createFont("Arial 19", "C:\\Windows\\Fonts\\Arial.ttf", 18, 0);
	}
	if(selectteams)
	{
		currPrev->update(currentTime);
		for(int i = 0; i < prevs.size(); i++)
		{
			prevs[i]->update(currentTime);
		}
		GLFWwindow* window = glfwGetCurrentContext();

		if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && _lastKey != GLFW_KEY_ENTER && !enter)
		{
			select();
		}
		else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && _lastKey != GLFW_KEY_UP)
		{
			_lastKey = GLFW_KEY_UP;
			selectionUp();
		}
		else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && _lastKey != GLFW_KEY_DOWN)
		{
			_lastKey = GLFW_KEY_DOWN;
			selectionDown();
		}

		if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			enter = true;
		else
			enter = false;

		// lastKey reset statement
		if(_lastKey != -1)
		{
			if(glfwGetKey(window, _lastKey) == GLFW_RELEASE)
				_lastKey = -1;
		}
		//currPrev->LoadModel(species[monsters[_currentSelection].spc_id].spc_model);
		
		
	}
	if(battlestart)
	{
		//run initial battle code #battlecode
		battling = true;
		battlestart = false;
		string x = playerteam[playerindex].spc_model;
		string y = enemyteam[enemyindex].spc_model;
		entity = new Entity(x);
		entity2 = new Entity(y);
	}
	if(battling)
	{
		entity->update(currentTime);
		entity2->update(currentTime);
		party0f = playerteam[0].mst_nickname;
		(playerteam.size() > 1) ? party1f = playerteam[1].mst_nickname : party1f = "-";
		(playerteam.size() > 2) ? party2f = playerteam[2].mst_nickname : party2f = "-";
		party0IDf = playerteam[0].mst_id;
		(playerteam.size() > 1) ? party1IDf = playerteam[1].mst_id : party1IDf = -1;
		(playerteam.size() > 2) ? party2IDf = playerteam[2].mst_id : party2IDf = -1;

		
		if(!music)
		{
	//	PlaySound(TEXT("../battlemusic"),NULL, SND_SYNC | SND_LOOP);
		music = true;
		}
		GLFWwindow* window = glfwGetCurrentContext();
		if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !enter)
		{
			select();
			
		}
		else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && _lastKey != GLFW_KEY_UP)
		{
			_lastKey = GLFW_KEY_UP;
			selectionUp();
		}
		else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && _lastKey != GLFW_KEY_DOWN)
		{
			_lastKey = GLFW_KEY_DOWN;
			selectionDown();
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && _lastKey != GLFW_KEY_LEFT)
		{
			_lastKey = GLFW_KEY_LEFT;
			selectionLeft();
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && _lastKey != GLFW_KEY_RIGHT)
		{
			_lastKey = GLFW_KEY_RIGHT;
			selectionRight();
		}

		// lastKey reset statement
		if(_lastKey != -1)
		{
			if(glfwGetKey(window, _lastKey) == GLFW_RELEASE)
				_lastKey = -1;
		}
		
		if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			enter = true;
		else
			enter = false;

	}

}

void FalseFightState::draw()
{	
	

	
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int windowSizeX = 0;
	int windowSizeY = 0;
	glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
	float scaleX = (float)(2.0f / windowSizeX);
	float scaleY = (float)(2.0f / windowSizeY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(selectteams)
	{
			glUseProgram(0);

	glScalef(0.04, 0.04, 0.04);

	// Create the isometric view
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	float s = .6;

	glOrtho(-1 * s, 1 * s,-1 * s,1 * s, -200, 200);


	//glRotatef(45.f, 1.f, 0.f, 0.f);
	//glRotatef(-45.f, 0.f, 1.f, 0.f);

	// big close
	glPushMatrix();


	//glTranslatef(0.05,0.05,.15);
	//glRotatef(170,0,1,0);
//glRotatef(-13,0,0,1);
//glRotatef(90,1,0,0);
	//glScalef(2.7,2.7,2.7);
	//entity->draw();


	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.2,.05,-.2);
	glRotatef(-10,0,0,1);
	glRotatef(10,0,1,0);
	glRotatef(80,1,0,0);
	glScalef(1.3,1.3,1.3);
	currPrev->draw();
	glTranslatef(-.2,-.05,.2);
	glPopMatrix();
	for(int i = 0; i < prevs.size(); i++)
	{
	glPushMatrix();
	glTranslatef(0.8*i,.05*i,-.2*i);
	glRotatef(-10*i,0,0,1);
	glRotatef(10*i,0,1,0);
	glRotatef(80*i,1,0,0);
	glScalef(1.0,1.0,1.0);
	prevs[i]->draw();
	glTranslatef(-0.8*i,-.05*i,.2*i);
	glPopMatrix();
	}


	
	
	
		string d ="Select Monster ";
		itoa(monindex,l,10);
		d.append(l);
		const char * e = d.c_str();
		if(teamone)
		{
			d.append(" for team two");
		}
		else
		{
			d.append(" for team one");
		}
	font->drawText("Arial 19", e, -1 + 30 * scaleX, 1 - 55 * scaleY, 0.45f, 0.85f, 0.95f, scaleX, scaleY);
	for(int i = 0; i < monsters.size(); i++)
	{
		if(_currentSelection == i)
		{

			string s = ">>";
			s.append(monsters[i].mst_nickname);
			s.append(": Level ");
			
			itoa(monsters[i].mst_level,l,10);
			s.append(l);
			s.append(" ");
			s.append(species[monsters[i].spc_id-1].spc_name);

			const char * c = s.c_str();
			font->drawText("Arial 19",c, -1 + 30 * scaleX, 1 - (90 + (30*i)) * scaleY, 1, 1, 1, scaleX, scaleY);
		}
		else
		{
			string s = "";
			s.append(monsters[i].mst_nickname);
			s.append(": Level ");
			
			itoa(monsters[i].mst_level,l,10);
			s.append(l);
			s.append(" ");
			s.append(species[monsters[i].spc_id-1].spc_name);
			const char * c = s.c_str();
			font->drawText("Arial 19",c, -1 + 30 * scaleX, 1 - (90 + (30*i)) * scaleY, 1, 1, 1, scaleX, scaleY);
			//font->drawText("Arial 19",monsters[i].mst_nickname, -1 + 30 * scaleX, 1 - (90 + (30*i)) * scaleY, 1, 1, 1, scaleX, scaleY);	
		}

	}
	if(_currentSelection == monsters.size())
	{
			font->drawText("Arial 19",">>Finish", -1 + 30 * scaleX, 1 - (90 + (30*monsters.size())) * scaleY, 1, 1, 1, scaleX, scaleY);
	}
	else
	{
		font->drawText("Arial 19","Finish", -1 + 30 * scaleX, 1 - (90 + (30*monsters.size())) * scaleY, 1, 1, 1, scaleX, scaleY);
	}

	}
	if(battleover)
	{
		font->drawText("Arial 19", "BATTLE OVER", -1 + 30 * scaleX, 1 - 55 * scaleY, .9f, 1.0f, 0.3f, scaleX*2, scaleY*2);
		if(playerloses)
		{
			font->drawText("Arial 19", "PLAYER LOSES", -1 + 30 * scaleX, 1 - 80 * scaleY, .9f, 1.0f, 0.3f, scaleX*2, scaleY*2);
		}
		else
		{
			font->drawText("Arial 19", "PLAYER WINS", -1 + 30 * scaleX, 1 - 80 * scaleY, .9f, 1.0f, 0.3f, scaleX*2, scaleY*2);
		}
		//return;
	}
	if(battling)
	{
		int windowSizeX = 0;
		int windowSizeY = 0;
		glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
		float scaleX = (float)(2.0f / windowSizeX);
		float scaleY = (float)(2.0f / windowSizeY);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		string s = "Your ";

		font->drawText("Arial 19", "Battle start", -1 + 30 * scaleX, 1 - 55 * scaleY, .9f, 1.0f, 0.3f, scaleX, scaleY);
		s.append(playerteam[playerindex].mst_nickname);
		const char * trr = s.c_str();
		font->drawText("Arial 19", trr, -1 + 50 * scaleX, 1 - 490 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------attack buff---------------//
		s = "Att: ";
		itoa(playerAttackBuff, buffF, 10);
		s.append(buffF);
		const char * bc = s.c_str();
		font->drawText("Arial 19", bc, -1 + 610 * scaleX, 1 - 520 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------attack---------------//
		s = "";
		s.append("Attack: ");
		itoa(playerteam[playerindex].attack, att, 10);
		s.append(att);
		const char * c = s.c_str();
		font->drawText("Arial 19", c, -1 + 680 * scaleX, 1 - 520 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------def buff---------------//
		s = "Def: ";
		itoa(playerDefBuff, buffF, 10);
		s.append(buffF);
		const char * bbc = s.c_str();
		font->drawText("Arial 19", bbc, -1 + 610 * scaleX, 1 - 540 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------def---------------//
		s = "";
		s.append("Defence: ");
		itoa(playerteam[playerindex].defence, att, 10);
		s.append(att);
		const char *dc = s.c_str();
		font->drawText("Arial 19", dc, -1 + 680 * scaleX, 1 - 540 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//---------speed buff---------------//
		s = "Spd: ";
		itoa(playerSpeedBuff, buffF, 10);
		s.append(buffF);
		const char * bbbc = s.c_str();
		font->drawText("Arial 19", bbbc, -1 + 610 * scaleX, 1 - 560 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//----------------speed-----//
		s = "";
		s.append("Speed: ");
		itoa(playerteam[playerindex].speed, att, 10);
		s.append(att);
		const char *ddc = s.c_str();
		font->drawText("Arial 19", ddc, -1 + 680 * scaleX, 1 - 560 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//----------acc buff---------------//
		s = "Acc: ";
		itoa(playerAccBuff, buffF, 10);
		s.append(buffF);
		const char * bbbbc = s.c_str();
		font->drawText("Arial 19", bbbbc, -1 + 610 * scaleX, 1 - 580 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		//-------------level-----------------//
		s = "";
		s.append("Level: ");
		itoa(playerteam[playerindex].mst_level, att, 10);
		s.append(att);
		const char *dddc = s.c_str();
		font->drawText("Arial 19", ddc, -1 + 680 * scaleX, 1 - 580 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		/*	for(int ii = 0; ii < startingplayer; ii++)
			{
			if(ii!=playerindex)
			{
			fontW->drawText("Arial 19",  playerteam[ii-1].mst_nickname, -1 + 350 * scaleX, 1 - 420+(30*ii)  * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			}*/ //bug. doesnt show up

		if (playerteam[playerindex].att_1 != 0)
		{
			s = "";
			if (_currentSelection == 0 && _currentColumn == 0)
			{
				s = ">>";

			}
			attackcount = 1;

			s.append(attacks[playerteam[playerindex].att_1 - 1].att_name);
			//itoa(types[attacks[playerteam[playerindex].att_1-1].typ_1].typ_detail, att, 10);
			string qq = "";
			qq.append(types[attacks[playerteam[playerindex].att_1 - 1].typ_1].typ_detail);
			qq.append(" ");
			itoa(attacks[playerteam[playerindex].att_1 - 1].att_pow, att, 10);
			qq.append(att);
			//copy
			qq.append(" - ");
			itoa(playerteam[playerindex].cool_1, att, 10);
			qq.append(att);
			const char *dwdc = s.c_str(); //attack name
			const char *dedc = qq.c_str(); //attack stats
			font->drawText("Arial 19", dwdc, -1 + 50 * scaleX, 1 - 520 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			font->drawText("Arial 19", dedc, -1 + 220 * scaleX, 1 - 520 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			//change x * scaleX to x = 220
			//paste
		}
		if (playerteam[playerindex].att_2 != 0)
		{
			s = "";
			if (_currentSelection == 1 && _currentColumn == 0)
			{
				s = ">>";
			}
			attackcount = 2;
			s.append(attacks[playerteam[playerindex].att_2 - 1].att_name);
			//itoa(types[attacks[playerteam[playerindex].att_1-1].typ_1].typ_detail, att, 10);
			string qq = "";
			qq.append(types[attacks[playerteam[playerindex].att_2 - 1].typ_1].typ_detail);
			qq.append(" ");
			itoa(attacks[playerteam[playerindex].att_2 - 1].att_pow, att, 10);
			qq.append(att);
			qq.append(" - ");
			itoa(playerteam[playerindex].cool_2, att, 10);
			qq.append(att);
			const char *dwdc = s.c_str();
			const char *dedc = qq.c_str();
			font->drawText("Arial 19", dwdc, -1 + 50 * scaleX, 1 - 540 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			font->drawText("Arial 19", dedc, -1 + 220 * scaleX, 1 - 540 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		}
		if (playerteam[playerindex].att_3 != 0)
		{
			s = "";
			if (_currentSelection == 2 && _currentColumn == 0)
			{
				s = ">>";
			}
			attackcount = 3;
			s.append(attacks[playerteam[playerindex].att_3 - 1].att_name);
			//itoa(types[attacks[playerteam[playerindex].att_1-1].typ_1].typ_detail, att, 10);
			string qq = "";
			qq.append(types[attacks[playerteam[playerindex].att_3 - 1].typ_1].typ_detail);
			qq.append(" ");
			itoa(attacks[playerteam[playerindex].att_3 - 1].att_pow, att, 10);
			qq.append(att);
			qq.append(" - ");
			itoa(playerteam[playerindex].cool_3, att, 10);
			qq.append(att);
			const char *dwdc = s.c_str();
			const char *dedc = qq.c_str();
			font->drawText("Arial 19", dwdc, -1 + 50 * scaleX, 1 - 560 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			font->drawText("Arial 19", dedc, -1 + 220 * scaleX, 1 - 560 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		}
		if (playerteam[playerindex].att_4 != 0)
		{
			s = "";
			if (_currentSelection == 3 && _currentColumn == 0)
			{
				s = ">>";
			}
			attackcount = 4;
			s.append(attacks[playerteam[playerindex].att_4 - 1].att_name);
			//itoa(types[attacks[playerteam[playerindex].att_1-1].typ_1].typ_detail, att, 10);
			string qq = "";
			qq.append(types[attacks[playerteam[playerindex].att_4 - 1].typ_1].typ_detail);
			qq.append(" ");
			itoa(attacks[playerteam[playerindex].att_4 - 1].att_pow, att, 10);
			qq.append(att);
			qq.append(" - ");
			itoa(playerteam[playerindex].cool_4, att, 10);
			qq.append(att);
			const char *dwdc = s.c_str();
			const char *dedc = qq.c_str();
			font->drawText("Arial 19", dwdc, -1 + 50 * scaleX, 1 - 580 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			font->drawText("Arial 19", dedc, -1 + 220 * scaleX, 1 - 580 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		}
		int teamSize = playerteam.size();
		//the y position on the screen where do draw the first selectable monster
		int firstMon = 520;
		bool first = true;

			if (playerindex == 0)
			{
				s = "";
				if (_currentSelection == 0 && _currentColumn == 1)
				{
					s = ">>";
				}				
				s.append("swap to ");
				s.append(party1f);
				s.append(displayHPLVLF(party1IDf));
				const char *mon = s.c_str();
				font->drawText("Arial 19", mon, -1 + 360 * scaleX, 1 - 520 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
				s = "";
				if (_currentSelection == 1 && _currentColumn == 1)
				{
					s = ">>";
				}				
				s.append("swap to ");
				s.append(party2f);
				s.append(displayHPLVLF(party2IDf));
				const char *mon1 = s.c_str();
				font->drawText("Arial 19", mon1, -1 + 360 * scaleX, 1 - 540 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}

			if (playerindex == 1)
			{
				s = "";
				if (_currentSelection == 0 && _currentColumn == 1)
				{
					s = ">>";
				}				
				s.append("swap to ");
				s.append(party0f);
				s.append(displayHPLVLF(party0IDf));
				const char *mon = s.c_str();
				font->drawText("Arial 19", mon, -1 + 360 * scaleX, 1 - 520 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
				s = "";
				if (_currentSelection == 1 && _currentColumn == 1)
				{
					s = ">>";
				}				
				s.append("swap to ");
				s.append(party2f);
				s.append(displayHPLVLF(party2IDf));
				const char *mon1 = s.c_str();
				font->drawText("Arial 19", mon, -1 + 360 * scaleX, 1 - 540 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (playerindex == 2)
			{
				s = "";
				if (_currentSelection == 0 && _currentColumn == 1)
				{
					s = ">>";
				}			
				s.append("swap to ");
				s.append(party0f);
				s.append(displayHPLVLF(party0IDf));
				const char *mon = s.c_str();
				font->drawText("Arial 19", mon, -1 + 360 * scaleX, 1 - 520 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
				s = "";
				if (_currentSelection == 1 && _currentColumn == 1)
				{
					s = ">>";
				}			
				s.append("swap to ");
				s.append(party1f);
				s.append(displayHPLVLF(party1IDf));
				const char *mon1 = s.c_str();
				font->drawText("Arial 19", mon, -1 + 360 * scaleX, 1 - 540 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}

			if (_currentSelection == 2 && _currentColumn == 1)
			{
				font->drawText("Arial 19", ">> Items", -1 + 360 * scaleX, 1 - 560 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else{
				font->drawText("Arial 19", "Items", -1 + 360 * scaleX, 1 - 560 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (_currentSelection == 3 && _currentColumn == 1)
			{
				font->drawText("Arial 19", ">> Run", -1 + 360 * scaleX, 1 - 580 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else{
				font->drawText("Arial 19", "Run", -1 + 360 * scaleX, 1 - 580 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}

		if (frametemp > 0)
		{
			if (attacktemp == 0)
			{
				font->drawText("Arial 19", attacks[playerteam[playerindex].att_1 - 1].att_name, -1 + 50 * scaleX, 1 - 250 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (attacktemp == 1)
			{
				font->drawText("Arial 19", attacks[playerteam[playerindex].att_2 - 1].att_name, -1 + 50 * scaleX, 1 - 250 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (attacktemp == 2)
			{
				font->drawText("Arial 19", attacks[playerteam[playerindex].att_3 - 1].att_name, -1 + 50 * scaleX, 1 - 250 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (attacktemp == 3)
			{
				font->drawText("Arial 19", attacks[playerteam[playerindex].att_4 - 1].att_name, -1 + 50 * scaleX, 1 - 250 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (playerMissedF)
			{
				font->drawText("Arial 19", "missed bitched", -1 + 50 * scaleX, 1 - 270 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(plTypOneF * plTypeTwoF == .5)
			{
				font->drawText("Arial 19", "not very", -1 + 50 * scaleX, 1 - 270 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(plTypOneF * plTypeTwoF == 0)
			{
				font->drawText("Arial 19", "yeah no, immune", -1 + 50 * scaleX, 1 - 270 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(plTypOneF * plTypeTwoF == 2)
			{
				font->drawText("Arial 19", "dubs", -1 + 50 * scaleX, 1 - 270 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (eattchran == 0)
			{
				font->drawText("Arial 19", attacks[enemyteam[enemyindex].att_1 - 1].att_name, -1 + 650 * scaleX, 1 - 350 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (eattchran == 1)
			{
				font->drawText("Arial 19", attacks[enemyteam[enemyindex].att_2 - 1].att_name, -1 + 650 * scaleX, 1 - 350 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (eattchran == 2)
			{
				font->drawText("Arial 19", attacks[enemyteam[enemyindex].att_3 - 1].att_name, -1 + 650 * scaleX, 1 - 350 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (eattchran == 3)
			{
				font->drawText("Arial 19", attacks[enemyteam[enemyindex].att_4 - 1].att_name, -1 + 650 * scaleX, 1 - 350 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			if (enemyMissedF)
			{
				font->drawText("Arial 19", "cant touch this", -1 + 650 * scaleX, 1 - 370 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(enTypOneF * enTypeTwoF == .5)
			{
				font->drawText("Arial 19", "not very", -1 + 650 * scaleX, 1 - 370 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(enTypOneF * enTypeTwoF == 0)
			{
				font->drawText("Arial 19", "yeah no, immune", -1 + 650 * scaleX, 1 - 370 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}
			else if(enTypOneF * enTypeTwoF == 2)
			{
				font->drawText("Arial 19", "dubs", -1 + 650 * scaleX, 1 - 370 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
			}

			frametemp--;
		}
		if (frametemp <= 0)
		{
			attacking = false;
			frametemp = 0;
		}

		s = "";
		itoa(playerteam[playerindex].currenthp, att, 10);
		s.append(att);
		s.append("/");

		itoa(playerteam[playerindex].hp, att, 10);
		s.append(att);
		s.append(" HP");
		const char *dwdc = s.c_str();
		font->drawText("Arial 19", dwdc, -1 + 50 * scaleX, 1 - 140 * scaleY, 0.0f, 0.4f, 0.2f, scaleX, scaleY);
		s = "";
		itoa(enemyteam[enemyindex].currenthp, att, 10);

		s.append(att);
		s.append("/");
		itoa(enemyteam[enemyindex].hp, att, 10);
		s.append(att);
		s.append(" HP");
		const char *dedc = s.c_str();
		font->drawText("Arial 19", dedc, -1 + 500 * scaleX, 1 - 70 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		s = "Enemys's ";
		s.append(enemyteam[enemyindex].mst_nickname);
		const char * trrr = s.c_str();
		font->drawText("Arial 19", trrr, -1 + 500 * scaleX, 1 - 50 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//------------acc buff-------------//
		s = "Acc: ";
		itoa(enemyAccBuff, buffF, 10);
		s.append(buffF);
		const char * cb = s.c_str();
		font->drawText("Arial 19", cb, -1 + 410 * scaleX, 1 - 90 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//------level------------//
		s = "Level: ";
		itoa(enemyteam[enemyindex].mst_level, att, 10);
		s.append(att);
		const char * terr = s.c_str();
		font->drawText("Arial 19", terr, -1 + 500 * scaleX, 1 - 90 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//------------attack buff------------//
		s = "Att: ";
		itoa(enemyAttackBuff, buffF, 10);
		s.append(buffF);
		const char * cbb = s.c_str();
		font->drawText("Arial 19", cbb, -1 + 410 * scaleX, 1 - 110 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//----------attack----------------------//
		s = "Attack: ";
		itoa(enemyteam[enemyindex].attack, att, 10);
		s.append(att);
		const char * tetr = s.c_str();
		font->drawText("Arial 19", tetr, -1 + 500 * scaleX, 1 - 110 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//-------def buff--------------//
		s = "Def: ";
		itoa(enemyDefBuff, buffF, 10);
		s.append(buffF);
		const char * cbbb = s.c_str();
		font->drawText("Arial 19", cbbb, -1 + 410 * scaleX, 1 - 130 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//----------def---------------//
		s = "Defence: ";
		itoa(enemyteam[enemyindex].defence, att, 10);
		s.append(att);
		const char * twetr = s.c_str();
		font->drawText("Arial 19", twetr, -1 + 500 * scaleX, 1 - 130 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//-----------speed buff--------------//
		s = "Spd: ";
		itoa(enemySpeedBuff, buffF, 10);
		s.append(buffF);
		const char * cbbbb = s.c_str();
		font->drawText("Arial 19", cbbbb, -1 + 410 * scaleX, 1 - 150 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);
		//------------speed----------------//
		s = "Speed: ";
		itoa(enemyteam[enemyindex].speed, att, 10);
		s.append(att);
		const char * twetf = s.c_str();
		font->drawText("Arial 19", twetf, -1 + 500 * scaleX, 1 - 150 * scaleY, 1.0f, 0.2f, 0.1f, scaleX, scaleY);

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
		entity->draw();
		glPopMatrix();

		// small far
		glPushMatrix();
		glTranslatef(0.2, .05, -.2);
		glRotatef(-10, 0, 0, 1);
		glRotatef(10, 0, 1, 0);
		glRotatef(80, 1, 0, 0);

		glScalef(1.6, 1.6, 1.6);
		//entity2W->draw();
		glPopMatrix();
	}
		
	

	glPopAttrib();

	//////////////////////////////////////////////////////////////////// PLSSSSSSSSSS
	if(battling){
	glUseProgram(0);

	glScalef(0.04, 0.04, 0.04);

	// Create the isometric view
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	float s = .6;

	glOrtho(-1 * s, 1 * s,-1 * s,1 * s, -200, 200);


	glRotatef(45.f, 1.f, 0.f, 0.f);
	glRotatef(-45.f, 0.f, 1.f, 0.f);

	// big close
	glPushMatrix();


	glTranslatef(0.05,0.05,.15);
	glRotatef(170,0,1,0);
glRotatef(-13,0,0,1);
glRotatef(90,1,0,0);
	glScalef(2.7,2.7,2.7);
	entity->draw();
	glPopMatrix();

	// small far
	glPushMatrix();
	glTranslatef(0.2,.05,-.2);
glRotatef(-10,0,0,1);
glRotatef(10,0,1,0);
glRotatef(80,1,0,0);

	glScalef(1.6,1.6,1.6);
	entity2->draw();
	glPopMatrix();
	}
	
	////////////////////////////////////////////////////////////////////////

}
int loadall()
{
	//loadIndex();
	loadSpc();
	loadMst();
	loadAtt();
	loadEff();
	loadTmr();
	loadMvset();
	loadTyp();
	loadEvo();
	loadCnd();
	
	//selectMons();
	load = false;
	selectteams = true;
	return 0;
}
int loadIndex()
{
		INDEX sIndex;
	cout << "exporting " <<"index.dat"<<endl;

	//files
	fstream file_dat (("Database/index.dat"), ios::in | ios::binary); //The dat file with the bits
	fstream file_csv (("index.csv"), ios::out); //the spreadshit that displays the bits
	if(!file_dat.is_open() || !file_csv.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sIndex, sizeof(INDEX));
	   indexes.push_back(sIndex);
      ++record_count;
   }
   file_dat.close();
   file_csv.close();
   cout << record_count << " record(s) processed." << endl;	   
	return 0;
}
int loadSpc()
{
			SPECIES sSpecies;
	cout << "exporting " <<"species.dat"<<endl;

	//files
	fstream file_dat (("Database/species.dat"), ios::in | ios::binary); //The dat file with the bits
	if(!file_dat.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sSpecies, sizeof(SPECIES));
	   species.push_back(sSpecies);
       ++record_count;
   }
   file_dat.close();
   cout << record_count << " record(s) processed." << endl;	   
   return 0;
}
int loadMst()
{
			MONSTER sMonster;
	cout << "exporting " <<"monsters.dat"<<endl;

	//files
	fstream file_dat (("Database/monsters.dat"), ios::in | ios::binary); //The dat file with the bits
	if(!file_dat.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sMonster, sizeof(MONSTER));
	   monsters.push_back(sMonster);
      ++record_count;
   }
   file_dat.close();
   cout << record_count << " record(s) processed." << endl;	   
	return 0;
}
int loadAtt()
{
			ATTACK sAttack;
	cout << "exporting " <<"attacks.dat"<<endl;

	//files
	fstream file_dat (("Database/attacks.dat"), ios::in | ios::binary); //The dat file with the bits
	if(!file_dat.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sAttack, sizeof(ATTACK));
	   attacks.push_back(sAttack);
      ++record_count;
   }
   file_dat.close();
   cout << record_count << " record(s) processed." << endl;	   
	return 0;
}
int loadEff()
{
				EFFECT sEffect;
	cout << "exporting " <<"effects.dat"<<endl;

	//files
	fstream file_dat (("Database/effects.dat"), ios::in | ios::binary); //The dat file with the bits
	if(!file_dat.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sEffect, sizeof(EFFECT));
	   effects.push_back(sEffect);
      ++record_count;
   }
   file_dat.close();
   cout << record_count << " record(s) processed." << endl;	   
	return 0;
}
int loadTmr()
{
				TAMER sTamer;
	cout << "exporting " <<"tamers.dat"<<endl;

	//files
	fstream file_dat (("Database/tamers.dat"), ios::in | ios::binary); //The dat file with the bits
	if(!file_dat.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sTamer, sizeof(TAMER));
	   tamers.push_back(sTamer);
      ++record_count;
   }
   file_dat.close();
   cout << record_count << " record(s) processed." << endl;	   
	return 0;
}
int loadMvset()
{
				MOVESET sMoveset;
	cout << "exporting " <<"movesets.dat"<<endl;

	//files
	fstream file_dat (("Database/movesets.dat"), ios::in | ios::binary); //The dat file with the bits
	if(!file_dat.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sMoveset, sizeof(MOVESET));
	   movesets.push_back(sMoveset);
      ++record_count;
   }
   file_dat.close();
   cout << record_count << " record(s) processed." << endl;	   
	return 0;
}
int loadTyp()
{
				TYPE sType;
	cout << "exporting " <<"types.dat"<<endl;

	//files
	fstream file_dat (("Database/types.dat"), ios::in | ios::binary); //The dat file with the bits
	if(!file_dat.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sType, sizeof(TYPE));
	   types.push_back(sType);
      ++record_count;
   }
   file_dat.close();
   cout << record_count << " record(s) processed." << endl;	   
	return 0;
}
int loadEvo()
{
				EVOLUTION sEvo;
	cout << "exporting " <<"evolutions.dat"<<endl;

	//files
	fstream file_dat (("Database/evolutions.dat"), ios::in | ios::binary); //The dat file with the bits
	if(!file_dat.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sEvo, sizeof(EVOLUTION));
	   evolutions.push_back(sEvo);
      ++record_count;
   }
   file_dat.close();
   cout << record_count << " record(s) processed." << endl;	   
	return 0;
}
int loadCnd()
{
				CONDITION sCnd;
	cout << "exporting " <<"conditions.dat"<<endl;

	//files
	fstream file_dat (("Database/conditions.dat"), ios::in | ios::binary); //The dat file with the bits
	if(!file_dat.is_open())
	{
      return 1;
	}
	file_dat.seekg (0, ios::end);
    streamoff filesize = file_dat.tellg();
	cout << filesize<<endl;
    file_dat.seekg (0, ios::beg);
	file_dat.seekg(0,ios::beg); 
	
    int record_count = 0;

while(file_dat.tellg() < filesize)
   {
     
	   file_dat.read((char*)&sCnd, sizeof(CONDITION));
	   conditions.push_back(sCnd);
      ++record_count;
   }
   file_dat.close();
   cout << record_count << " record(s) processed." << endl;	   
	return 0;
}
int selectMons()
{
	
	return 0;
}
void selectionUp()
{
	
	if(battling)
	{
		--_currentSelection;
		//number of options column 1
		if (_currentSelection < 0 && _currentColumn == 0)
		{
			_currentSelection = attackcount - 1;
		}
		//number of options column 2
		if (_currentSelection == -1 && _currentColumn == 1)
		{
			_currentSelection = 3;
		}
		//handle skipping dash "-" in menu
		if (_currentSelection == 1 && _currentColumn == 1 && party2f == "-")
		{
			_currentSelection = 0;
			if (party1f == "-")
			{
				_currentSelection = 3;
			}

		}
		if (_currentSelection == 1 && _currentColumn == 1 && party1f == "-")
		{
			_currentSelection = 3;
		}
	}
	else
	{
		_currentSelection--;
		if(_currentSelection < 0)
		{
			_currentSelection = monsters.size();
			
		}
		if(_currentSelection <monsters.size()-1 && _currentSelection >= 0)
		{
			string d = species[monsters[_currentSelection].spc_id-1].spc_model;
			currPrev = new Entity(d);
		}
	}
	/*
		--_currentSelection;
	if(!battling)
	{
		if(_currentSelection <monsters.size()-1 && _currentSelection >= 0)
		{
			string d = species[monsters[_currentSelection].spc_id-1].spc_model;
			currPrev = new Entity(d);
		}
	}
	if(_currentSelection < 0)
	{
		if(!battling)
		{
			_currentSelection = monsters.size();
		}
		
		else
		{
			_currentSelection = attackcount-1;
				
		}
	}*/
	
}
void selectionDown()
{
	
	++_currentSelection;
	if(_currentSelection >=5)
	{
		int x = 0;
	}
	if(!battling)
	{
		if(_currentSelection > monsters.size())
		{

			_currentSelection = 0;
		}
		if(_currentSelection <6)
		{
			string d = species[monsters[_currentSelection].spc_id-1].spc_model;
			currPrev = new Entity(d);
		}
	}
	else
	{

		//number of options column 1
		if (_currentSelection > attackcount - 1 && _currentColumn == 0)
		{
			_currentSelection = 0;
		}
		//number of options column 2
		if (_currentSelection == 4 && _currentColumn == 1)
		{
			_currentSelection = 0;
		}
		//handle skipping dash "-" in menu
		if (_currentSelection == 0 && _currentColumn == 1 && party1f == "-")
		{
			_currentSelection = 1;
		}
		if (_currentSelection == 1 && _currentColumn == 1 && party2f == "-")
		{
			_currentSelection = 2;
		}
		
	}
}
void selectionLeft()
{
	if(battling)
	{
		--_currentColumn;
		if (_currentColumn <= -1)
		{
			_currentColumn = 1;
		}
		if (_currentColumn == 0)
		{
			if (attackcount - 1 < _currentSelection)
			{
				_currentSelection = attackcount - 1;
			}
		}

		if (_currentSelection == 0 && _currentColumn == 1 && party1f == "-")
		{
			_currentSelection = 2;
		}
		if (_currentSelection == 1 && _currentColumn == 1 && party2f == "-")
		{
			_currentSelection = 2;
		}
	}
	
}
void selectionRight()
{
		++_currentColumn;
		if (_currentColumn >= 2)
		{
			_currentColumn = 0;
		}
		if (_currentColumn == 0)
		{
			if (attackcount - 1 < _currentSelection)
			{
				_currentSelection = attackcount - 1;
			}
		}

		if (_currentSelection == 0 && _currentColumn == 1 && party1f == "-")
		{
			_currentSelection= 2;
		}
		if (_currentSelection == 1 && _currentColumn == 1 && party2f == "-")
		{
			_currentSelection = 2;
		}
	
}
void select()
{
bool valid = false;
		if (battling && !attacking)
		{
			//BATTLE ROUND START
			
	#pragma region selectAttack
			//PLAYER TURN
			//SELECT ATTACK
			if (_currentColumn == 0)
			{
				attacktemp = _currentSelection;

				attch = 0;

				//everything on cooldown
				if (playerteam[playerindex].cool_1 > 0 && playerteam[playerindex].cool_2 > 0
					&& playerteam[playerindex].cool_3 > 0 && playerteam[playerindex].cool_4 > 0)
				{
					attacktemp = 4;
				}

				//check if valid

				if (attacktemp == 0)
				{
					attch = playerteam[playerindex].att_1;
					valid = (playerteam[playerindex].cool_1 == 0);
				}
				if (attacktemp == 1)
				{
					attch = playerteam[playerindex].att_2;
					valid = (playerteam[playerindex].cool_2 == 0);
				}
				if (attacktemp == 2)
				{
					attch = playerteam[playerindex].att_3;
					valid = (playerteam[playerindex].cool_3 == 0);
				}
				if (attacktemp == 3)
				{
					valid = (playerteam[playerindex].cool_4 == 0);
					attch = playerteam[playerindex].att_4;
				}
				//ENEMY TURN
				//SELECT ATTACK

				int c = 0;
				if (enemyteam[enemyindex].att_1 > 0)
				{
					c++;
				}
				if (enemyteam[enemyindex].att_2 > 0)
				{
					c++;
				}
				if (enemyteam[enemyindex].att_3 > 0)
				{
					c++;
				}
				if (enemyteam[enemyindex].att_4 > 0)
				{
					c++;
				}
				if (valid)
				{
					bool enemyvalid = false;
					//everythin on cool down
					if (enemyteam[enemyindex].cool_1 > 0 && enemyteam[enemyindex].cool_2 > 0
						&& enemyteam[enemyindex].cool_3 > 0 && enemyteam[enemyindex].cool_4 > 0)
					{
						enemyvalid = true;
						eattch = -1;
						eattchran = 4;
					}

					while (!enemyvalid)
					{
						eattch = 0;
						eattchran = rand() % c;
						if (eattchran == 0)
						{
							enemyvalid = (enemyteam[enemyindex].cool_1 == 0);
							eattch = enemyteam[enemyindex].att_1;
						}
						if (eattchran == 1)
						{
							enemyvalid = (enemyteam[enemyindex].cool_2 == 0);
							eattch = enemyteam[enemyindex].att_2;
						}
						if (eattchran == 2)
						{
							enemyvalid = (enemyteam[enemyindex].cool_3 == 0);
							eattch = enemyteam[enemyindex].att_3;
						}
						if (eattchran == 3)
						{
							enemyvalid = (enemyteam[enemyindex].cool_4 == 0);
							eattch = enemyteam[enemyindex].att_4;
						}
					}
					attacksSelected();
				}
				else
				{
				}
			}
	#pragma endregion selectAttack
	#pragma region selectOther
			if (_currentColumn == 1)
			{
				if (_currentSelection == 0)
				{
					//swap to first mon
					if (playerindex == 0)
					{
						if (playerteam[1].currenthp > 0)
						{
							playerindex = 1;
							valid = true;
							playerAccBuff = 0;
							playerSpeedBuff = 0;
							playerDefBuff = 0;
							playerAttackBuff = 0;
							entity->LoadModel(playerteam[playerindex].spc_model);
						}

					}
					else if (playerindex == 1)
					{
						if (playerteam[0].currenthp > 0)
						{
							playerindex = 0;
							valid = true;
							playerAccBuff = 0;
							playerSpeedBuff = 0;
							playerDefBuff = 0;
							playerAttackBuff = 0;
							entity->LoadModel(playerteam[playerindex].spc_model);
						}
					}
					else if (playerindex == 2)
					{
						if (playerteam[0].currenthp > 0)
						{
							playerindex = 0;
							valid = true;
							playerAccBuff = 0;
							playerSpeedBuff = 0;
							playerDefBuff = 0;
							playerAttackBuff = 0;
							entity->LoadModel(playerteam[playerindex].spc_model);
						}

					}

					attch = -1;
					attacktemp = 4;

					int c = 0;
					if (enemyteam[enemyindex].att_1 > 0)
					{
						c++;
					}
					if (enemyteam[enemyindex].att_2 > 0)
					{
						c++;
					}
					if (enemyteam[enemyindex].att_3 > 0)
					{
						c++;
					}
					if (enemyteam[enemyindex].att_4 > 0)
					{
						c++;
					}
					if (valid)
					{
						bool enemyvalid = false;
						if (enemyteam[enemyindex].cool_1 > 0 && enemyteam[enemyindex].cool_2 > 0
							&& enemyteam[enemyindex].cool_3 > 0 && enemyteam[enemyindex].cool_4 > 0)
						{
							enemyvalid = true;
							eattch = -1;
						}

						while (!enemyvalid)
						{
							eattch = 0;
							eattchran = rand() % c;
							if (eattchran == 0)
							{
								enemyvalid = (enemyteam[enemyindex].cool_1 == 0);
								eattch = enemyteam[enemyindex].att_1;
							}
							if (eattchran == 1)
							{
								enemyvalid = (enemyteam[enemyindex].cool_2 == 0);
								eattch = enemyteam[enemyindex].att_2;
							}
							if (eattchran == 2)
							{
								enemyvalid = (enemyteam[enemyindex].cool_3 == 0);
								eattch = enemyteam[enemyindex].att_3;
							}
							if (eattchran == 3)
							{
								enemyvalid = (enemyteam[enemyindex].cool_4 == 0);
								eattch = enemyteam[enemyindex].att_4;
							}
						}
						attacksSelected();
					}


				}
				if (_currentSelection == 1)
				{

					//swap to second mon
					if (playerindex == 0)
					{
						if (playerteam[2].currenthp > 0)
						{
							playerindex = 2;
							valid = true;
							playerAccBuff = 0;
							playerSpeedBuff = 0;
							playerDefBuff = 0;
							playerAttackBuff = 0;
							entity->LoadModel(playerteam[playerindex].spc_model);
						}
					}
					else if (playerindex == 1)
					{
						if (playerteam[2].currenthp > 0)
						{
							playerindex = 2;
							valid = true;
							playerAccBuff = 0;
							playerSpeedBuff = 0;
							playerDefBuff = 0;
							playerAttackBuff = 0;
							entity->LoadModel(playerteam[playerindex].spc_model);
						}
					}
					else if (playerindex == 2)
					{
						if (playerteam[1].currenthp > 0)
						{
							playerindex = 1;
							valid = true;
							playerAccBuff = 0;
							playerSpeedBuff = 0;
							playerDefBuff = 0;
							playerAttackBuff = 0;
							entity->LoadModel(playerteam[playerindex].spc_model);
						}
					}



					attch = -1;
					attacktemp = 4;

					int c = 0;
					if (enemyteam[enemyindex].att_1 > 0)
					{
						c++;
					}
					if (enemyteam[enemyindex].att_2 > 0)
					{
						c++;
					}
					if (enemyteam[enemyindex].att_3 > 0)
					{
						c++;
					}
					if (enemyteam[enemyindex].att_4 > 0)
					{
						c++;
					}
					if (valid)
					{
						bool enemyvalid = false;
						if (enemyteam[enemyindex].cool_1 > 0 && enemyteam[enemyindex].cool_2 > 0
							&& enemyteam[enemyindex].cool_3 > 0 && enemyteam[enemyindex].cool_4 > 0)
						{
							enemyvalid = true;
							eattch = -1;
						}

						while (!enemyvalid)
						{
							eattch = 0;
							eattchran = rand() % c;
							if (eattchran == 0)
							{
								enemyvalid = (enemyteam[enemyindex].cool_1 == 0);
								eattch = enemyteam[enemyindex].att_1;
							}
							if (eattchran == 1)
							{
								enemyvalid = (enemyteam[enemyindex].cool_2 == 0);
								eattch = enemyteam[enemyindex].att_2;
							}
							if (eattchran == 2)
							{
								enemyvalid = (enemyteam[enemyindex].cool_3 == 0);
								eattch = enemyteam[enemyindex].att_3;
							}
							if (eattchran == 3)
							{
								enemyvalid = (enemyteam[enemyindex].cool_4 == 0);
								eattch = enemyteam[enemyindex].att_4;
							}
						}
						attacksSelected();
					}

				}
				//items
				if (_currentSelection == 2)
				{//cant use items
				}
				//run
				if (_currentSelection == 3)
				{
					runn = true;
					battleover = true;
					battling = false;
					screenCounterF = 350;
				}

			}
	#pragma endregion
		}
		

	///other
if(_currentSelection == monsters.size())
{
	if(!teamone)
	{
		teamone =true;
		playerdudes = monindex-1;
		startingplayer = playerdudes;
		monindex = 1;
	}
	else
	{
		enemydudes = monindex-1;
		startingenemy = enemydudes;
		teamtwo = true;
	}
}
else if(!teamone)
{
	MONSTERACTUAL monactual;

	int monone = 0;
	monone = _currentSelection;
	
	cout<<"you loaded: " << monsters[monone].mst_nickname << " the " << species[monsters[monone].spc_id-1].spc_name<<endl<<endl;
	
	monactual.attack =  (species[monsters[monone].spc_id-1].spc_attack * 2 * monsters[monone].mst_level / 100) + 5;
	monactual.defence =  (species[monsters[monone].spc_id-1].spc_defence * 2 * monsters[monone].mst_level / 100) + 5;
	monactual.speed =  (species[monsters[monone].spc_id-1].spc_speed * 2 * monsters[monone].mst_level / 100) + 5;
	monactual.hp =  (species[monsters[monone].spc_id-1].spc_hp * 2 * monsters[monone].mst_level / 100) + 5;
	monactual.currenthp = monactual.hp;
	monactual.mst_id = monsters[monone].mst_id;
	monactual.mst_level = monsters[monone].mst_level;
	strcpy (monactual.mst_nickname, monsters[monone].mst_nickname);
	//monactual.mst_nickname = monsters[monone].mst_nickname;
	monactual.typ_1 = species[monsters[monone].spc_id-1].typ_1;
	monactual.typ_2 = species[monsters[monone].spc_id-1].typ_2;
	monactual.att_1 = monsters[monone].mst_attack1;
	monactual.att_2 = monsters[monone].mst_attack2;
    monactual.att_3 = monsters[monone].mst_attack3;
	monactual.att_4 = monsters[monone].mst_attack4;
	monactual.cool_1 = 0;
	monactual.cool_2 = 0;
	monactual.cool_3 = 0;
	monactual.cool_4 = 0;
	strcpy(monactual.spc_model, species[monsters[monone].spc_id-1].spc_model);
	//monactual.spc_model = species[monsters[monone].spc_id].spc_model;
	strcpy(monactual.spc_name, species[monsters[monone].spc_id-1].spc_name);
	//monactual.spc_name = species[monsters[monone].spc_id].spc_name;
	
	playerteam.push_back(monactual);
	string d = monactual.spc_model;
		Entity* curr = new Entity(d);
		prevs.push_back(curr);
	monindex++;
	if(monindex==4)
	{
		playerdudes = 3;
		startingplayer = 3;
		monindex=1;
		teamone = true;
	}

}
else if(!teamtwo)
{
	MONSTERACTUAL monactual;
	int monone = 0;
	monone = _currentSelection;
	
	cout<<"you loaded: " << monsters[monone].mst_nickname << " the " << species[monsters[monone].spc_id-1].spc_name<<endl<<endl;
	
	monactual.attack =  (species[monsters[monone].spc_id-1].spc_attack * 2 * monsters[monone].mst_level / 100) + 5;
	monactual.defence =  (species[monsters[monone].spc_id-1].spc_defence * 2 * monsters[monone].mst_level / 100) + 5;
	monactual.speed =  (species[monsters[monone].spc_id-1].spc_speed * 2 * monsters[monone].mst_level / 100) + 5;
	monactual.hp =  (species[monsters[monone].spc_id-1].spc_hp * 2 * monsters[monone].mst_level / 100) + 5;
	monactual.currenthp = monactual.hp;
	monactual.mst_id = monsters[monone].mst_id;
	monactual.mst_level = monsters[monone].mst_level;
	strcpy (monactual.mst_nickname, monsters[monone].mst_nickname);
	//monactual.mst_nickname = monsters[monone].mst_nickname;
	monactual.typ_1 = species[monsters[monone].spc_id-1].typ_1;
	monactual.typ_2 = species[monsters[monone].spc_id-1].typ_2;
	monactual.att_1 = monsters[monone].mst_attack1;
	monactual.att_2 = monsters[monone].mst_attack2;
    monactual.att_3 = monsters[monone].mst_attack3;
	monactual.att_4 = monsters[monone].mst_attack4;
	monactual.cool_1 = 0;
	monactual.cool_2 = 0;
	monactual.cool_3 = 0;
	monactual.cool_4 = 0;
	strcpy(monactual.spc_model, species[monsters[monone].spc_id-1].spc_model);
	//monactual.spc_model = species[monsters[monone].spc_id].spc_model;
	strcpy(monactual.spc_name, species[monsters[monone].spc_id-1].spc_name);
	//monactual.spc_name = species[monsters[monone].spc_id].spc_name;
	
	enemyteam.push_back(monactual);
	string d = monactual.spc_model;
		Entity* curr = new Entity(d);
		prevs.push_back(curr);
	monindex++;
	if(monindex==4)
	{enemydudes = 3;
	startingenemy =3;
		monindex=1;
		teamtwo = true;
		//_currentSelection = 0;
	}
}
	if(teamtwo && !battling && !battlestart)
	{
		selectteams = false;
		if(!battlestart)
		{
			_currentSelection = 0;
		}
		if(!battling && !battleover)
		{
		battlestart = true;
		}
		//_currentSelection = 0;
	}

}
void attacksSelected()
{
	frametemp = 60;
		attacking = true;
	if(playerteam[playerindex].speed >= enemyteam[enemyindex].speed)
		{
			handlePlayer();
			handleEnemy();
					
		}
		else
		{
			//enemy does damage
			//player takes damage
			//check if player dead
			//check if player out of monsters
			handleEnemy();

			//player does damage
			//enemy takes damage
			//check if enemy dead
			//check if enemy out of monsters
			handlePlayer();
		}
		
		
		
}
void handlePlayer()
{
			plTypOneF = 1, plTypeTwoF = 1;
	//PLAYER HANDLE
	if (attacking)
	{
		playerMissedF = false;
		int xx = 0;
		int baseModAcc = 1 + (playerAccBuff / 3);
		if (attch != -1)
		{

			if ((attacks[attch - 1].att_acc * baseModAcc) >= (rand() % 100 + 1))
			{
				if (attacks[attch - 1].eff_id == 0)
				{
					double baseModAtt = 1 + (playerAccBuff / 2);
					double baseModDef = 1 + (enemyDefBuff / 2);
					double dmgRange = (rand() % 15 + 85) / 100.0;
					double att = baseModAtt * attacks[attch - 1].att_pow;
					double def = baseModDef * enemyteam[enemyindex].defence;
					//change battle formula
					//player does damage		
					xx = ((2 * playerteam[playerindex].mst_level * att *  (att / def)) / 50) * dmgRange;
					if (attacktemp == 4)
					{
						xx = 0;
					}
					if(enemyteam[enemyindex].typ_1-5>=0 && attacks[attch-1].typ_1-5 >= 0)
					{
						plTypOneF= typesMatch[enemyteam[enemyindex].typ_1-5][attacks[attch-1].typ_1-5];
					}
					if(playerteam[enemyindex].typ_2-5>=0 && attacks[eattch-1].typ_1-5 >= 0)
					{
						plTypeTwoF = typesMatch[enemyteam[enemyindex].typ_2-5][attacks[attch-1].typ_1-5];
					}
					xx *= plTypOneF*plTypeTwoF;
				}
				//do work here
				else{
					switch (attacks[attch - 1].eff_id)
					{
						//self buffs
					case 2:
						playerAttackBuff += attacks[attch - 1].att_pow;
						break;
					case 4:
						playerDefBuff += attacks[attch - 1].att_pow;
						break;
					case 6:
						playerSpeedBuff += attacks[attch - 1].att_pow;
						break;
					case 8:
						playerAccBuff += attacks[attch - 1].att_pow;
						break;
						//debuffs on enemy
					case 1:
						enemyAttackBuff += attacks[attch - 1].att_pow;
						break;
					case 3:
						enemyDefBuff += attacks[attch - 1].att_pow;
						break;
					case 5:
						enemySpeedBuff += attacks[attch - 1].att_pow;
						break;
					case 7:
						enemyAccBuff += attacks[attch - 1].att_pow;
						break;
					}
				}
			}
			else
			{
				playerMissedF = true;
			}
		}
		//apply cooldown
		switch (attacktemp)
		{
		case 0:
			playerteam[playerindex].cool_1 = attacks[playerteam[playerindex].att_1 - 1].att_cool;
			playerteam[playerindex].cool_2--;
			playerteam[playerindex].cool_3--;
			playerteam[playerindex].cool_4--;
			break;
		case 1:
			playerteam[playerindex].cool_2 = attacks[playerteam[playerindex].att_2 - 1].att_cool;
			playerteam[playerindex].cool_1--;
			playerteam[playerindex].cool_3--;
			playerteam[playerindex].cool_4--;
			break;
		case 2:
			playerteam[playerindex].cool_3 = attacks[playerteam[playerindex].att_3 - 1].att_cool;
			playerteam[playerindex].cool_1--;
			playerteam[playerindex].cool_2--;
			playerteam[playerindex].cool_4--;
			break;
		case 3:
			playerteam[playerindex].cool_4 = attacks[playerteam[playerindex].att_4 - 1].att_cool;
			playerteam[playerindex].cool_1--;
			playerteam[playerindex].cool_2--;
			playerteam[playerindex].cool_3--;
			break;
		case 4:
			playerteam[playerindex].cool_1--;
			playerteam[playerindex].cool_2--;
			playerteam[playerindex].cool_3--;
			playerteam[playerindex].cool_4--;
			break;
		}
		if (playerteam[playerindex].cool_1 < 0)
		{
			playerteam[playerindex].cool_1 = 0;
		}
		if (playerteam[playerindex].cool_2 < 0)
		{
			playerteam[playerindex].cool_2 = 0;
		}
		if (playerteam[playerindex].cool_3 < 0)
		{
			playerteam[playerindex].cool_3 = 0;
		}
		if (playerteam[playerindex].cool_4 < 0)
		{
			playerteam[playerindex].cool_4 = 0;
		}

		//enemy takes damage
		enemyteam[enemyindex].currenthp -= xx;
		//check if enemy dead
		if (enemyteam[enemyindex].currenthp <= 0)
		{
			enemyteam[enemyindex].currenthp = 0;
			enemydudes--;
			eattchran = -1;
			attacking = false; // end the attack loop, cant hit if dead
			//enemydead;
			//levelup();
			//check if enemy out of monsters
			if (enemydudes <= 0)
			{
				//battle won by player
				enemyloses = true;
				battling = false;
				battleover = true;
			//	playerwins();
				return;
			}
			else
			{
				//HANDLE NEW DUDE
				//change index;
				//ai SELECT after
				for (int i = 0; i < startingenemy; i++)
				{
					if (enemyteam[i].currenthp > 0)
					{
						//change dude animation
						enemyindex = i;
						enemyAccBuff = 0;
						enemySpeedBuff = 0;
						enemyDefBuff = 0;
						enemyAttackBuff = 0;
						entity2->LoadModel(enemyteam[enemyindex].spc_model);
					}
				}
			}
		}
	}
}
void handleEnemy()
{
		//ENEMY HANDLE
	enTypOneF = 1, enTypeTwoF = 1;
	enemyMissedF = false;
	if (attacking)
	{
		//enemy does damage
		int yy = 0;
		int baseModAcc = 1 + (enemyAccBuff / 3);
		if (eattch != -1)
		{
			if ((attacks[eattch - 1].att_acc * baseModAcc) >= (rand() % 100 + 1))
			{
				if (attacks[eattch - 1].eff_id == 0)
				{
					double dmgRange = (rand() % 15 + 85) / 100.0;
					//change battle formula
					//player does damage						
					double baseModAtt = 1 + (enemyAttackBuff / 2);
					double baseModDef = 1 + (playerDefBuff / 2);
					double att = baseModAtt * attacks[eattch - 1].att_pow;
					double def = baseModDef * playerteam[playerindex].defence;
					if (eattch > 0)
					{
						yy = ((2 * enemyteam[enemyindex].mst_level * att *  (att / def)) / 50) * dmgRange;
						if(playerteam[playerindex].typ_1-5>=0 && attacks[eattch-1].typ_1-5 >= 0)
						{
						enTypOneF = typesMatch[playerteam[playerindex].typ_1-5][attacks[eattch-1].typ_1-5];
						}
						if(playerteam[playerindex].typ_2-5>=0 && attacks[eattch-1].typ_1-5 >= 0)
						{
						enTypeTwoF = typesMatch[playerteam[playerindex].typ_2-5][attacks[eattch-1].typ_1-5];
						}
						yy *= enTypOneF*enTypeTwoF;
					}
				}
				else
				{
					switch (attacks[eattch - 1].eff_id)
					{
						//self buffs
					case 2:
						enemyAttackBuff += attacks[eattch - 1].att_pow;
						break;
					case 4:
						enemyDefBuff += attacks[eattch - 1].att_pow;
						break;
					case 6:
						enemySpeedBuff += attacks[eattch - 1].att_pow;
						break;
					case 8:
						enemyAccBuff += attacks[eattch - 1].att_pow;
						break;
						//debuffs on player
					case 1:
						playerAttackBuff += attacks[eattch - 1].att_pow;
						break;
					case 3:
						playerDefBuff += attacks[eattch - 1].att_pow;
						break;
					case 5:
						playerSpeedBuff += attacks[eattch - 1].att_pow;
						break;
					case 7:
						playerAccBuff += attacks[eattch - 1].att_pow;
						break;
					}
				}
			}
			else
			{
				enemyMissedF = true;
			}
		}

		//player takes damage

		//apply cooldown
		///decrease other cooldowns
		switch (eattchran)
		{
		case 0:
			enemyteam[enemyindex].cool_1 = attacks[enemyteam[enemyindex].att_1 - 1].att_cool;
			enemyteam[enemyindex].cool_2--;
			enemyteam[enemyindex].cool_3--;
			enemyteam[enemyindex].cool_4--;
			break;
		case 1:
			enemyteam[enemyindex].cool_2 = attacks[enemyteam[enemyindex].att_2 - 1].att_cool;
			enemyteam[enemyindex].cool_1--;
			enemyteam[enemyindex].cool_3--;
			enemyteam[enemyindex].cool_4--;
			break;
		case 2:
			enemyteam[enemyindex].cool_3 = attacks[enemyteam[enemyindex].att_3 - 1].att_cool;
			enemyteam[enemyindex].cool_2--;
			enemyteam[enemyindex].cool_1--;
			enemyteam[enemyindex].cool_4--;
			break;
		case 3:
			enemyteam[enemyindex].cool_4 = attacks[enemyteam[enemyindex].att_4 - 1].att_cool;
			enemyteam[enemyindex].cool_2--;
			enemyteam[enemyindex].cool_3--;
			enemyteam[enemyindex].cool_1--;
			break;
		case 4:
			enemyteam[enemyindex].cool_1--;
			enemyteam[enemyindex].cool_2--;
			enemyteam[enemyindex].cool_3--;
			enemyteam[enemyindex].cool_4--;
			break;
		}
		//reset negative cooldowns to 0
		if (enemyteam[enemyindex].cool_1 < 0)
		{
			enemyteam[enemyindex].cool_1 = 0;
		}
		if (enemyteam[enemyindex].cool_2 < 0)
		{
			enemyteam[enemyindex].cool_2 = 0;
		}
		if (enemyteam[enemyindex].cool_3 < 0)
		{
			enemyteam[enemyindex].cool_3 = 0;
		}
		if (enemyteam[enemyindex].cool_4 < 0)
		{
			enemyteam[enemyindex].cool_4 = 0;
		}
		playerteam[playerindex].currenthp -= yy;
		//check if player dead
		if (playerteam[playerindex].currenthp <= 0)
		{
			playerteam[playerindex].currenthp = 0;
			playerdudes--;
			attacktemp = -1;
			attacking = false;
			//playerdead;
			//check if player out of monsters
			if (playerdudes <= 0)
			{
				//battle won by enemy

				playerloses = true;
				
				return;

			}
			else
			{
				//HANDLE NEW DUDE
				//change index;
				//player SELECT after
				//fontW->drawText(
				for (int i = 0; i < startingplayer; i++)
				{
					if (playerteam[i].currenthp > 0)
					{
						//change dude animation
						playerindex = i;
						playerAccBuff = 0;
						playerSpeedBuff = 0;
						playerDefBuff = 0;
						playerAttackBuff = 0;
						entity->LoadModel(playerteam[playerindex].spc_model);
					}
				}
			}

		}
	}
}