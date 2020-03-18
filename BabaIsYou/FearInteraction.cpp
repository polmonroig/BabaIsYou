#include "FearInteraction.h"


FearInteraction::FearInteraction(int enemy) {
	enemyType = enemy;
}


void FearInteraction::interact(Tile& movedTile, Tile& otherTile) {

}



int FearInteraction::ID() const {
	return FEAR_ID;
}