#pragma once
#include "GameState.h"
#include "World.h"
class PlayState : public GameState
{
public:
	~PlayState(void);

	void enterState();
	void leaveState();
	void update(double currentTime);
	void draw();

	// Returns a static instance of PlayState to the StateManager
	static PlayState* getInstance(StateManager* manager);

	static void changeState(GameState* newState);

protected:
	PlayState(StateManager* manager);

private:
	World world;
};

