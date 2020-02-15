#ifndef TILE_H 
#define TILE_H 


#include"AnimatedSprite.h"

class Tile {

public:

	Tile();
	Tile(float x, float y, float width, float height, int shaderProgramID);
	void move(float moveX, float moveY);
	void render();
	void free();

private:

	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	AnimatedSprite animated_sprite;

	int programID;
	float xPos, yPos, tileWidth, tileHeight;
	bool active;

	float* calculateVertices();
};


#endif 