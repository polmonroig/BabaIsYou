#include "MoveInteraction.h"



MoveInteraction::MoveInteraction(TileMap* map) {
	std::cout << "Adding interaction" << std::endl;
	mapReference = map;
}

void MoveInteraction::interact() {
	std::cout << "Moving" << std::endl;
	mapReference->move();
}