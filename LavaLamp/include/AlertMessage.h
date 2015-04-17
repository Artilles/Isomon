#pragma once
#define GLFW_DLL
#include "AlertMessage.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

class AlertMessage
{
public:
	AlertMessage();
	~AlertMessage();

	bool update();
	void render();

private:
	short int _selected;

	bool select();
};

