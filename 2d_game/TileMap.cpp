#include "TileMap.h"

#include <iostream>

TileMap::TileMap(int s, float leftMargin, float topMargin) {

    size = s;

    marginLeft = leftMargin;
    marginTop = topMargin;
    

    map = LinkedMatrix(s, LinkedVector(s));

    

}

void TileMap::init(int shaderProgramID, int backgroundProgram, float width, float height) {
    backgroundProgramID = backgroundProgram;
    float posX = marginLeft;
    float posY = marginTop;
    float borderRight = (width - marginLeft * 2);
    float borderBottom = (height - marginTop * 2);
    background = Background(marginLeft, marginTop, borderRight, borderBottom, backgroundProgram);
    background.init();
    width = borderRight / float(size);
    height = borderBottom / float(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            map[i][j].push_back(Tile(posX, posY, width, height, shaderProgramID));
            map[i][j].begin()->init();
            posX += width;
            if (j == 1)break;
        }
        posY += height;
        posX = marginLeft;
        break;
    }
  //  map[0][1].begin()->setCanMove(false);
}

bool TileMap::insideMap(int posX, int posY) {
    return posX >= 0 && posX < size && posY >= 0 && posY < size;
}

CollisionType TileMap::checkForCollisions(Tile const& currentTile, LinkedTiles::iterator& movable, int i, int j)  {
    auto collision = CollisionType::None;
    for (auto it = map[i][j].begin(); it != map[i][j].end(); ++it) {
        CollisionType type = currentTile.collide(*it);
        if (type == CollisionType::Fixed || collision == CollisionType::Fixed)return type;
        else if (type == CollisionType::Destroy)collision = type;
        else if (collision != CollisionType::Destroy) {
            if (collision != CollisionType::Moveable) {
                collision = type;
            }
        }
        if (collision == CollisionType::Moveable)movable = it;
    }
    return collision;
}

bool TileMap::moveTile(Direction const& dir, LinkedTiles::iterator const& it , int i, int j) {
    auto dirPair = dir.getDir();
    bool moved = false;
    int xMove = dirPair.first;
    int yMove = dirPair.second;
    int newTileI = i + yMove;
    int newTileJ = j + xMove;
    std::list<Tile>::iterator movable;
    if (insideMap(newTileI, newTileJ)) {
        auto collision = checkForCollisions(*it, movable, newTileI, newTileJ);
        if (collision == CollisionType::None || collision == CollisionType::Overlap) { // empty tile 
            it->move(dir);
            map[i][j].erase(it);
            map[newTileI][newTileJ].push_back(*it);
            moved = true;
        }
        else if (collision == CollisionType::Moveable) {
            if (moveTile(dir, movable, newTileI, newTileJ)) {
                it->move(dir); // check if can be moved correctly 
                map[i][j].erase(it);
                map[newTileI][newTileJ].push_back(*it);
                moved = true;
            }
                
        }
        else if (collision == CollisionType::Destroy) {
            it->setActive(false);
            it->free();
        }
        // else if collision == fixed => don't move 
    }

    return moved;
}

// depending on the direction to take we need to move the tiles in an according order 
// this are the cases and their ocurrences 
// Case UP => Go down:
// i = 0, j = 0, ++i, ++j => Normal path 
// 
// Case DOWN => Go up:
// i = SIZE - 1, j = 0; --i; ++j 
// 
// Case LEFT => Go right 
// i = 0, j 0= 0, ++i, ++j => transpose matrix 
// 
// Case RIGHT => Go left 
// i = 0, j = SIZE, ++i, --j => tranpose matrix 

// UP == LEFT BUT TRANSPOSED 
// RIGHT = DOWN BUT TRANSPOSED 

void TileMap::movePlayerTiles(Direction const& dir) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int newI = i;
            int newJ = j;
            if (dir.isType(DirectionType::LEFT) || dir.isType(DirectionType::RIGHT)) {
                // transpose matrix 
                newI = j;
                newJ = i;
            }
            if(dir.isType(DirectionType::DOWN))
                newI = size - i - 1;
            if (dir.isType(DirectionType::RIGHT))newJ = size - i - 1;

           for (auto it = map[newI][newJ].begin(); it != map[newI][newJ].end(); ++it) {
               if (it->canMove()) {
                   if(moveTile(dir, it, newI, newJ))break; // at most 1 moveable object per tile 
                   
               }
            }
        }
    }

    
}


void TileMap::render() {
    auto shaderM = ServiceLocator::getShaderManager();
    shaderM->use(backgroundProgramID);
    background.render();
    shaderM->use();
   for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (auto it = map[i][j].begin(); it != map[i][j].end(); ++it) {
                it->render();
            }
        }
    }
    
}