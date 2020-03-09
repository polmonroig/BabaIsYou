#ifndef TILE_MAP_H 
#define TILE_MAP_H

#include <vector>
#include <list>
#include <iostream> // debug 

#include "Background.h"
#include "Direction.h"
#include "Cell.h"

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
	typedef std::vector<Cell> CellVector;
	typedef std::vector<CellVector> CellMatrix;

	bool insideMap(int posX, int posY);
	bool moveTile(Direction const& dir,  int i, int j);

	int size;
	float marginLeft;
	float marginTop;
	int backgroundProgramID;

	Background background;

	CellMatrix map;
};


#endif 