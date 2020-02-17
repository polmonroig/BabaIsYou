#ifndef TILE_MAP_H 
#define TILE_MAP_H

#include <vector>
#include <list>

#include "Tile.h"
#include "Background.h"

class Tile;

class TileMap {

public:

	TileMap() = default;

	TileMap(int rows, int cols, int leftMargin, int topMargin);

	void init(int shaderProgramID, int backgroundProgram, float width, float height);
	void movePlayerTiles(float xMove, float yMove);
	void render();

private:
	
	typedef std::vector<std::list<Tile>> LinkedVector;
	typedef std::vector<LinkedVector> LinkedMatrix;

	bool insideMap(int posX, int posY);
	bool checkForCollisions(Tile const& currentTile, int i, int j) const;

	int nRows;
	int nCols;
	float marginLeft;
	float marginTop;
	int backgroundProgramID;

	Background background;

	LinkedMatrix map;
};


#endif 