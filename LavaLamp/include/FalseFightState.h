#pragma once
#include "GameState.h"
#include "Entity.h"
#include "objloader.hpp"
#include "glm\vec3.hpp"
#include "glm\vec2.hpp"
#include <vector>
#include "GameFont.h"

class FalseFightState : public GameState
{
public:
	~FalseFightState(void);

	void enterState();
	void leaveState();

	void update(double currentTime);
	void draw();


	// Returns a static instance of FalseFightState to the StateManager
	static FalseFightState* getInstance(StateManager* manager);

protected:
	FalseFightState(StateManager* manager);

private:
	Entity* entity;
	Entity* entity2;
	vector<Entity*> playerPrev;
	vector<Entity*> enemyPrev;
	

	GLuint _vertexBuffer;
	GLuint _uvBuffer;

	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;
};

