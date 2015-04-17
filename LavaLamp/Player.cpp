#include "include\Player.h"

void Player::Reset(void)
{
	GlobalX = 0; GlobalY = 0;
	LocalX = 0; LocalY = 0;

	SectorX = 0;
	SectorY = 0;
	x = 0, z = 0, moveDist = 0, tileDist = 0.2, moveX = 0, moveZ = 0, moving = false;
	tileNumber = 0;
	dir = 0;
	ScreenX = 2;
	ScreenY = 0;

	GlobalX = 400;
	GlobalY = 400;
	x = 2.2, z = 2.2;
}
Player::Player(void)
{
	GlobalX = 0; GlobalY = 0;
	LocalX = 0; LocalY = 0;

	SectorX = 0;
	SectorY = 0;
	x = 0, z = 0, moveDist = 0, tileDist = 0.2, moveX = 0, moveZ = 0, moving = false;
	bool res = loadOBJ("resource/models/girl2.obj", _vertices, _uvs, _normals);
	//tileNumber = GlobalX * 5 + (GlobalY) * 500;
	tileNumber = 0;
	dir = 0;
	//default start, for testing
	//LocalX = 2;
	//LocalY = 2;
	//SectorX = 1;
	//SectorY = 1;
	ScreenX = 2;
	ScreenY = 0;

	GlobalX = 400;
	GlobalY = 400;
	x = 2.2, z = 2.2;
	//load stuff
	//change x and ys here with .sav file

	//	GlobalX = LocalX + (SectorX*100);
	//	GlobalY = LocalY + (SectorY*100);
	//x = LocalX;
	//z = LocalY;
	//x/=5;
	//z/=5;

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

}

Player::~Player(void)
{
}

void Player::update(double currentTime)
{
	//if ((GlobalY - 1) * 5 < 0)
	//	GlobalY = 0;
	//else 
	tileNumber = GlobalX / 20 + (GlobalY / 10) * 50;
	//std::cout << "(" << tileNumber << ")" << std::endl;
}

void Player::draw()
{
	glEnable(GL_DEPTH_TEST);
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);


	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	glColor3f(1, 0, 0.8);
	//glTranslatef(0.0, 0, 0.0);
	//glTranslatef(0.01, -0.09, 0);
	//glTranslatef(0.090,0,.096);//puts the base tile model on the actual tile, dead in the centre

	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glRotatef(180, 0, 0, 1);
	glTranslatef(x , -z , .3);
	glRotatef(90 * dir, 0, 0, 1);
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
	glPopMatrix();

	//////////// IMPORTANT ////////////////
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDisable(GL_DEPTH_TEST);
}