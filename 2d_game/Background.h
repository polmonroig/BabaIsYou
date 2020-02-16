#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Managers.h"

class Background{

public:

	Background() = default;

	Background(float x, float y, float width, float height, int shaderProgramID);

	void render();

private:

	GLuint vao, vbo;
	GLuint posLocation;

};

#endif

