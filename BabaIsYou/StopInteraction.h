#ifndef STOP_INTERACTION_H
#define STOP_INTERACTION_H

#include "Interaction.h"


class StopInteraction : public Interaction {

public:

	virtual void interact(Tile& movedTile, Tile& otherTile) final;

	virtual int ID()const  final;

	static const int STOP_ID = 4;



};


#endif 
