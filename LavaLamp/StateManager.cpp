#include "include\StateManager.h"
#include "include\GameState.h"


StateManager::StateManager(void)
	: _currentState(nullptr)
{

}

StateManager::~StateManager(void)
{
}


void StateManager::update(double currentTime)
{
	if(_currentState)
		_currentState->update(currentTime);
}

void StateManager::draw()
{
	if(_currentState)
		_currentState->draw();
}

