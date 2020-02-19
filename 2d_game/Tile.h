#ifndef TILE_H 
#define TILE_H 


#include "Direction.h"
#include "Properties.h"
#include "ServiceLocator.h"

enum class CollisionType {Overlap, Fixed, Moveable, Destroy, None};


class Tile {

public:

	

	Tile();
	Tile( float x, float y, float width, float height, int shaderProgramID);
	virtual void move(Direction const& dir);
	void render();
	void free();
	void init();
	CollisionType collide(Tile const& other) const;
	bool canMove() const; // move to dynamic 
	void setCanMove(bool value); // move to dynamic 
	void setActive(bool value);

private:


	void sendVertices();


	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	
	Properties properties;


	int programID;
	float xPos, yPos, tileWidth, tileHeight;
	

	float* calculateVertices();
};


#endif 