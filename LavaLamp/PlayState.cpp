#include "include\PlayState.h"
#include "include\GameState.h"
#include "include\GLFW\glfw3.h"
#include "include\GameWindow.h"


//World PlayState::world;

PlayState::PlayState(StateManager* manager)
	: GameState(manager)
{
}

PlayState::~PlayState(void)
{
}

PlayState* PlayState::getInstance(StateManager* manager)
{
	static PlayState Instance(manager);
	return &Instance;
}

void PlayState::enterState()
{
	//world = new World();
	GameWindow::Sound->playSong("the-lonely-amazon");
}

void PlayState::leaveState()
{
	glScalef(1.0, 1.0, 1.0);
	glRotatef(45.f, 0.f, 1.f, 0.f);
	glRotatef(-45.f, 1.f, 0.f, 0.f);
}

void PlayState::update(double currentTime)
{

	world.update(currentTime);
}

void PlayState::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glScalef(0.04, 0.04, 0.04);
	//glScalef(0.1, 0.1, 0.1);

	// Create the isometric view
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	float s = 0.9;

	glOrtho(-1 * s, 1 * s,-1 * s, 1 * s, -200, 200);
	//glOrtho(0, 1280, 720, 0, -200, 200);

	glRotatef(45.f, 1.f, 0.f, 0.f);
	glRotatef(-45.f, 0.f, 1.f, 0.f);
	//glEnable(GL_LIGHTING);

	world.draw();
}

void PlayState::changeState(GameState* newState)
{
	// delete &world;
	GameState::changeState(newState);
}