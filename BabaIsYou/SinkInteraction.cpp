#include "SinkInteraction.h"



void SinkInteraction::interact(Tile& movedTile, Tile& otherTile) {
	if (&movedTile != &otherTile) {
		movedTile.setFlag(State::Death);
		otherTile.setFlag(State::Death);
	}
}


int SinkInteraction::ID() const   {
	return SINK_ID;
}