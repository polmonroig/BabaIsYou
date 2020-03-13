#include "DefeatInteraction.h"


DefeatInteraction::DefeatInteraction(Cell* movableTile) {
	movable = movableTile;
}

void DefeatInteraction::interact() {
	movable->setCollisionType(CollisionType::Destroy);
}