#include "include\GameWindow.h"
#include "include\MenuState.h"
#include <stdio.h>

SoundManager* GameWindow::Sound;
GLsizei GameWindow::_width;
GLsizei GameWindow::_height;

GameWindow& GameWindow::getGameWindow()
{
	static GameWindow* gameWindow = nullptr;

	if (gameWindow == nullptr)
	{
		gameWindow = new GameWindow(true);
	}

	return *gameWindow;
}


void GameWindow::destroyGameWindow()
{
	GameWindow* gameWindow = &getGameWindow();
	delete gameWindow;

	GLFWwindow* window = glfwGetCurrentContext();
	glfwDestroyWindow(window);

	glfwTerminate();
}


GameWindow::GameWindow(bool running)
	: _running(running), _input(&Input::getInput())
{
	_width = 1366;
	_height = 768;

	initialize();
	createContext();

	glfwSetKeyCallback(_window, _input->keyCallbackFun);
	glfwSetErrorCallback(error_callback);
	//glfwSetWindowCloseCallback(_window, window_close_callback);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, _width * (16/9), _height * (16/9));

	Sound = new SoundManager;

	_stateManager = new StateManager;
	_stateManager->changeState(MenuState::getInstance(_stateManager));
}


GameWindow::~GameWindow()
{
}


void GameWindow::initialize()
{
	if(!glfwInit())
	{
		fprintf(stderr, "Error: <GameWindow, GLFW> Failed to intialize GLFW.\n");
	}

	glShadeModel(GL_SMOOTH);
}


void GameWindow::createContext()
{
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE); // Borderless Window
	_window = glfwCreateWindow(_width, _height, "Lava Lamp", glfwGetPrimaryMonitor(), NULL);

	if(!_window)
	{
		fprintf(stderr, "Error: Failed to create widnow context.\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(_window);

	if(auto err = glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Error: <GameWindow, GLEW> %s\n", glewGetErrorString(err));
	}

	glfwSwapInterval(1);
}


void GameWindow::setRunning(bool value)
{
	_running = value;
}


bool GameWindow::getRunning()
{
	return _running;
}


void GameWindow::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


void GameWindow::window_close_callback(GLFWwindow* window)
{
	// When the window is closed through the X button
	glfwSetWindowShouldClose(window, GL_TRUE);
}


#define UPDATES_PER_SECOND 60.0f
void GameWindow::gameLoop()
{
	double lastTime = glfwGetTime();
	double deltaTime = 0.0f;

	while(_running)
	{
		double currentTime = glfwGetTime();
		deltaTime += (currentTime - lastTime) * UPDATES_PER_SECOND;
		lastTime = currentTime;
		double whateveryouwant = deltaTime;
		if (deltaTime > 60.0f)
		{ 
			deltaTime = 60.0f;
		}
		if (deltaTime > 60.f)
		{
			// Throttle FPS to prevent frame boosting after low FPS
			deltaTime = 60.f;
		}

		// Run 60 frames per second
		while (deltaTime >= 1.0f)
		{
			_running = !glfwWindowShouldClose(_window);

			_input->update();
			update(currentTime);
			render();
			
			--deltaTime;
			//deltaTime -= whateveryouwant / 60.0f;
		}
	}
}


void GameWindow::render()
{
	_stateManager->draw();

	glfwSwapBuffers(_window);
}


void GameWindow::update(double time)
{
	_stateManager->update(time);

	glfwPollEvents();
}

void GameWindow::resize()
{
	glViewport(0, 0, _width * (16 / 9), _height * (16 / 9));
}