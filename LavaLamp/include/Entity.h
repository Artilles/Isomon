#pragma once
#include "objloader.hpp"
#include "GL\glew.h"
#define GLFW_DLL
#include "GLFW\glfw3.h"
#include "glm\vec3.hpp"
#include "glm\vec2.hpp"
#include <vector>
#include <string>
using namespace std;

class Entity
{
public:
	//Entity(string model);
	Entity::Entity();
	Entity::Entity(string model);
	~Entity(void);
	int LoadModel(string model);

	float x,z, moveX, moveZ, moveDist, tileDist, rng;
	bool moving;

	void update(double currentTime);
	void draw();

private:
	GLuint _vertexBuffer;
	GLuint _uvBuffer;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;
};

