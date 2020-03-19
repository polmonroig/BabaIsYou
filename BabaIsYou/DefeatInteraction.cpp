#include "DefeatInteraction.h"




void DefeatInteraction::interact(Tile& movedTile, Tile& otherTile) {
	if (movedTile.getFlag() != State::Win && InteractionsTable::find(movedTile.getType(), YouInteraction::YOU_ID)) {
		movedTile.setFlag(State::Death);
	}
}

int DefeatInteraction::ID() const{
	return DEFEAT_ID;
}