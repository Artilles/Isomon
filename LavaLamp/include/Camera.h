#pragma once
#define GLFW_DLL
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Vector.h"

class Camera
{
public:
	Camera();
	~Camera();

	void update(double currentTime);
	void render();
	void Reset();

private:
	void isometricView();
	
};

