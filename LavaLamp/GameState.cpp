#include "include\GameState.h"
#include "include\StateManager.h"
#include <string>

StateManager* GameState::stateManager;
int GameState::_lastKey;

GameState::GameState(StateManager* manager)
{
	stateManager = manager;
}

GameState::~GameState(void)
{
}

void GameState::changeState(GameState* newState)
{
	stateManager->changeState(newState);
}
