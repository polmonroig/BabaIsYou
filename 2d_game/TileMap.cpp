#include "TileMap.h"

#include <iostream>

TileMap::TileMap(int rows, int cols, int leftMargin, int topMargin) {

    nRows = rows;
    nCols = cols; 

    marginLeft = leftMargin;
    marginTop = topMargin;
    

    map = LinkedMatrix(nRows, LinkedVector(nCols));

    

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
            map[i][j].push_back(Tile(posX, posY, width, height, shaderProgramID));
            map[i][j].begin()->init();
            posX += width;
            if (j == 1)break;
        }
        posY += height;
        posX = marginLeft;
        break;
    }
    map[0][1].begin()->setCanMove(false);
}

bool TileMap::insideMap(int posX, int posY) {
    return posX >= 0 && posX < nRows && posY >= 0 && posY < nCols;
}

bool TileMap::checkForCollisions(Tile const& currentTile, int i, int j) const {
    for (auto it = map[i][j].begin(); it != map[i][j].end(); ++it) {
        if (currentTile.collides(*it))return true;
    }
    return false;
}

void TileMap::movePlayerTiles(float xMove, float yMove) {

    std::vector<std::pair<std::pair<int, int>, Tile*>> references;
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {

            for (auto it = map[i][j].begin(); it != map[i][j].end(); ++it) {
                if (it->canMove()) {
                    int newTileI = i + yMove;
                    int newTileJ = j + xMove;
                    if (insideMap(newTileI, newTileJ)) {
                        if (!checkForCollisions(*it, newTileI, newTileJ)) {
                            it->move(xMove, yMove);
                            references.push_back({ {newTileI, newTileJ},  &*it });
                            map[i][j].erase(it);
                        }
                    }
                }
            }
        }
    }
    // move deleted tiles to a new position 
    for (auto& ref : references) {
        map[ref.first.first][ref.first.second].push_back(*(ref.second));
    }
    
}


void TileMap::render() {
    auto shaderM = ServiceLocator::getShaderManager();
    shaderM->use(backgroundProgramID);
    background.render();
    shaderM->use();
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            for (auto it = map[i][j].begin(); it != map[i][j].end(); ++it) {
                it->render();
            }
        }
    }
    
}