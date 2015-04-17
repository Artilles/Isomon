#define GLFW_INCLUDE_GLU
#include "include\MenuState.h"
#include "include\GameWindow.h"
#include "include\StateManager.h"
#include "include\PlayState.h"
#include "include\FalseFightState.h"
#include "include\HighscoreState.h"
#include "include\OptionsState.h"
#include "include\GameFont.h"
#include "include\GLFW\glfw3.h"
#include <stdio.h>

MenuState::MenuState(StateManager* manager)
	: GameState(manager), _currentSelection(0),
	_currentGame(nullptr), _optionsState(nullptr), _highscoreState(nullptr)
{
	// Assign fonts and background images here
	font->createFont("Arial 18", "resource/fonts/arial.ttf", 18, 0);
	GameWindow::Sound->loadSong("the-lonely-amazon");
	GameWindow::Sound->loadSong("never-forget");
}

MenuState::~MenuState()
{
}

MenuState* MenuState::getInstance(StateManager* manager)
{
	static MenuState Instance(manager);
	return &Instance;
}

void MenuState::enterState()
{
	// Intro credits, start soundtrack here
	GameWindow::Sound->playSong("never-forget");

	readHighscore();

	_lastKey = GLFW_KEY_ENTER;
}

void MenuState::leaveState()
{
	glUseProgram(0);
}

void MenuState::selectionUp()
{
	--_currentSelection;
	if(_currentSelection < 0)
		_currentSelection = 2;
}

void MenuState::selectionDown()
{
	++_currentSelection;
	if(_currentSelection > 2)
		_currentSelection = 0;
}

void MenuState::select()
{
	switch(_currentSelection)
	{
	case 0:
		// New Game
		GameWindow::Sound->stopSong("never-forget");
		if(_currentGame == nullptr)
			_currentGame = PlayState::getInstance(stateManager);
		changeState(_currentGame);
		break;
	case 1:
		// Free Battle
		changeState(FalseFightState::getInstance(stateManager));
		break;
	case 2:
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
		break;
	}
}

void MenuState::update(double currentTime)
{
	GLFWwindow* window = glfwGetCurrentContext();

	if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && _lastKey != GLFW_KEY_ENTER)
	{
		_lastKey = GLFW_KEY_ENTER;
		GameWindow::Sound->playSound("menu_select");
		select();		
	}
	else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && _lastKey != GLFW_KEY_UP)
	{
		_lastKey = GLFW_KEY_UP;
		GameWindow::Sound->playSound("menu_click");
		selectionUp();
	}
	else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && _lastKey != GLFW_KEY_DOWN)
	{
		_lastKey = GLFW_KEY_DOWN;
		GameWindow::Sound->playSound("menu_click");
		selectionDown();
	}

	// lastKey reset statement
	if(_lastKey != -1)
	{
		if(glfwGetKey(window, _lastKey) == GLFW_RELEASE)
			_lastKey = -1;
	}
}

void MenuState::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(0);

	glPushAttrib(GL_ENABLE_BIT);	
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -200, 200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPopAttrib();

	glBegin(GL_QUADS);
	glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
	glVertex2d(-0.98, 0.2);
	glVertex2d(-0.98, 0.8);
	glVertex2d(-0.7, 0.8);
	glVertex2d(-0.7, 0.2);
	glEnd();

	glColor4f(0.45f, 0.45f, 0.45f, 0.9f);
	glBegin(GL_LINES);
	glLineWidth(1.5f);
	glVertex2d(-0.98, 0.2);
	glVertex2d(-0.98, 0.8);
	glVertex2d(-0.98, 0.8);
	glVertex2d(-0.7, 0.8);
	glVertex2d(-0.7, 0.8);
	glVertex2d(-0.7, 0.2);
	glVertex2d(-0.7, 0.2);
	glVertex2d(-0.98, 0.2);
	glColor4f(0.4f, 0.4f, 0.4f, 0.6f);
	glVertex2d(-0.98, 0.64);
	glVertex2d(-0.7, 0.64);
	glEnd();

	/*if (_currentSelection == 0)
	{
		glColor4f(0.55f, 0.55f, 0.55f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2d(9.1, 3.15);
		glVertex2d(9.1, -0.6);
		glVertex2d(21.9, -0.6);
		glVertex2d(21.9, 3.15);
		glEnd();
	}*/


	// -------------------------------------------- //
	// DRAW ALL TEXT HERE
	// -------------------------------------------- //
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Get the window size, used for the text scale
	int windowSizeX = 0;
	int windowSizeY = 0;
	glfwGetWindowSize(glfwGetCurrentContext(), &windowSizeX, &windowSizeY);
	float scaleX = (float)(2.0f / windowSizeX);
	float scaleY = (float)(2.0f / windowSizeY);

	font->drawText("Arial 18", "IsoMon", -1 + 30 * scaleX, 1 - 120 * scaleY, 0.45f, 0.85f, 0.95f, scaleX, scaleY);
	if(_currentSelection == 0)
		font->drawText("Arial 18", "> Play", -1 + 30 * scaleX, 1 - 165 * scaleY, 1, 1, 1, scaleX, scaleY);
	else
		font->drawText("Arial 18", "Play", -1 + 30 * scaleX, 1 - 165 * scaleY, 1, 1, 1, scaleX, scaleY);

	if(_currentSelection == 1)
		font->drawText("Arial 18", "> Battle", -1 + 30 * scaleX, 1 - 195 * scaleY, 1, 1, 1, scaleX, scaleY);
	else
		font->drawText("Arial 18", "Battle", -1 + 30 * scaleX, 1 - 195 * scaleY, 1, 1, 1, scaleX, scaleY);

	if(_currentSelection == 2)
		font->drawText("Arial 18", "> Quit", -1 + 30 * scaleX, 1 - 225 * scaleY, 1, 1, 1, scaleX, scaleY);
	else
		font->drawText("Arial 18", "Quit", -1 + 30 * scaleX, 1 - 225 * scaleY, 1, 1, 1, scaleX, scaleY);

	font->drawText("Arial 18", "Highscore:", -1 + 66 * scaleX, 1 - 265 * scaleY, 1, 1, 1, scaleX, scaleY);
	font->drawText("Arial 18", "Your highest level is ", -1 + 20 * scaleX, 1 - 283 * scaleY, 1, 1, 1, scaleX, scaleY);
	font->drawText("Arial 18", _highscore.c_str(), -1 + 190 * scaleX, 1 - 285 * scaleY, 1, 1, 1, scaleX, scaleY);

	glPopAttrib();
}


void MenuState::readHighscore()
{
	/*FILE* file;
	file = fopen("resource\\highscore.txt", "r");
	if (file != NULL)
	{
		fgets(temp, 100, file);
		fclose(file);
	}*/

	ifstream file("resource\\highscore.txt");
	if (file.is_open())
	{
		string t1;
		getline(file, t1);
		if (t1.empty() != true)
			_highscore = t1;
	}
	else _highscore = "0";
}
