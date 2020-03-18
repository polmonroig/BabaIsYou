#ifndef MOVE_INTERACTION_H
#define MOVE_INTERACTION_H 

#include "Interaction.h"


class YouInteraction : public Interaction{

public:

	virtual void interact(Tile& movedTile, Tile& otherTile) final;

	virtual int ID()const  final;

	static const int YOU_ID = 2;

private:


};


#endif 

