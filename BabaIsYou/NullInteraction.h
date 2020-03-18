#ifndef NULL_INTERACTION_H
#define NULL_INTERACTION_H

#include "Interaction.h"

class NullInteraction : public Interaction{

public:
	

	virtual void interact(Tile& movedTile, Tile& otherTile) final;

	virtual int ID()const  final;

	static const int NULL_ID = -1;

};

#endif

