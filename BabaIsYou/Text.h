#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SpriteSheet.h"
#include "ServiceLocator.h"
#include <ft2build.h>
#include FT_FREETYPE_H 


struct Character {
	unsigned int textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	glm::ivec2 advance;
};

class Text{

public:

	Text();

	void init(std::string const& fileName);
	void render(std::string const& str, const glm::vec2& pixel, int size, const glm::vec4& color);



private:

	static const int ATLAS_FONT_SIZE = 64;

	void initLibrary();
	void initFont(std::string const& fileName);

	int fontSize, textureSize, maxCharWidth, maxCharHeight;
	FT_Face face;

	static bool bLibInit;
	static FT_Library library;
	
};


#endif 
