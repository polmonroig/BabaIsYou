#ifndef INTERACTION_H 
#define INTERACTION_H 

#include "Tile.h"



class Interaction{

public:

	
	virtual int ID() const = 0;

	virtual void interact(Tile& movedTile, Tile& otherTile) = 0;



};


#endif

