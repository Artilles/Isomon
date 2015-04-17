#include "include\OverworldMenu.h"
#pragma pack(1)
#include "database_types.h"
#include "engine_types.h"
#include "World.h"
#include "include\GameWindow.h"
#include "include\PlayState.h"
#include "include\MenuState.h"



OverworldMenu::OverworldMenu()
{
	font->createFont("Arial 36", "resource/fonts/arialbd.ttf", 36, 0);
	font->createFont("Arial 14", "resource/fonts/arial.ttf", 14, 0);
	font->createFont("Arial 12", "resource/fonts/arial.ttf", 12, 0);

	_selected = 0;
	_lastKey = -1;
	_infoSelected = 0;
	_itemSelected = 0;
	_monsterNumber = 0;
	_itemWindow = false;
	_monsterWindow = false;
}


OverworldMenu::~OverworldMenu()
{
}


void OverworldMenu::update(vector<MONSTERACTUAL> playerteamW)
{
	GLFWwindow* window = glfwGetCurrentContext();

	if (!_monsterWindow && !_itemWindow)
	{
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && _lastKey != GLFW_KEY_UP)
		{
			--_selected;
			if (_selected < 0)
				_selected = playerteamW.size() - 1 + 4;
			_lastKey = GLFW_KEY_UP;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && _lastKey != GLFW_KEY_DOWN)
		{
			++_selected;
			if (_selected > playerteamW.size() - 1 + 4)
				_selected = 0;
			_lastKey = GLFW_KEY_DOWN;
		}
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && _lastKey != GLFW_KEY_ENTER)
		{
			select();
			_lastKey = GLFW_KEY_ENTER;
		}
	}
	else if (_monsterWindow)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && _lastKey != GLFW_KEY_LEFT)
		{
			--_infoSelected;
			if (_infoSelected < 0)
				_infoSelected = 1;
			_lastKey = GLFW_KEY_LEFT;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && _lastKey != GLFW_KEY_RIGHT)
		{
			++_infoSelected;
			if (_infoSelected > 1)
				_infoSelected = 0;
			_lastKey = GLFW_KEY_RIGHT;
		}
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && _lastKey != GLFW_KEY_ENTER)
		{
			selectInfo();
			_lastKey = GLFW_KEY_ENTER;
		}
	}
	else if (_itemWindow)
	{
		/*if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && _lastKey != GLFW_KEY_UP)
		{
			--_itemSelected;
			if (_itemSelected < 0)
				_itemSelected = 3;
			_lastKey = GLFW_KEY_UP;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && _lastKey != GLFW_KEY_DOWN)
		{
			++_itemSelected;
			if (_itemSelected > 3)
				_itemSelected = 0;
			_lastKey = GLFW_KEY_DOWN;
		}*/
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && _lastKey != GLFW_KEY_ENTER)
		{
			selectItem();
			_lastKey = GLFW_KEY_ENTER;
		}
	}

	// Key Reset
	if (_lastKey != -1)
	{
		if (glfwGetKey(window, _lastKey) == GLFW_RELEASE)
			_lastKey = -1;
	}
}


void OverworldMenu::render(vector<MONSTERACTUAL> playerteamW, int playerindexW, vector<TYPE> typesW, vector<ATTACK> attacksW, vector<ITEM> items)
{
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);

#pragma region Pause Menu
	glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
	glBegin(GL_QUADS);
	glVertex2d(9, -13);
	glVertex2d(9, 15);
	glVertex2d(22, 15);
	glVertex2d(22, -13);
	glEnd();

	glColor4f(0.45f, 0.45f, 0.45f, 0.9f);
	glBegin(GL_LINES);
	glLineWidth(1.5f);
	glVertex2d(9, -13);
	glVertex2d(9, 15);
	glVertex2d(9, 15);
	glVertex2d(22, 15);
	glVertex2d(22, 15);
	glVertex2d(22, -13);
	glVertex2d(22, -13);
	glVertex2d(9, -13);
	// View All
	glVertex2d(13, -12);
	glVertex2d(13, -10.5);
	glVertex2d(18, -12);
	glVertex2d(18, -10.5);
	glVertex2d(13, -12);
	glVertex2d(18, -12);
	glVertex2d(13, -10.5);
	glVertex2d(18, -10.5);
	glColor4f(0.4f, 0.4f, 0.4f, 0.6f);
	glVertex2d(9, 11.5);
	glVertex2d(22, 11.5);
	glVertex2d(9, 3.3);
	glVertex2d(22, 3.3);
	glEnd();

	if (_selected == 4)
	{
		glColor4f(0.55f, 0.55f, 0.55f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2d(9.1, 3.15);
		glVertex2d(9.1, -0.6);
		glVertex2d(21.9, -0.6);
		glVertex2d(21.9, 3.15);
		glEnd();
	}
	else if (_selected == 5)
	{
		glColor4f(0.55f, 0.55f, 0.55f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2d(9.1, -0.6);
		glVertex2d(9.1, -4.4);
		glVertex2d(21.9, -4.4);
		glVertex2d(21.9, -0.6);
		glEnd();
	}
	else if (_selected == 6)
	{
		glColor4f(0.55f, 0.55f, 0.55f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2d(9.1, -4.4);
		glVertex2d(9.1, -8.2);
		glVertex2d(21.9, -8.2);
		glVertex2d(21.9, -4.4);
		glEnd();
	}
	else if (_selected == playerteamW.size() + 4)
	{
		glColor4f(0.55f, 0.55f, 0.55f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2d(13, -10.5);
		glVertex2d(13, -12);
		glVertex2d(18, -12);
		glVertex2d(18, -10.5);
		glEnd();
	}

	// View All


	int windowSizeX = 0;
	int windowSizeY = 0;
	glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
	float scaleX = (float)(2.0f / windowSizeX);
	float scaleY = (float)(2.0f / windowSizeY);

	font->drawText("Arial 36", "PAUSED", -1 + 1070 * scaleX, 1 - 170 * scaleY, 0.9f, 0.4f, 0.1f, scaleX, scaleY);
	// Menu Items			
	if (_selected == 0)
		font->drawText("Arial 18", "> Items", -1 + 980 * scaleX, 1 - 211 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
	else
		font->drawText("Arial 18", "Items", -1 + 996 * scaleX, 1 - 211 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);

	if (_selected == 1)
		font->drawText("Arial 18", "> Save", -1 + 980 * scaleX, 1 - 241 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
	else
		font->drawText("Arial 18", "Save", -1 + 996 * scaleX, 1 - 241 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);

	if (_selected == 2)
		font->drawText("Arial 18", "> Quit", -1 + 980 * scaleX, 1 - 271 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
	else
		font->drawText("Arial 18", "Quit", -1 + 996 * scaleX, 1 - 271 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);

	if (_selected == 3)
		font->drawText("Arial 18", "> Exit", -1 + 980 * scaleX, 1 - 301 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
	else
		font->drawText("Arial 18", "Exit", -1 + 996 * scaleX, 1 - 301 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);

	// Monster Stats
	// Monster #1
	char attW[15];
	if (playerteamW.size() > 0)
	{		
		string s = "";

		s.append(playerteamW[0].mst_nickname);
		if (playerindexW == 0)
			s.append("  (current)");
		font->drawText("Arial 14", s.c_str(), -1 + 970 * scaleX, 1 - 346 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		s = "Level: ";
		itoa(playerteamW[0].mst_level, attW, 10);
		s.append(attW);
		font->drawText("Arial 12", s.c_str(), -1 + 970 * scaleX, 1 - 358 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		s = "HP: ";
		itoa(playerteamW[0].currenthp, attW, 10);
		s.append(attW);
		s.append(" / ");
		itoa(playerteamW[0].hp, attW, 10);
		s.append(attW);
		font->drawText("Arial 12", s.c_str(), -1 + 1250 * scaleX, 1 - 358 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		s = "Exp: ";
		itoa(playerteamW[0].mst_xp, attW, 10);
		s.append(attW);
		s.append(" / ");
		int xpfornext = (4 * (playerteamW[0].mst_level + 1) *(playerteamW[0].mst_level + 1)*(playerteamW[0].mst_level + 1)) / 5;
		itoa(xpfornext, attW, 10);
		s.append(attW);
		font->drawText("Arial 12", s.c_str(), -1 + 970 * scaleX, 1 - 370 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
	}
	// Monster #2
	if (playerteamW.size() > 1)
	{
		string s = "";
		
		s.append(playerteamW[1].mst_nickname);
		if (playerindexW == 1)
			s.append("  (current)");
		font->drawText("Arial 14", s.c_str(), -1 + 970 * scaleX, 1 - 410 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		s = "Level: ";
		itoa(playerteamW[1].mst_level, attW, 10);
		s.append(attW);
		font->drawText("Arial 12", s.c_str(), -1 + 970 * scaleX, 1 - 422 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		s = "HP: ";
		itoa(playerteamW[1].currenthp, attW, 10);
		s.append(attW);
		s.append(" / ");
		itoa(playerteamW[1].hp, attW, 10);
		s.append(attW);
		font->drawText("Arial 12", s.c_str(), -1 + 1250 * scaleX, 1 - 422 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		s = "Exp: ";
		itoa(playerteamW[1].mst_xp, attW, 10);
		s.append(attW);
		s.append(" / ");
		int xpfornext = (4 * (playerteamW[1].mst_level + 1) *(playerteamW[1].mst_level + 1)*(playerteamW[1].mst_level + 1)) / 5;
		itoa(xpfornext, attW, 10);
		s.append(attW);
		font->drawText("Arial 12", s.c_str(), -1 + 970 * scaleX, 1 - 434 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
	}
	// Monster #3
	if (playerteamW.size() > 2)
	{
		string s = "";

		s.append(playerteamW[2].mst_nickname);
		if (playerindexW == 2)
			s.append("  (current)");
		font->drawText("Arial 14", s.c_str(), -1 + 970 * scaleX, 1 - 474 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		s = "Level: ";
		itoa(playerteamW[2].mst_level, attW, 10);
		s.append(attW);
		font->drawText("Arial 12", s.c_str(), -1 + 970 * scaleX, 1 - 486 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		s = "HP: ";
		itoa(playerteamW[2].currenthp, attW, 10);
		s.append(attW);
		s.append(" / ");
		itoa(playerteamW[2].hp, attW, 10);
		s.append(attW);
		font->drawText("Arial 12", s.c_str(), -1 + 1250 * scaleX, 1 - 486 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		s = "Exp: ";
		itoa(playerteamW[2].mst_xp, attW, 10);
		s.append(attW);
		s.append(" / ");
		int xpfornext = (4 * (playerteamW[2].mst_level + 1) *(playerteamW[2].mst_level + 1)*(playerteamW[2].mst_level + 1)) / 5;
		itoa(xpfornext, attW, 10);
		s.append(attW);
		font->drawText("Arial 12", s.c_str(), -1 + 970 * scaleX, 1 - 498 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
	}
	font->drawText("Arial 12", "View All", -1 + 1130 * scaleX, 1 - 578 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);

	glUseProgram(0);
#pragma endregion	

#pragma region Monster Info
	if (_monsterWindow)
	{
		glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
		glBegin(GL_QUADS);
		glVertex2d(-9, -10);
		glVertex2d(-9, 15);
		glVertex2d(8.5, 15);
		glVertex2d(8.5, -10);
		glEnd();

		glColor4f(0.45f, 0.45f, 0.45f, 0.9f);
		glBegin(GL_LINES);
		glLineWidth(1.5f);
		glVertex2d(-9, -10);
		glVertex2d(-9, 15);
		glVertex2d(-9, 15);
		glVertex2d(8.5, 15);
		glVertex2d(8.5, 15);
		glVertex2d(8.5, -10);
		glVertex2d(8.5, -10);
		glVertex2d(-9, -10);
		glColor4f(0.4f, 0.4f, 0.4f, 0.6f);
		glVertex2d(-9, 11.5);
		glVertex2d(8.5, 11.5);
		glEnd();

		if (_infoSelected == 0)
		{
			glColor4f(0.55f, 0.55f, 0.55f, 0.35f);
			glBegin(GL_QUADS);
			glVertex2d(-7, -7.5);
			glVertex2d(-7, -9);
			glVertex2d(-1.5, -9);
			glVertex2d(-1.5, -7.5);
			glEnd();
		}
		else if (_infoSelected == 1)
		{
			glColor4f(0.55f, 0.55f, 0.55f, 0.35f);
			glBegin(GL_QUADS);
			glVertex2d(6.5, -7.5);
			glVertex2d(6.5, -9);
			glVertex2d(1, -9);
			glVertex2d(1, -7.5);
			glEnd();
		}

		// Make Current outline
		glColor4f(0.45f, 0.45f, 0.45f, 0.9f);
		glBegin(GL_LINES);
		glVertex2d(-7, -7.5);
		glVertex2d(-7, -9);
		glVertex2d(-1.5, -7.5);
		glVertex2d(-1.5, -9);
		glVertex2d(-7, -7.5);
		glVertex2d(-1.5, -7.5);
		glVertex2d(-7, -9);
		glVertex2d(-1.5, -9);
		glEnd();
		// Close outline
		glColor4f(0.45f, 0.45f, 0.45f, 0.9f);
		glBegin(GL_LINES);
		glVertex2d(6.5, -7.5);
		glVertex2d(6.5, -9);
		glVertex2d(1, -7.5);
		glVertex2d(1, -9);
		glVertex2d(6.5, -7.5);
		glVertex2d(1, -7.5);
		glVertex2d(6.5, -9);
		glVertex2d(1, -9);
		glEnd();

		int s = _selected - 4;
		string t = "";
		t.append("Level ");
		t.append(itoa(playerteamW[s].mst_level, attW, 10));
		font->drawText("Arial 36", playerteamW[s].mst_nickname, -1 + 435 * scaleX, 1 - 166 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		font->drawText("Arial 36", t.c_str(), -1 + 780 * scaleX, 1 - 166 * scaleY, 0.9f, 0.4f, 0.1f, scaleX, scaleY);
		// Left Column
		//hp
		t = "HP: ";
		t.append(itoa(playerteamW[s].currenthp, attW, 10));
		t.append(" / ");
		t.append(itoa(playerteamW[s].hp, attW, 10));
		font->drawText("Arial 12", t.c_str(), -1 + 435 * scaleX, 1 - 410 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		//exp	
		t = "Exp: ";
		int xpfornext = (4 * (playerteamW[s].mst_level + 1) *(playerteamW[s].mst_level + 1)*(playerteamW[s].mst_level + 1)) / 5;
		t.append(itoa(playerteamW[s].mst_xp, attW, 10));
		t.append(" / ");
		t.append(itoa(xpfornext, attW, 10));
		font->drawText("Arial 12", t.c_str(), -1 + 435 * scaleX, 1 - 424 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		//type
		t = "Type: ";
		t.append(typesW[playerteamW[s].typ_1].typ_detail);
		font->drawText("Arial 12", t.c_str(), -1 + 435 * scaleX, 1 - 438 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		if (playerteamW[s].typ_2 != 0)
		{
			t = "";
			//t.append(" | ");
			t.append(typesW[playerteamW[s].typ_2].typ_detail);
			font->drawText("Arial 12", t.c_str(), -1 + 468 * scaleX, 1 - 452 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		}

		attacksW[playerteamW[s].att_1 - 1].att_name;
		// Right Column
		font->drawText("Arial 14", "Attacks", -1 + 680 * scaleX, 1 - 410 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		//font->drawText("Arial 12", attacksW[playerteamW[s].att_1 - 1].att_name, -1 + 420 * scaleX, 1 - 324 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		if (playerteamW[s].att_1 > 0)
		{
			t = "";
			t.append(attacksW[playerteamW[s].att_1 - 1].att_name);
			//t.append("	Type:  ");
			t.append(" - ");
			t.append(typesW[attacksW[playerteamW[s].att_1 - 1].typ_1].typ_detail);
			t.append(" - CD: ");
			t.append(itoa(playerteamW[s].cool_1,attW,10));
			//t.append("turns");


			font->drawText("Arial 12", t.c_str(), -1 + 680 * scaleX, 1 - 424 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		}
		if (playerteamW[s].att_2 > 0)
		{
			t = "";
			t.append(attacksW[playerteamW[s].att_2 - 1].att_name);
			//t.append("	Type:  ");
			t.append(" - ");
			t.append(typesW[attacksW[playerteamW[s].att_2 - 1].typ_1].typ_detail);
			t.append(" - CD: ");
			t.append(itoa(playerteamW[s].cool_2, attW, 10));
			//t.append("turns");
			font->drawText("Arial 12", t.c_str(), -1 + 680 * scaleX, 1 - 438 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		}
		if (playerteamW[s].att_3 > 0)
		{
			t = "";
			t.append(attacksW[playerteamW[s].att_3 - 1].att_name);
			//t.append("	Type:  ");
			t.append(" - ");
			t.append(typesW[attacksW[playerteamW[s].att_3 - 1].typ_1].typ_detail);
			t.append(" - CD: ");
			t.append(itoa(playerteamW[s].cool_3, attW, 10));
			//t.append("turns");
			font->drawText("Arial 12", t.c_str(), -1 + 680 * scaleX, 1 - 452 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		}
		if (playerteamW[s].att_4 > 0)
		{
			t = "";
			t.append(attacksW[playerteamW[s].att_4 - 1].att_name);
			//t.append("	Type:  ");
			t.append(" - ");
			t.append(typesW[attacksW[playerteamW[s].att_4 - 1].typ_1].typ_detail);
			t.append(" - CD: ");
			t.append(itoa(playerteamW[s].cool_4, attW, 10));
			//t.append("turns");
			font->drawText("Arial 12", t.c_str(), -1 + 680 * scaleX, 1 - 466 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		}
		// Buttons
		font->drawText("Arial 12", "Make Current", -1 + 517 * scaleX, 1 - 526 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		font->drawText("Arial 12", "Close", -1 + 777 * scaleX, 1 - 526 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);

		glUseProgram(0);
	}
#pragma endregion

#pragma region Items
	if (_itemWindow)
	{
		glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
		glBegin(GL_QUADS);
		glVertex2d(-2.5, -10);
		glVertex2d(-2.5, 15);
		glVertex2d(8.5, 15);
		glVertex2d(8.5, -10);
		glEnd();

		glColor4f(0.45f, 0.45f, 0.45f, 0.9f);
		glBegin(GL_LINES);
		glLineWidth(1.5f);
		glVertex2d(-2.5, -10);
		glVertex2d(-2.5, 15);
		glVertex2d(-2.5, 15);
		glVertex2d(8.5, 15);
		glVertex2d(8.5, 15);
		glVertex2d(8.5, -10);
		glVertex2d(8.5, -10);
		glVertex2d(-2.5, -10);
		glColor4f(0.4f, 0.4f, 0.4f, 0.6f);
		glVertex2d(-2.5, 11.5);
		glVertex2d(8.5, 11.5);
		glVertex2d(-2.5, -7);
		glVertex2d(8.5, -7);
		glEnd();

		// Close Lines
		glColor4f(0.45f, 0.45f, 0.45f, 0.9f);
		glBegin(GL_LINES);
		glVertex2d(-0.5, -7.5);
		glVertex2d(-0.5, -9);
		glVertex2d(6.5, -7.5);
		glVertex2d(6.5, -9);
		glVertex2d(-0.5, -7.5);
		glVertex2d(6.5, -7.5);
		glVertex2d(-0.5, -9);
		glVertex2d(6.5, -9);
		glEnd();


		glColor4f(0.55f, 0.55f, 0.55f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2d(-0.5, -7.5);
		glVertex2d(-0.5, -9);
		glVertex2d(6.5, -9);
		glVertex2d(6.5, -7.5);
		glEnd();

		// ITEMS
		font->drawText("Arial 36", "ITEMS", -1 + 715 * scaleX, 1 - 166 * scaleY, 0.9f, 0.4f, 0.1f, scaleX, scaleY);
		for (int iii = 0; iii < items.size(); iii++)
		{		
			string st = "";
			st.append(items[iii].name);
			st.append(" x");
			st.append(itoa(items[iii].count, attW, 10));
			font->drawText("Arial 18", st.c_str(), -1 + 625  * scaleX, 1 - (210 + (23 * iii)) * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);
		}
		// CLOSE
		font->drawText("Arial 12", "Close", -1 + 756 * scaleX, 1 - 526 * scaleY, 1.0f, 1.0f, 1.0f, scaleX, scaleY);

		glUseProgram(0);
	}
#pragma endregion

	glPopAttrib();
	glPopMatrix();
}


void OverworldMenu::select()
{
	switch (_selected)
	{
	case 0:
		_itemWindow = true;
		break;
	case 1:
		World::writeHighscore();
		break;
	case 2:
		World::writeHighscore();
		//GameState::setLastKey(GLFW_KEY_ENTER);
		GameWindow::Sound->stopSong("the-lonely-amazon");
		PlayState::changeState(MenuState::getInstance(GameState::getManager()));
		break;
	case 3:
		World::writeHighscore();
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
		break;
	case 4:
		_monsterWindow = true;
		_monsterNumber = 1;
		break;
	case 5:
		_monsterWindow = true;
		_monsterNumber = 2;
		break;
	case 6:
		_monsterWindow = true;
		_monsterNumber = 3;
		break;
	}
}


void OverworldMenu::selectItem()
{
	switch (_itemSelected)
	{
	case 0:
		_itemWindow = false;
		break;
	}
}


void OverworldMenu::selectInfo()
{
	switch (_infoSelected)
	{
	case 0:
		//do work here
		World::setCurrent(_selected - 4);
		break;
	case 1:
		_monsterWindow = false;
		_infoSelected = 0;
		break;
	}
}


void OverworldMenu::close()
{
	_selected = 0;
	_itemWindow = false;
	_monsterWindow = false;
	_itemSelected = 0;
	_infoSelected = 0;
}
