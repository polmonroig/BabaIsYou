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
	Tile( float x, float y, float width, float height, int tileType);
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

	void pushType(int animtype);
	void resetTypes();

	void addInteraction(Interaction* inter);

	void setBorders(int borderLeft, int borderRight, int borderTop, int borderBottom);

	void insideBorders();
	

private:

	int bLeft, bRight, bTop, bBottom;

	void sendVertices();
	void setAnimation();
	float* calculateVertices();

	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	
	CollisionType collisionType;


	AnimatedSprite* animation;
	std::list<Interaction*> interactions;


	std::pair<int, int> currentTile;


	bool canMove, isActive;
	float xPos, yPos, tileWidth, tileHeight;
	std::stack<int> types;
	

	
};


#endif 