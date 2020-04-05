#ifndef TILE_H 
#define TILE_H 

#include <list>


#include "Type.h"
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
	Tile( float x, float y, float width, float height, Type const& tileType);
	void render();
	void free();
	void init();

	void move(Direction const& dir);

	void changeType(Type const& animtype);

	Type getType() const;

	void setFlag(State value);
	
	State getFlag() const;

	void setIndex(int i, int j);

	std::pair<int, int>  getIndex() const;

	Tile copy() const;

	void setIlum(float value);
	
	void addSpawn(Type const& spawned);

	std::vector<Type> getSpawned() ;

private:

	// RENDERING ATTRIBUTES
	void sendVertices();
	void setAnimation();
	float* calculateVertices();
	float xPos, yPos, tileWidth, tileHeight;
	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	float iluminationMultiplier;
	std::shared_ptr<AnimatedSprite>  animation;

	Type tileType;

	std::pair<int, int> index;

	State flag;

	std::vector<Type> spawned;

	
};


#endif 