#include "TileMap.h"


TileMap::TileMap(int s, float leftMargin, float topMargin) {

    size = s;

    marginLeft = leftMargin;
    marginTop = topMargin;
    loaded = false;
    map = CellMatrix(s, CellVector(s));
    cols = std::vector<std::pair<int, int>>(s, {0,0});

}

void TileMap::initSound() {
    engine = irrklang::createIrrKlangDevice();
    if (engine)
        engine->play2D("sound/theme_soundtrack.mp3", true);
}

void TileMap::init(std::string const& fileName, float width, float height) {
    float posX = marginLeft;
    float posY = marginTop;
    float borderRight = (width - marginLeft * 2);
    float borderBottom = (height - marginTop * 2);
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
                auto tile = Tile(posX, posY, width, height, tileCode);
                tile.setBorders(marginLeft, borderRight, marginTop, borderBottom);
                map[i][j] = Cell(tile);
              
               
                if (type != AnimationsManager::SPRITE) {
                    map[i][j].setCollider();
                    map[i][j].addInteraction(new PushInteraction(&map[i][j]));
                }
            }
            map[i][j].setBackground(posX, posY, width, height);
            posX += width;
            // read empty 

        }
        posY += height;
        posX = marginLeft;
    }
    updateInteractions();
    initSound();
    
}

void TileMap::insideMap(int& posX, int& posY) {
    if (posX < 0)posX = size - 1;
    else if (posX >= size)posX = 0;
    if (posY < 0)posY = size - 1;
    else if (posY >= size)posY = 0;
}

int TileMap::getUpperType(std::pair<int, int> pos)const {
    return map[pos.first][pos.second].getType().second;
}


void TileMap::applyInteractionType(int i, int j, int nameType, int operatorType, int actionType) {
    int animType = actionType / 10;
    int category = actionType % 10;
    if (operatorType == AnimationsManager::FEAR) {
       map[i][j].setCollider();
       map[i][j].addInteraction(new FearInteraction(this, animType - AnimationsManager::N_SPRITES));
    }
    else if (animType == AnimationsManager::STOP) {
        map[i][j].setCollider();
        map[i][j].addInteraction(new StopInteraction(&map[i][j]));
    }
    else if (animType == AnimationsManager::YOU) {
        map[i][j].setCollider();
        map[i][j].addInteraction(new MoveInteraction(this));
    }
    else if (animType == AnimationsManager::WIN || animType == AnimationsManager::PLAY) {
        map[i][j].setCollider();
        map[i][j].addInteraction(new WinInteraction(&map[i][j]));
    }
    else if (category == AnimationsManager::NAME) {
        map[i][j].setCollider();
        map[i][j].pushType((animType - AnimationsManager::N_SPRITES) * 10);
    }
}

void TileMap::applyInteraction(int nameType, int operatorType, int actionType) {
     int type = nameType - AnimationsManager::N_SPRITES;
     for (int i = 0; i < size; ++i) {
         for (int j = 0; j < size; ++j) {
             auto types = map[i][j].getType();
             types.first /= 10;
             types.second /= 10;
             if (types.first == type) {
                 applyInteractionType(i, j, type, operatorType, actionType);
             }
             if (types.second == type) {
                 applyInteractionType(i, j, type, operatorType, actionType);
             }
         }
     }
}

void TileMap::free() {
    if (engine) {
        engine->stopAllSounds();
        engine->drop();
    }
   
}

void TileMap::findInteractions(std::pair<int, int> namePos, Direction const& dir) {
   
    auto operatorPos = Direction::move(namePos, dir);
    insideMap(operatorPos.first, operatorPos.second);
    if (map[operatorPos.first][operatorPos.second].isCateogry(AnimationsManager::OPERATOR)) {
        auto actionPos = Direction::move(operatorPos, dir);
        insideMap(actionPos.first, actionPos.second);
        if (map[actionPos.first][actionPos.second].isCateogry(AnimationsManager::PROPERTY)
            || map[actionPos.first][actionPos.second].isCateogry(AnimationsManager::NAME)) {
            int nameType = getUpperType(namePos);
            int operatorType = getUpperType(operatorPos);
            int actionType = getUpperType(actionPos);
            applyInteraction(nameType / 10, operatorType / 10, actionType);
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
  
    insideMap(newTileI, newTileJ);
    
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
        ServiceLocator::endGame();
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
    
    if (moved) {
        if(engine)
            engine->play2D("sound/002.ogg", false);
    }
} 

void TileMap::escape(int enemyType) {
    std::vector<Direction> directions{ Direction(DirectionType::LEFT), Direction(DirectionType::RIGHT),
                     Direction(DirectionType::UP), Direction(DirectionType::DOWN) };
    for (auto const& dir : directions) {
        auto newPos = Direction::move(currentTile, dir);
        insideMap(newPos.first, newPos.second);
        int type = getUpperType(newPos);
        if (enemyType == type / 10) {
            bool moved = moveTile(-dir, currentTile.first, currentTile.second);
        }
    }
}


void TileMap::movePlayerTiles(Direction const& dir) {
    bool playerIsAlive = false;
    if (loaded) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int newI = i;
                int newJ = j;
                if (dir.isType(DirectionType::LEFT) || dir.isType(DirectionType::RIGHT)) {
                    // transpose matrix 
                    newI = j;
                    newJ = i;
                }
                if (dir.isType(DirectionType::DOWN))
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
  
}


void TileMap::renderRow(int row) {
    int dir = cols[row].second;
    int iterations = 0;
    if (dir < 0) {
        for (int i = cols[row].first; i < size; ++i) {
            map[row][i].render();
            iterations++;
        }
    }
    else if (dir > 0) {
        for (int i = 0; i <= cols[row].first; ++i) {
            map[row][i].render();
            iterations++;
        }
    }
 
    if (iterations < size)loaded = false;
}

void TileMap::loadMap() {
    
    for (int i = 0; i < LOAD_SPEED; ++i) {
        int selectedRow = std::rand() % size;
        if (cols[selectedRow].second == 0) {
            int direction = std::rand() % 2;
            if (direction == 0) {
                cols[selectedRow] = { size - 1 , -1 };
            }
            else {
                cols[selectedRow] = { 0, 1 };
            }
        }
        else {
            cols[selectedRow].first += cols[selectedRow].second;
            if (cols[selectedRow].first < 0)cols[selectedRow].first = 0;
            else if (cols[selectedRow].first >= size)cols[selectedRow].first = size - 1;
        }
    }

    loaded = true;
    for (int i = 0; i < size; ++i) {
        if (cols[i].second != 0)renderRow(i);
    }
}

void TileMap::renderTiles() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            map[i][j].render();
        }
    }
}

void TileMap::render() {
 
    if (!loaded) {
        loadMap();
    }
    else {
        renderTiles();
    }
    
   
}