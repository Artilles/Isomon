#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "freetype\ft2build.h"
#include FT_FREETYPE_H
#include "shader_utils.h"
#include <string>
#include <vector>
#include <stdio.h>

using std::vector;

class GameFont
{
public:
	// Create the font with specified height and width for the characters
	void createFont(const char* name, const char* typeface, int height, int weight);
	void drawText(const char* name, const char* text, float xPos, float yPos,
		GLfloat red, GLfloat green, GLfloat blue, float scaleX, float scaleY);
	void drawText(const char* name, const char* text, float xPos, float yPos,
		GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, float scaleX, float scaleY);
	//void setTextColor(GLfloat red = 1.0, GLfloat green = 1.0, GLfloat blue = 1.0);

	// Returns the size of the text, top and right fields are set to 0.
	//Rectangle getTextSize(const std::string& text);		

private:
	static GLuint program; // shader
	static GLint attribute_coord;
	static GLint uniform_tex;
	static GLint uniform_color;
	static GLuint vbo; // Vertex Buffer

	~GameFont();
	void initialize();

	struct Font
	{
		const char* name;
		FT_Face face;
		int height;
		int weight;
		
		Font(const char* pName, FT_Face pFace, int pHeight, int pWeight);
	};

	struct Point {
		GLfloat x;
		GLfloat y;
		GLfloat s;
		GLfloat t;
	};

	static bool _initialized;
	static FT_Library ft;
	static vector<Font> _fontList;
};

