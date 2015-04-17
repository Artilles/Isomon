#include "include\Input.h"
#include "include\StateManager.h"
#include <stdio.h>

Input::Input() : _window(glfwGetCurrentContext())
{
}

Input::~Input()
{
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode,
	int action, int mods)
{
	if(action != GLFW_PRESS)
		return;

	switch(key)
	{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		default:
			break;
	}
}

void Input::keyCallbackFun(GLFWwindow* window, int key, int scancode,
	int action, int mods)
{
	Input* inputSystem = &getInput();
	inputSystem->keyCallback(window, key, scancode, action, mods);
}

Input& Input::getInput()
{	
	static Input* inputSystem = nullptr;

	if(inputSystem == nullptr)
	{
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//glfwSetKeyCallback(glfwGetCurrentContext(), keyCallbackFun);
		inputSystem = new Input();
	}

	return *inputSystem;
}

void Input::destroyInput()
{
	Input* inputSystem = &getInput();
	delete inputSystem;
}

void Input::update()
{
	/*_gameState = _stateManager->getCurrentState();

	// MenuState Controls
	if(_gameState->currentState == _gameState->MENU)
	{
		
	}
	// Highscore controls
	else if(_gameState->currentState == _gameState->HIGHSCORE)
	{

	}
	// Options controls
	else if(_gameState->currentState == _gameState->OPTIONS)
	{

	}
	// GamePlay Controls
	else if(_gameState->currentState == _gameState->GAME)
	{

	}*/
}
