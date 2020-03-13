#ifndef MOVE_INTERACTION_H
#define MOVE_INTERACTION_H 

#include "Interaction.h"
#include "TileMap.h"

class TileMap;

class MoveInteraction : public Interaction{

public:

	MoveInteraction() = default;

	MoveInteraction(TileMap* map);

	virtual void interact() final;

private:

	TileMap* mapReference;

};


#endif 

