#pragma once
#include "GameState.h"

class HighscoreState : public GameState
{
public:
	~HighscoreState(void);



protected:
	HighscoreState(StateManager* manager);
};

