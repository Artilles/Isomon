#pragma once
#include <stdio.h>
#include "StateManager.h"
#include "GLFW\glfw3.h"

class Input
{
public:
	static Input& getInput();
	static void destroyInput();

	void update();

	static void keyCallbackFun(GLFWwindow* window, int key, int scancode, int action, int mods);


private:
	Input();
	~Input();

	StateManager* _stateManager;
	GameState* _gameState;
	GLFWwindow* _window;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

