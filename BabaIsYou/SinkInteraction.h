#ifndef SINK_INTERACTION_H
#define SINK_INTERACTION_H


#include "Interaction.h"

class SinkInteraction : public Interaction{

	virtual void interact(Tile& movedTile, Tile& otherTile) final;

	virtual int ID() const  final;

	static const int SINK_ID = 6;
};



#endif 