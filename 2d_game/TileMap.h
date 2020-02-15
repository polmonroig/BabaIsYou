#ifndef TILE_MAP_H 
#define TILE_MAP_H

#include "Tile.h"


class TileMap {

public:

	TileMap() = default;
	TileMap(int rows, int cols, int leftMargin, int topMargin);

	void init(int shaderProgramID, float width, float height);
	void moveTile(int iPos, int jPos, float xMove, float yMove);
	void render();

private:

	int nRows;
	int nCols;
	float marginLeft;
	float marginTop;

	std::vector<std::vector<Tile>> map;
};


#endif 