#pragma once
#define GLFW_DLL
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "StateManager.h"
#include "Input.h"
#include "SoundManager.h"

class GameWindow
{
public:
	// Returns an instance of a GameWindow
	static GameWindow& getGameWindow();
	//static GLFWwindow* getGlfwWindow() { return _window; }
	static void destroyGameWindow();
	void gameLoop();

	void setRunning(bool value);
	bool getRunning();

	// Window Size Getters/Setters
	static GLsizei getWindowHeight() { return _height; }
	static GLsizei getWindowWidth() { return _width; }
	static void setWindowHeight(GLsizei value) { _height = value; resize(); }
	static void setWindowWidth(GLsizei value) { _width = value; resize(); }

	// Callback
	void window_close_callback(GLFWwindow* window);
	static void error_callback(int error, const char* description);

	static SoundManager* Sound;

private:
	GameWindow(bool running);
	~GameWindow();

	bool _running;
	static GLsizei _width, _height;

	void initialize();
	void createContext();
	void render();
	void update(double time);

	GLFWwindow* _window;
	StateManager* _stateManager;
	Input* _input;

	static void resize();
};
