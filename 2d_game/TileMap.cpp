#include "TileMap.h"

#include <iostream>

TileMap::TileMap(int rows, int cols, int leftMargin, int topMargin) {

	nRows = rows;
	nCols = cols; 

	marginLeft = leftMargin;
	marginTop = topMargin;
	

	map = std::vector<std::vector<Tile>>(nRows, std::vector<Tile>(nCols));

	

}

void TileMap::init(int shaderProgramID, int backgroundProgram, float width, float height) {
	backgroundProgramID = backgroundProgram;
	float posX = marginLeft;
	float posY = marginTop;
	width = (width - marginLeft * 2);
	height = (height - marginTop * 2);
	background = Background(0, 0, width, height, backgroundProgram);
	width = width / float(nRows);
	height = height / float(nCols);

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
	
	Managers::shaderManager.use(backgroundProgramID);
	background.render();
	Managers::shaderManager.use();
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			map[i][j].render();
		}
	}
	
}