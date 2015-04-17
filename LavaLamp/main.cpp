#include <stdlib.h>
#include "include\GameWindow.h"

void createIsometricView()
{
	// Create the isometric view
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glRotatef(45.f, 1.f, 0.f, 0.f);
	glRotatef(-45.f, 0.f, 1.f, 0.f);
}

int main(int argc, char* argv[])
{
	GameWindow* gameWindow = &GameWindow::getGameWindow();
	gameWindow->gameLoop();
	GameWindow::destroyGameWindow();
	exit(EXIT_SUCCESS);
}
