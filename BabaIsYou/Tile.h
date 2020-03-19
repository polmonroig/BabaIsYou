#ifndef TILE_H 
#define TILE_H 

#include <list>


#include "TypeStack.h"
#include "Direction.h"
#include "ServiceLocator.h"


enum class State {
	Stop, 
	Move,
	Death,
	Win
};

class Tile {

public:

	

	Tile();
	Tile( float x, float y, float width, float height, int tileType);
	void render();
	void free();
	void init();

	void move(Direction const& dir);

	void pushType(Type const& animtype);

	void resetType();

	Type getType() const;

	void setFlag(State value);
	
	State getFlag() const;

	void setIndex(int i, int j);

	std::pair<int, int>  getIndex() const;

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

	std::pair<int, int> index;

	State flag;
	

	
};


#endif 