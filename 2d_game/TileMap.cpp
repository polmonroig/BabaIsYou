#include "TileMap.h"

#include <iostream>

TileMap::TileMap(int rows, int cols, int leftMargin, int topMargin) {

	nRows = rows;
	nCols = cols; 

	marginLeft = leftMargin;
	marginTop = topMargin;

	map = std::vector<std::vector<Tile>>(nRows, std::vector<Tile>(nCols));

}

void TileMap::init(int shaderProgramID, float width, float height) {

	float posX = marginLeft;
	float posY = marginTop;

	width = (width - marginLeft * 2) / float(nRows);
	height = (height - marginTop * 2) / float(nCols);


	

	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			map[i][j] = Tile(posX, posY, width, height, shaderProgramID);
			posX += width;
			break;
		}
		posY += height;
		posX = marginLeft;
		break;
	}

}

void TileMap::moveTile(int iPos, int jPos, float xMove, float yMove) {
	map[iPos][jPos].move(xMove, yMove);
}


void TileMap::render() {
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			float color = (i % 2 == 0) - j % 2 == 0;
			map[i][j].render();
		}
	}
}