#ifndef INTERACTION_H 
#define INTERACTION_H 

class TileMap;

class Interaction{

public:

	virtual void interact() = 0;

protected:

	TileMap* mapReference;

};


#endif

