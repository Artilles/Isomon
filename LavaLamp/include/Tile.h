#pragma once
#include "glm\vec2.hpp"
#include "glm\vec3.hpp"
#include <string>
#include "Entity.h"

class Tile
{
public:
	Tile::Tile(int x, int y, int r, int g, int b, int encID, char model[30]);
	~Tile();

	glm::vec2 _position; // Stores X and Z values
	glm::vec3 _colour;
	char _model[30];
	int a;
	int _encounters;
	Entity e;
private:

	
};

