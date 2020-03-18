#ifndef TILE_H 
#define TILE_H 

#include <list>


#include "TypeStack.h"
#include "Direction.h"
#include "ServiceLocator.h"


class Tile {

public:

	

	Tile()=default;
	Tile( float x, float y, float width, float height, int tileType);
	void render();
	void free();
	void init();

	void move(Direction const& dir);

	void pushType(int animtype);

	Type const& getType() const;


	void setIlum(float value);
	
	

private:

	// RENDERING ATTRIBUTES
	void sendVertices();
	void setAnimation();
	float* calculateVertices();
	float xPos, yPos, tileWidth, tileHeight;
	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	float iluminationMultiplier;
	AnimatedSprite* animation;

	TypeStack types;
	

	
};


#endif 