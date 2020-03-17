#include "Cell.h"


Cell::Cell(Tile & tile) {
	lowerTile = tile;
	upperTile = Tile();
	lowerTile.init();
	interacted = false;
}

void Cell::setCollider() {
	if (!upperTile.getActive()) {
		upperTile = lowerTile;
		lowerTile = Tile();
	}
	
}

void Cell::unsetCollider() {
	if (!lowerTile.getActive()) {
		lowerTile = upperTile;
		upperTile = Tile();
	}
}


void Cell::setIlum(float ilum) {
	upperTile.setIlum(ilum);
}


void Cell::setBackground(float posX, float posY, float width, float height) {
	tileBackground = Background(posX, posY, width, height);
	tileBackground.init();
}

void Cell::pushType(int type) {
	upperTile.pushType(type);
}

void Cell::resetInteractions() {
	interacted = false;
	if (lowerTile.getActive() && lowerTile.isCategory(AnimationsManager::SPRITE))
		lowerTile.resetInteractions();
	if (upperTile.getActive() && upperTile.isCategory(AnimationsManager::SPRITE)) {
		upperTile.resetInteractions();
	}
		


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
	if (!interacted) {
		upperTile.interact();
		interacted = true;
	}
	
}

void Cell::free() {
	if(upperTile.getActive())upperTile.free();
	if(lowerTile.getActive())lowerTile.free();
	tileBackground.free();
}

void Cell::render(){
	auto shaderManager = ServiceLocator::getShaderManager();
	shaderManager->use(ShaderManager::BACKGROUND_PROGRAM);
	tileBackground.render();
	shaderManager->use(ShaderManager::TILE_PROGRAM);
	lowerTile.render();
	upperTile.render();
}

void Cell::addMovedTile(Cell const& movedCell) {
	if (upperTile.getActive())lowerTile = upperTile;
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