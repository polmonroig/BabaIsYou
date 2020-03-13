#include "MoveInteraction.h"



MoveInteraction::MoveInteraction(TileMap* map) {
	mapReference = map;
}

void MoveInteraction::interact() {
	mapReference->move();
}