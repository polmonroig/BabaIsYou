#ifndef FEAR_INTERACTION_H
#define FEAR_INTERACTION_H


#include "Interaction.h"


class FearInteraction : public Interaction {

public:

	FearInteraction(int enemy);

	virtual void interact(Tile& movedTile, Tile& otherTile) final;

	virtual int ID()const  final;

	static const int FEAR_ID = 1;

private:

	int enemyType;

};


#endif 

