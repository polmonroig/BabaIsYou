#ifndef CELL_H 
#define CELL_H

#include "Tile.h"

class Cell{

public:

	Cell() = default;

	explicit Cell(Tile const& tile);

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



private:

	Tile upperTile;
	Tile lowerTile;

};


#endif

