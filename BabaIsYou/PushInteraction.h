#ifndef MOVABLE_INTERACTION_H
#define MOVABLE_INTERACTION_H

#include "Interaction.h"

class PushInteraction : public Interaction{

public:


	virtual void interact(Tile& movedTile, Tile& otherTile) final;

	virtual int ID()const  final;

	static const int PUSH_ID = 3;


};



#endif 