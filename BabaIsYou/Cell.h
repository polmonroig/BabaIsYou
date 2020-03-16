#ifndef CELL_H 
#define CELL_H

#include "Tile.h"
#include "Background.h"

class Cell{

public:

	Cell() = default;

	explicit Cell(Tile & tile);

	void setCollider();

	void unsetCollider();

	void move(Direction const& dir);

	bool getCanMove() const;

	CollisionType collide(Cell const& collisionCell) const;

	void addMovedTile(Cell const& movedCell);

	void removeMovedTile();

	void destroyMovedTile();

	void setCanMove(bool value);

	void render();

	void interact();

	void addInteraction(Interaction* inter);

	bool isCateogry(int t) const;

	void setCollisionType(CollisionType const& type);

	std::pair<int, int>  getType() const;

	void resetInteractions();

	void pushType(int type);
	
	void setBackground(float posX, float posY, float width, float height);

private:

	Tile upperTile;
	Tile lowerTile;
	Background tileBackground;

	bool interacted;

};



#endif

