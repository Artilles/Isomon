#include "include\Tile.h"


Tile::Tile(int x, int y, int r, int g, int b, int encID, char model[30])
{
	_position.x = x;
	_position.y = y;
	_colour.x = r;
	_colour.y = g;
	_colour.z = b;
	a = 0;
	_encounters = 0;
	_encounters = encID;
	strcpy(_model, model);
	//e = Entity(_model);
}


Tile::~Tile(void)
{
}
