#ifndef TILE_H 
#define TILE_H 


#include "Properties.h"
#include "Managers.h"



class Tile {

public:

	Tile();
	Tile(float x, float y, float width, float height, int shaderProgramID);
	void move(float moveX, float moveY);
	void render();
	void free();
	void init();
	bool outsideBorders()const;
	void setBorders(float left, float right, float top, float bottom);
	bool collides(Tile const& other) const;

private:


	void Tile::sendVertices();


	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	
	Properties properties;


	int programID;
	float xPos, yPos, tileWidth, tileHeight;
	float borderLeft, borderBottom, borderTop, borderRight;
	

	float* calculateVertices();
};


#endif 