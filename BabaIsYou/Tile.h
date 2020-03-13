#ifndef TILE_H 
#define TILE_H 

#include <stack>
#include <list>

#include "Direction.h"
#include "Interaction.h"
#include "ServiceLocator.h"

enum class CollisionType { Fixed, Moveable, Destroy, None, Win};


class Tile {

public:

	

	Tile();
	Tile( float x, float y, float width, float height, int tileType, int shaderProgramID);
	virtual void move(Direction const& dir);
	void render();
	void free();
	void init();
	CollisionType collide(Tile const& other) const;
	bool getCanMove() const; // move to dynamic 
	void setCanMove(bool value); // move to dynamic 
	void setActive(bool value);
	bool getActive() const;
	void setCollisionType(CollisionType const& t);
	void resetInteractions();
	CollisionType getCollisionType() const;

	void interact();

	bool isCategory(int t) const;

	int getType() const;

	void pushAnimation(int animtype);

	void popAnimation(int animtype);

	void addInteraction(Interaction* inter);

	

private:



	void sendVertices();
	float* calculateVertices();

	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	
	CollisionType collisionType;

	std::stack<AnimatedSprite*> animations;
	std::list<Interaction*> interactions;

	
	

	std::pair<int, int> currentTile;

	int programID;
	bool canMove, isActive;
	float xPos, yPos, tileWidth, tileHeight;
	int type;
	

	
};


#endif 