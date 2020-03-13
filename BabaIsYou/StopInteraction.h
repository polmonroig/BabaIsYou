#ifndef STOP_INTERACTION_H
#define STOP_INTERACTION_H

#include "Interaction.h"
#include "Cell.h"

class StopInteraction : public Interaction {

public:

	StopInteraction(Cell* movableTile);

	virtual void interact() final;


private:

	Cell* movable;

};


#endif 
