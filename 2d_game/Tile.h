#ifndef TILE_H 
#define TILE_H 


#include "Direction.h"
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
	bool getCanMove() const; // move to dynamic 
	void setCanMove(bool value); // move to dynamic 
	void setActive(bool value);
	void setCollisionType(CollisionType const& t);
	CollisionType getCollisionType() const;
private:


	void sendVertices();
	float* calculateVertices();

	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	
	CollisionType type;
	AnimatedSprite* animatedSprite;

	int programID;
	bool canMove, isActive;
	float xPos, yPos, tileWidth, tileHeight;
	

	
};


#endif 