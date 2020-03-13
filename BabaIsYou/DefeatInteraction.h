#ifndef DEFEAT_INTERACTION_H
#define DEFEAT_INTERACTION_H

#include "Interaction.h"
#include "Cell.h"

class DefeatInteraction : public Interaction {

public:

	DefeatInteraction(Cell* movableTile);

	virtual void interact() final;


private:

	Cell* movable;

};


#endif 
