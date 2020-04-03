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
	void setColor(glm::vec3 const& c);

private:
	
	float xPos, yPos, width, height;
	GLuint vao, vbo;
	GLuint posLocation;

	glm::vec3 color;

};

#endif

