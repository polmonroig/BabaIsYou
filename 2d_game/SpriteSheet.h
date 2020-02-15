#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <string>
#include <GL/glew.h>

class SpriteSheet{

public:
	bool loadFromFile(const std::string& filename);

	void render() const;

private:

	GLuint texId;
	GLint wrapS, wrapT, minFilter, magFilter;

};


#endif 

