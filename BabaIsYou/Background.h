#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "ServiceLocator.h"

class Background{

public:

	Background() = default;

	Background(float x, float y, float width, float height);
	void init();
	void render();
	void free();

private:
	
	float xPos, yPos, width, height;
	GLuint vao, vbo;
	GLuint posLocation;

};

#endif

