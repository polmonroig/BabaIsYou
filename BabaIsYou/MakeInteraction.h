#ifndef MAKE_INTERACTION_H
#define MAKE_INTERACTION_H


#include "Interaction.h"


class MakeInteraction : public Interaction {

public:

	MakeInteraction(Type const& spawn);

	virtual void interact(Tile& movedTile, Tile& otherTile) final;

	virtual int ID()const  final;

	static const int MAKE_ID = 1;

private:
	Type spawnedType;

};


#endif 

