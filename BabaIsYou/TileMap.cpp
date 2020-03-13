#include "TileMap.h"


TileMap::TileMap(int s, float leftMargin, float topMargin) {

    size = s;

    marginLeft = leftMargin;
    marginTop = topMargin;
    
    map = CellMatrix(s, CellVector(s));
   

}

void TileMap::init(std::string const& fileName, int shaderProgramID, int backgroundProgram, float width, float height) {
    backgroundProgramID = backgroundProgram;
    float posX = marginLeft;
    float posY = marginTop;
    float borderRight = (width - marginLeft * 2);
    float borderBottom = (height - marginTop * 2);
    background = Background(marginLeft, marginTop, borderRight, borderBottom, backgroundProgram);
    background.init();
    width = borderRight / float(size);
    height = borderBottom / float(size);

    std::ifstream file;
    file.open(fileName);
   
    for (int i = 0; i < size; ++i) {
        int tileCode;
        for (int j = 0; j < size; ++j) {
            
            file >> tileCode;
            if (tileCode == 0) {
                map[i][j] = Cell();
            }
            else {
                int type = tileCode % 10;
                auto tile = Tile(posX, posY, width, height, tileCode, shaderProgramID);
                map[i][j] = Cell(tile);
              
               
                if (type != AnimationsManager::SPRITE) {
                    map[i][j].setCollider();
                    map[i][j].addInteraction(new PushInteraction(&map[i][j]));
                }
            }
           
            posX += width;
            // read empty 

        }
        posY += height;
        posX = marginLeft;
    }

    updateInteractions();
}

bool TileMap::insideMap(int posX, int posY) {
    return posX >= 0 && posX < size && posY >= 0 && posY < size;
}

int TileMap::getUpperType(std::pair<int, int> pos)const {
    return map[pos.first][pos.second].getType().second;
}

void TileMap::applyInteraction(int nameType, int operatorType, int actionType) {
     int type = nameType - AnimationsManager::N_SPRITES;
     for (int i = 0; i < size; ++i) {
         for (int j = 0; j < size; ++j) {
             auto types = map[i][j].getType();
  
             types.first /= 10;
             types.second /= 10;
             
             if (types.first == type) {
                 if (operatorType == AnimationsManager::FEAR) {
                     map[i][j].setCollider();
                     map[i][j].addInteraction(new FearInteraction(this, actionType - AnimationsManager::N_SPRITES));
                 }
                 if (actionType  == AnimationsManager::YOU) {
                     map[i][j].setCollider();
                     map[i][j].addInteraction(new MoveInteraction(this));
                 }
                 else if (actionType== AnimationsManager::WIN) {
                     map[i][j].setCollider();
                     map[i][j].addInteraction(new WinInteraction(&map[i][j]));
                 }
             }
             if (types.second == type) {
                 if (operatorType == AnimationsManager::FEAR) {
                     map[i][j].setCollider();
                     map[i][j].addInteraction(new FearInteraction(this, actionType));
                 }
                 if (actionType == AnimationsManager::YOU) {
                     map[i][j].setCollider();
                     map[i][j].addInteraction(new MoveInteraction(this));
                 }
                 else if (actionType == AnimationsManager::WIN) {
                     map[i][j].setCollider();
                     map[i][j].addInteraction(new WinInteraction(&map[i][j]));
                 }
             }
         }
     }
}

void TileMap::findInteractions(std::pair<int, int> namePos, Direction const& dir) {
   
    auto operatorPos = Direction::move(namePos, dir);
    if (insideMap(operatorPos.first, operatorPos.second)) {
 
        if (map[operatorPos.first][operatorPos.second].isCateogry(AnimationsManager::OPERATOR)) {
            auto actionPos = Direction::move(operatorPos, dir);
            if (insideMap(actionPos.first, actionPos.second)) {
                if (map[actionPos.first][actionPos.second].isCateogry(AnimationsManager::PROPERTY)
                    || map[actionPos.first][actionPos.second].isCateogry(AnimationsManager::NAME)) {
                    int nameType = getUpperType(namePos);
                    int operatorType = getUpperType(operatorPos);
                    int actionType = getUpperType(actionPos);
                    applyInteraction(nameType / 10, operatorType / 10, actionType / 10);
                }

            }
        }
    }
}

void TileMap::resetInteractions() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (map[i][j].isCateogry(AnimationsManager::SPRITE)) {
                map[i][j].resetInteractions();
                map[i][j].unsetCollider();
            }

        }
    }
}

void TileMap::updateInteractions() {

    
    resetInteractions();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (map[i][j].isCateogry(AnimationsManager::NAME)) {
                findInteractions({i, j}, DirectionType::DOWN);
                findInteractions({i, j}, DirectionType::RIGHT);
            }
        }
    }

}

bool TileMap::moveTile(Direction const& dir, int i, int j) {
    auto dirPair = dir.getDir();
    bool moved = false;
    int xMove = dirPair.first;
    int yMove = dirPair.second;
    int newTileI = i + yMove;
    int newTileJ = j + xMove;

    if (insideMap(newTileI, newTileJ)) {
        auto collision = map[i][j].collide(map[newTileI][newTileJ]);
        if (collision == CollisionType::None) { // empty tile 
            map[i][j].move(dir);
            map[newTileI][newTileJ].addMovedTile(map[i][j]);
            map[i][j].removeMovedTile();
            moved = true;
        }
        else if (collision == CollisionType::Moveable) {
            if (moveTile(dir, newTileI, newTileJ)) {
                map[i][j].move(dir); // check if can be moved correctly 
                map[newTileI][newTileJ].addMovedTile(map[i][j]);
                map[i][j].removeMovedTile();
                moved = true;
            }

        }
        else if (collision == CollisionType::Destroy) {
            map[i][j].destroyMovedTile();
        }
        else if (collision == CollisionType::Win) {
            map[i][j].move(dir);
            map[newTileI][newTileJ].addMovedTile(map[i][j]);
            map[i][j].removeMovedTile();
            moved = true;
            std::cout << "YOU WON!!!!!!!!!!!" << std::endl;
        }
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


void TileMap::move() {
    bool moved = moveTile(currentDirection, currentTile.first, currentTile.second);
} 

void TileMap::escape(int enemyType) {
    std::cout << "Enemy type: " << enemyType << std::endl;
    std::vector<Direction> directions{ Direction(DirectionType::LEFT), Direction(DirectionType::RIGHT),
                     Direction(DirectionType::UP), Direction(DirectionType::DOWN) };
    for (auto const& dir : directions) {
        auto newPos = Direction::move(currentTile, dir);
        if (insideMap(newPos.first, newPos.second) ){
            int type = getUpperType(newPos);
            if (enemyType == type / 10) {
                bool moved = moveTile(-dir, currentTile.first, currentTile.second);
            }
        }
    }
}


void TileMap::movePlayerTiles(Direction const& dir) {
    bool playerIsAlive = false;
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
            currentTile.first = newI;
            currentTile.second = newJ;
            currentDirection = dir;
            map[newI][newJ].interact();
        }
    }

    updateInteractions();
}


void TileMap::render() {
    auto shaderM = ServiceLocator::getShaderManager();
    shaderM->use(backgroundProgramID);
    background.render();
    shaderM->use();
   for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            map[i][j].render();
        }
    }
    
}