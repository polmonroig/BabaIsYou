#ifndef DEFEAT_INTERACTION_H
#define DEFEAT_INTERACTION_H

#include "Interaction.h"

class DefeatInteraction : public Interaction {

public:

	virtual void interact(Tile& movedTile, Tile& otherTile) final;


	virtual int ID() const  final;

	static const int DEFEAT_ID = 0;

private:


};


#endif 
