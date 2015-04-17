#pragma once
#include "GameState.h"

class OptionsState : public GameState
{
public:
	~OptionsState(void);

protected:
	OptionsState(StateManager* manager);
};

