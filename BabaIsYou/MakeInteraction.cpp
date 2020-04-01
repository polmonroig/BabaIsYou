#include "MakeInteraction.h"


MakeInteraction::MakeInteraction(Type const& spawn) {
	spawnedType = spawn;
}


void MakeInteraction::interact(Tile& movedTile, Tile& otherTile) {
	movedTile.addSpawn(spawnedType);
}



int MakeInteraction::ID() const {
	return MAKE_ID;
}