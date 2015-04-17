#include "include\GameFont.h"
//#include "include\freetype\ft2build.h"
#include "include\glm\vec2.hpp"
#include "include\glm\vec4.hpp"
//#include FT_FREETYPE_H
#include <stdlib.h>


// Static variable declarations
GLuint GameFont::program;
GLint GameFont::attribute_coord;
GLint GameFont::uniform_tex;
GLint GameFont::uniform_color;
GLuint GameFont::vbo;
bool GameFont::_initialized = false;
FT_Library GameFont::ft;
vector<GameFont::Font> GameFont::_fontList;


GameFont::Font::Font(const char* pName, FT_Face pFace, int pHeight, int pWeight)
			: name(pName), face(pFace), height(pHeight), weight(pWeight)
{
}

GameFont::~GameFont()
{
	glDeleteShader(program);
}


void GameFont::initialize()
{
	if(FT_Init_FreeType(&ft))
		fprintf(stderr, "Failed to initialize FreeType\n");

	program = create_program("./resource/text.v.glsl", "./resource/text.f.glsl");
	if(program == 0)
	{
		fprintf(stderr, "Error: <GameFont, program> create_program failed\n");
	}

	glLinkProgram(program);

	attribute_coord = get_attrib(program, "coord");
	uniform_tex = get_uniform(program, "tex");
	uniform_color = get_uniform(program, "color");
	
	if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
	{
		fprintf(stderr, "Error: <GameFont, attribute/uniform> failed to get attrib or uniform\n");
	}

	glGenBuffers(1, &vbo);

	_initialized = true;
}


void GameFont::createFont(const char* name, const char* typeface, int height, int weight)
{
	if(!_initialized)
		initialize();
	
	FT_Face face;
	if(FT_New_Face(ft, typeface, 0, &face))
		fprintf(stderr, "Failed to open font file {%s}\n", typeface);

	FT_Set_Pixel_Sizes(face, 0, height);

	for (auto it = _fontList.begin(); it != _fontList.end(); it++)
	{
		if (it->name == name)
			return;
	}

	Font temp = Font(name, face, height, weight);
	_fontList.push_back(temp);
}


void GameFont::drawText(const char* name, const char* text, float xPos, float yPos,
	GLfloat red, GLfloat green, GLfloat blue, float scaleX, float scaleY)
{
	if (!_fontList.empty())
	{
		for (vector<Font>::iterator it = _fontList.begin(); it != _fontList.end(); ++it)
		{
			if (it->name == name)
			{
				glPushAttrib(GL_ENABLE_BIT);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				// Create color
				GLfloat color[4] = { red, green, blue, 1 };
				glUniform4fv(uniform_color, 1, color);

				glUseProgram(program);

				const char* p;
				FT_GlyphSlot g = it->face->glyph;

				GLuint tex; // the texture that will be used to hold one glyph

				glActiveTexture(GL_TEXTURE0);
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
				glUniform1i(uniform_tex, 0);

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // 1 byte alignment instead of 4 bytes for texture data

				// clamping to edges to prevent artifacts when scaling
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				// linear filtering usually looks best for text
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				// set up the bvo for the vertex data
				glEnableVertexAttribArray(attribute_coord);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
				
				// Loop through all the characters passed in
				//p = &text[0];
				for (p = text; *p; p++)
				{
					if (FT_Load_Char(it->face, *p, FT_LOAD_RENDER))
						continue;

					// Upload the bitmap as an alpha texture, contains an 8-bit grayscale image
					glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows,
						0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

					// Calculate the vertex and texture coordinates
					float x = xPos + g->bitmap_left * scaleX;
					float y = -yPos - g->bitmap_top * scaleY;
					float w = g->bitmap.width * scaleX;
					float h = g->bitmap.rows * scaleY;

					Point box[4] =
					{
						{ x, -y, 0, 0 },
						{ x + w, -y, 1, 0 },
						{ x, -y - h, 0, 1 },
						{ x + w, -y - h, 1, 1 }
					};

					// Draw the character
					glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
					glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

					// Move the cursor to the start of the next character
					xPos += (g->advance.x >> 6) * scaleX;
					yPos -= (g->advance.y >> 6) * scaleY;
				}

				glDisableVertexAttribArray(attribute_coord);
				glDeleteTextures(1, &tex);
				glPopAttrib();

			}
		}
	}
	else
		fprintf(stderr, "Error: <GameFont.cpp> Font %s not in the font list\n", name);
}


void GameFont::drawText(const char* name, const char* text, float xPos, float yPos,
	GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, float scaleX, float scaleY)
{
	if(!_fontList.empty())
	{
		for(vector<Font>::iterator it = _fontList.begin(); it != _fontList.end(); ++it)
		{
			if(it->name == name)
			{
				glPushAttrib(GL_ENABLE_BIT);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				// Create color
				GLfloat color[4] = { red, green, blue, alpha };
				glUniform4fv(uniform_color, 1, color);
				
				glUseProgram(program);				
				
				const char* p;
				FT_GlyphSlot g = it->face->glyph;
				
				GLuint tex; // the texture that will be used to hold one glyph
				
				glActiveTexture(GL_TEXTURE0);
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
				glUniform1i(uniform_tex, 0);
				
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // 1 byte alignment instead of 4 bytes for texture data
				
				// clamping to edges to prevent artifacts when scaling
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				
				// linear filtering usually looks best for text
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				
				// set up the bvo for the vertex data
				glEnableVertexAttribArray(attribute_coord);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
				
				// Loop through all the characters passed in
				for(p = text; *p; p++)
				{
					if(FT_Load_Char(it->face, *p, FT_LOAD_RENDER))
						continue;
					
					// Upload the bitmap as an alpha texture, contains an 8-bit grayscale image
					glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows,
						0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

					// Calculate the vertex and texture coordinates
					float x = xPos + g->bitmap_left * scaleX;
					float y = -yPos - g->bitmap_top * scaleY;
					float w = g->bitmap.width * scaleX;
					float h = g->bitmap.rows * scaleY;

					Point box[4] = 
					{
						{x, -y, 0, 0 },
						{x + w, -y, 1, 0},
						{x, -y - h, 0, 1},
						{x + w, -y - h, 1, 1}
					};

					// Draw the character
					glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
					glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

					// Move the cursor to the start of the next character
					xPos += (g->advance.x >> 6) * scaleX;
					yPos -= (g->advance.y >> 6) * scaleY;
				}

				glDisableVertexAttribArray(attribute_coord);
				glDeleteTextures(1, &tex);
				glPopAttrib();
				
			}
		}
	}
	else
		fprintf(stderr, "Error: <GameFont.cpp> Font %s not in the font list\n", name);	
}
