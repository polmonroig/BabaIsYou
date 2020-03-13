#include "WinInteraction.h"


WinInteraction::WinInteraction(Cell* movableTile) {
	movable = movableTile;
}

void WinInteraction::interact() {
	movable->setCollisionType(CollisionType::Win);
}