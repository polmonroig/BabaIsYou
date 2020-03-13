#include "FearInteraction.h"

FearInteraction::FearInteraction(TileMap* map, int enemy) {
	mapReference = map;
	enemyType = enemy;
}

void FearInteraction::interact()  {
	mapReference->escape(enemyType);
}