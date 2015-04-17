#pragma once

class StateManager;

class GameState
{
public:
	GameState(StateManager* manager);
	virtual ~GameState(void);

	enum State { MENU, FREEBATTLE, OPTIONS, HIGHSCORE, GAME };
	State currentState;

	// Functions called when transitioning states
	virtual void leaveState() { }
	virtual void enterState() { }

	virtual void update(double currentTime) { }
	virtual void draw() { }

	static void changeState(GameState* newState);

	static StateManager* getManager() { return stateManager; }
	static void setLastKey(int value) { _lastKey = value; }

protected:	
	static StateManager* stateManager;

	static int _lastKey;
};

