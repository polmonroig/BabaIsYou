#include "Cell.h"


Cell::Cell(Tile const& tile) {
	lowerTile = tile;
	upperTile = Tile();
	lowerTile.init();
	std::cout << "Initializing tile" << std::endl;
}

void Cell::setCollider() {
	upperTile = lowerTile;
	lowerTile = Tile();
}

void Cell::unsetCollider() {
	lowerTile = upperTile;
	upperTile = Tile();
}

bool Cell::getCanMove() const {
	return upperTile.getCanMove();
}

void Cell::setCanMove(bool value) {
	upperTile.setCanMove(value);
}


void Cell::move(Direction const& dir) {
	upperTile.move(dir);
}

CollisionType Cell::collide(Cell const& collisionCell) const {

	if (collisionCell.upperTile.getActive()) {
		return upperTile.collide(collisionCell.upperTile);
	}
	else return CollisionType::None;
}


void Cell::render(){
	upperTile.render();
}

void Cell::addMovedTile(Cell const& movedCell) {
	upperTile = movedCell.upperTile;
}

void Cell::destroyMovedTile() {
	upperTile.free();
	removeMovedTile();
}

void Cell::removeMovedTile() {
	upperTile = Tile();
}