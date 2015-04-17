#pragma once
#include "GameState.h"
#include "Entity.h"
#include "GameFont.h"
#include "Camera.h"
#include "TileManager.h"
#include "Player.h"
#include "OverworldMenu.h"
#include "objloader.hpp"
#include "glm\vec3.hpp"
#include "glm\vec2.hpp"
#include <vector>
#include <string>


class World
{
public:
	World(void);
	~World(void);

	void update(double currentTime);
	void draw();
	
	Player* player;

	static bool getPaused() { return _isPaused; }
	static bool setPaused(bool value) { _isPaused = value; }
	static void setCurrent(int x);
	static void writeHighscore();

private:
	Camera* camera;
	TileManager* tileManager;
	OverworldMenu* pauseMenu;

	GLuint _vertexBuffer;
	GLuint _uvBuffer;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;

	static bool _isPaused;
};

