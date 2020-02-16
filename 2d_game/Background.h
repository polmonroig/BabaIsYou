#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Managers.h"

class Background{

public:

	Background() = default;

	Background(float x, float y, float width, float height, int shaderProgramID);
	void init();
	void render();

private:
	
	float xPos, yPos, width, height;
	int programID;
	GLuint vao, vbo;
	GLuint posLocation;

};

#endif

