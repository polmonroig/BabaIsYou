#include "PushInteraction.h"



void PushInteraction::interact(Tile& movedTile, Tile& otherTile) {
	std::cout << "PushInteraction" << std::endl;
	otherTile.setFlag(State::Move);
}

int PushInteraction::ID() const {
	return PUSH_ID;
}