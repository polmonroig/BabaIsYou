#include "StopInteraction.h"



StopInteraction::StopInteraction(Cell* movableTile) {
	movable = movableTile;
}

void StopInteraction::interact() {
	movable->setCollisionType(CollisionType::Fixed);
}