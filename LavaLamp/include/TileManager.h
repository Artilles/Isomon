#pragma once
#include "Tile.h"
#include "GLFW\glfw3.h"
#include "glm\vec2.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class TileManager
{
public:
	TileManager(void);
	~TileManager(void);

	void update(double currentTime);
	void draw(int, int);
	void Reset();
	
	float x,z, moveX, moveZ, moveDist, tileDist, rng;
	bool moving;

	void createTileSet(int rows, int columns);
	
	std::vector<Tile> _tileList; // total tiles Tile has X and Y
	Entity tree, girl;

private:
	

};

