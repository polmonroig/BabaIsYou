#include "StopInteraction.h"



void StopInteraction::interact(Tile& movedTile, Tile& otherTile) {
	if (movedTile.getFlag() != State::Win && movedTile.getFlag() != State::Death)
		otherTile.setFlag(State::Stop);
	movedTile.setFlag(State::Stop);
}

int StopInteraction::ID() const {
	return STOP_ID;

}