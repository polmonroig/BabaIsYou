#include "PushInteraction.h"



PushInteraction::PushInteraction(Cell* movableTile) {
	movable = movableTile;
}

void PushInteraction::interact()  {
	movable->setCollisionType(CollisionType::Moveable);
}