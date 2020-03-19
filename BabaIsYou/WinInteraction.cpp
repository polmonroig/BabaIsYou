#include "WinInteraction.h"


void WinInteraction::interact(Tile& movedTile, Tile& otherTile) {
	if (InteractionsTable::find(movedTile.getType(), YouInteraction::YOU_ID)) {
		movedTile.setFlag(State::Win);
	}
}

int WinInteraction::ID() const {
	return WIN_ID;

}