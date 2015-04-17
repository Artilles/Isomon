#pragma once
#include "Camera.h"
#include "TileManager.h"
#include "objloader.hpp"
#include "glm\vec3.hpp"
#include "glm\vec2.hpp"
#include <vector>

class Player
{
public:
	Player(void);
	~Player(void);

	float x,z, moveX, moveZ, moveDist, tileDist, rng;
	int GlobalX, GlobalY; //from sector 0,0 , position x,y
	int LocalX, LocalY; //from sector x,y , position x,y
	int SectorX, SectorY; //sector x,y
	int ScreenX, ScreenY;
	int tileNumber;
	bool moving;
	int dir; // facing direction
	void Reset();

	void update(double currentTime);
	void draw();

private:
	GLuint _vertexBuffer;
	GLuint _uvBuffer;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;
};

