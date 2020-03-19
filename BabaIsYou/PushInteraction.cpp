#include "PushInteraction.h"



void PushInteraction::interact(Tile& movedTile, Tile& otherTile) {
	otherTile.setFlag(State::Move);
}

int PushInteraction::ID() const {
	return PUSH_ID;
}