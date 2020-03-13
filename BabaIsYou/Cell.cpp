#include "Cell.h"


Cell::Cell(Tile & tile) {
	lowerTile = tile;
	upperTile = Tile();
	lowerTile.init();
}

void Cell::setCollider() {
	if (!upperTile.getActive()) {
		upperTile = lowerTile;
		lowerTile = Tile();
	}
	
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

void Cell::resetInteractions() {
	if (lowerTile.getActive() && lowerTile.isCategory(AnimationsManager::SPRITE))
		lowerTile.resetInteractions();
	if (upperTile.getActive() && upperTile.isCategory(AnimationsManager::SPRITE))
		upperTile.resetInteractions();
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

void Cell::interact() {
	upperTile.interact();
}

void Cell::render(){
	lowerTile.render();
	upperTile.render();
}

void Cell::addMovedTile(Cell const& movedCell) {
	upperTile = movedCell.upperTile;
}

bool Cell::isCateogry(int t) const {
	return upperTile.isCategory(t);
}

std::pair<int, int> Cell::getType() const {
	return { lowerTile.getType(), upperTile.getType() };
}


void Cell::destroyMovedTile() {
	upperTile.free();
	removeMovedTile();
}

void Cell::removeMovedTile() {
	upperTile = Tile();
}

void Cell::setCollisionType(CollisionType const& type) {
	upperTile.setCollisionType(type);
}


void Cell::addInteraction(Interaction* inter) {
	upperTile.addInteraction(inter);
}