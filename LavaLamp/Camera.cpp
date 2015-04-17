#include "Camera.h"


float px,py,pz,ex = 0,ey = 0,ez = 0, tempX = 0, tempY = 0;

Camera::Camera()
{
	//double dist = sqrt(1 / 3.0);
	double dist = 0;
	px = dist;
	py = dist;
	pz = dist;
	tempY = 1.8;
	tempX = -1.8;
}
void Camera::Reset()
{
	//double dist = sqrt(1 / 3.0);
	double dist = 0;
	px = dist;
	py = dist;
	pz = dist;
	tempY = 1.8;
	tempX = -1.8;
}


Camera::~Camera()
{
}


void Camera::isometricView()
{	
	gluLookAt(
		px,py,pz, // position of camera
		ex,ey,ez, // where camera is pointing at
		0.0, 1.0, 0.0); // which direction is up
}


void Camera::update(double currentTime)
{
	GLFWwindow* window = glfwGetCurrentContext();
	/*
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		py+= .001f;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		py-= .001f;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		px-= .001f;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		px+= .001f;
	}	
	*/
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		tempY -= 0.005f;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		tempY += 0.005f;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		tempX += 0.005f;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		tempX -= 0.005f;
	}

	if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		pz+= .001f;
	}
	if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		pz-= .01f;
	}	
	
	if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		ez+= .001f;
	}
	if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		ez-= .001f;
	}

	if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		//double dist = sqrt(1 / 3.0);
		double dist = 0;

		px = dist;
		py = dist;
		pz = dist;
		ex = 0;
		ey = 0;
		ez = 0;
	}	
}


void Camera::render()
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	/*
	gluLookAt(
		0,0,1, // position of camera
		0,0,0, // where camerais pointing at
		0.0, 1.0, 0.0); // which direction is up
	*/
	
	glTranslatef(tempX,0,-tempY);
	
	//isometricView();
}