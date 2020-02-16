#ifndef TILE_MAP_H 
#define TILE_MAP_H

#include <vector>

#include "Tile.h"
#include "Background.h"

class Tile;

class TileMap {

public:

	TileMap() = default;

	TileMap(int rows, int cols, int leftMargin, int topMargin);

	void init(int shaderProgramID, int backgroundProgram, float width, float height);
	void moveTile(int iPos, int jPos, float xMove, float yMove);
	void render();

private:

	int nRows;
	int nCols;
	float marginLeft;
	float marginTop;
	int backgroundProgramID;

	Background background;

	std::vector<std::vector<Tile>> map;
};


#endif 