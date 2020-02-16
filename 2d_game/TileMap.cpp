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
			map[i][j] = Tile(i, j, posX, posY, width, height, shaderProgramID);
			map[i][j].init();
			posX += width;
			break;
		}
		posY += height;
		posX = marginLeft;
		break;
	}

}

bool TileMap::insideMap(int posX, int posY) {
	return posX >= 0 && posX < nRows && posY >= 0 && posY < nCols;
}

void TileMap::moveTile(int iPos, int jPos, float xMove, float yMove) {
	int newTileI = map[iPos][jPos].getIIndex() + yMove;
	int newTileJ = map[iPos][jPos].getJIndex() + xMove;
	std::cout << "NewTileI: " << newTileI << std::endl;
	std::cout << "NewTileJ: " << newTileJ << std::endl;
	if (insideMap(newTileI, newTileJ)) {
		map[iPos][jPos].move(xMove, yMove);
	}
	
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