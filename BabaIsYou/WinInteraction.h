#ifndef WIN_INTERACTION_H
#define WIN_INTERACTION_H

#include "Interaction.h"
#include "Cell.h"

class WinInteraction : public Interaction{

public:

	WinInteraction(Cell* movableTile);

	virtual void interact() final;


private:

	Cell* movable;

};


#endif 

