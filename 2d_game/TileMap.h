#ifndef TILE_MAP_H 
#define TILE_MAP_H

#include <vector>
#include <list>
#include <iostream> // debug 

#include "Tile.h"
#include "Background.h"
#include "Direction.h"

class Tile;

class TileMap {

public:

	TileMap() = default;

	TileMap(int s,float leftMargin, float topMargin);

	void init(int shaderProgramID, int backgroundProgram, float width, float height);
	void movePlayerTiles(Direction const& dir);
	void render();

private:
	
	// typedefs to simplify expressions
	typedef std::list<Tile> LinkedTiles;
	typedef std::vector<LinkedTiles> LinkedVector;
	typedef std::vector<LinkedVector> LinkedMatrix;

	bool insideMap(int posX, int posY);
	CollisionType checkForCollisions(Tile const& currentTile, LinkedTiles::iterator& movable,  int i, int j);
	bool moveTile(Direction const& dir, LinkedTiles::iterator & it, int i, int j);

	int size;
	float marginLeft;
	float marginTop;
	int backgroundProgramID;

	Background background;

	LinkedMatrix map;
};


#endif 