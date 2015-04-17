#pragma once
#include "GameState.h"
#include "PlayState.h"
#include "HighscoreState.h"
#include "OptionsState.h"
#include "GameFont.h"

class MenuState : public GameState
{
public:
	~MenuState();

	void enterState();
	void leaveState();
	void draw();
	void update(double currentTime);

	// Returns a static instance of the MenuState to the StateManager
	static MenuState* getInstance(StateManager* manager);

protected:
	MenuState(StateManager* manager);

private:
	void selectionUp();
	void selectionDown();
	void select();
	void readHighscore();

	GameFont* font;

	int _currentSelection;

	//int _lastKey;
	
	PlayState* _currentGame;
	OptionsState* _optionsState;
	HighscoreState* _highscoreState;

	string _highscore;
	
	//Image _backgroundImage;
	//Image _titleImage;
};

