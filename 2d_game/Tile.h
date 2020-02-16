#ifndef TILE_H 
#define TILE_H 


#include "Properties.h"
#include "Managers.h"



class Tile {

public:

	

	Tile();
	Tile( float x, float y, float width, float height, int shaderProgramID);
	void move(float moveX, float moveY);
	void render();
	void free();
	void init();
	bool collides(Tile const& other) const;
	bool canMove() const;
	void setCanMove(bool value);

private:


	void Tile::sendVertices();


	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	
	Properties properties;


	int programID;
	float xPos, yPos, tileWidth, tileHeight;
	

	float* calculateVertices();
};


#endif 