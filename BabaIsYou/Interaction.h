#ifndef INTERACTION_H 
#define INTERACTION_H 

#include "TileMap.h"

class Interaction{

public:

	virtual void interact() = 0;

protected:

	TileMap* mapReference;

};


#endif

