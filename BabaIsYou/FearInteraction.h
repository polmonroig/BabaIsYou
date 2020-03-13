#ifndef FEAR_INTERACTION_H
#define FEAR_INTERACTION_H


#include "Interaction.h"
#include "TileMap.h"


class TileMap;

class FearInteraction : public Interaction {

public:

	FearInteraction(TileMap* map, int enemy);

	virtual void interact() final;

private:

	TileMap* mapReference;
	int enemyType;

};


#endif 

