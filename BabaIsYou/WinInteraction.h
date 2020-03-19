#ifndef WIN_INTERACTION_H
#define WIN_INTERACTION_H

#include "Interaction.h"
#include "InteractionsTable.h"
#include "YouInteraction.h"

class WinInteraction : public Interaction{

public:

	virtual void interact(Tile& movedTile, Tile& otherTile) final;

	virtual int ID()const  final;

	static const int WIN_ID = 5;


};


#endif 

