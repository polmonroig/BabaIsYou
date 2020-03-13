#ifndef MOVABLE_INTERACTION_H
#define MOVABLE_INTERACTION_H

#include "Interaction.h"
#include "Cell.h"

class PushInteraction : public Interaction{

public:

	PushInteraction(Cell* movableTile);

	virtual void interact() final;


private:

	Cell* movable;

};



#endif 