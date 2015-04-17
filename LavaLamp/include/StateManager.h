#pragma once
#include "GameState.h"

class StateManager
{
public:
	StateManager(void);
	~StateManager(void);

	void changeState(GameState* newState)
	{
		if(_currentState)
		{
			_currentState->leaveState();
			_previousState = _currentState;
		}
		_currentState = newState;
		_currentState->enterState();
	}

	GameState* getCurrentState() { return _currentState; }

	//void onKeyDown();
	//void onKeyUp();

	void update(double currentTime);
	void draw();

private:
	GameState* _currentState;
	GameState* _previousState;

};