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
	float borderRight = (width - marginLeft * 2);
	float borderBottom = (height - marginTop * 2);
	background = Background(marginLeft, marginTop, borderRight, borderBottom, backgroundProgram);
	background.init();
	width = borderRight / float(nRows);
	height = borderBottom / float(nCols);

	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			map[i][j] = Tile(posX, posY, width, height, shaderProgramID);
			map[i][j].setBorders(marginLeft, borderRight, marginTop, borderBottom);
			map[i][j].init();
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