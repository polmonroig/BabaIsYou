#include "TileMap.h"


irrklang::ISoundEngine* TileMap::engine;
bool TileMap::restarted = false;

TileMap::TileMap(float winHeight, float winWidth) {
    windowHeight = winHeight;
	windowWidth = winWidth;
    loaded = false;
    firstLoad = true;
    unloaded = true;
}

void TileMap::initSound() {
    engine = irrklang::createIrrKlangDevice();
    //if (engine)
       // engine->play2D(THEME_SOUND.c_str(), true);
}

void TileMap::init(std::string const& fileName, float width, float height) {
    
    std::ifstream file;
    file.open(fileName);
    file >> mapWidth;
    file >> mapHeight;
    map = CellMatrix(mapHeight, CellVector(mapWidth));
    cols = std::vector<std::pair<int, int>>(mapWidth, { 0,0 });
    
    float tileWidth = 40;
    float tileHeight = 40;
    float marginLeft = (width - tileWidth * mapWidth) / 2.0;
    float marginTop = (height - tileHeight * mapHeight) / 2.0;
    float posX = marginLeft;
    float posY = marginTop;
    float borderRight = (width - marginLeft * 2);
    float borderBottom = (height - marginTop * 2);

   
    for (int i = 0; i < mapHeight; ++i) {
        int tileCode;
        for (int j = 0; j < mapWidth; ++j) {
            
            file >> tileCode;
            if (tileCode == 0) {
                map[i][j] = Cell();
            }
            else {
                int type = tileCode % 10;
                auto tile = Tile(posX, posY, tileWidth, tileHeight, tileCode);
                map[i][j] = Cell(tile);
              
               
                if (type != AnimationsManager::SPRITE) {
                    map[i][j].setCollider();
                    map[i][j].addInteraction(new PushInteraction(&map[i][j]));
                }
            }
            map[i][j].setBackground(posX, posY, tileWidth, tileHeight);
            posX += tileWidth;
            // read empty 

        }
        posY += tileHeight;
        posX = marginLeft;
    }
    updateInteractions();
    initSound();
    
}

bool TileMap::insideMap(int posX, int posY) {
    return posX >= 0 && posX < mapHeight && posY >= 0 && posY < mapWidth;
}

int TileMap::getUpperType(std::pair<int, int> pos)const {
    return map[pos.first][pos.second].getType().second;
}

bool TileMap::isRestarting() const {
    return !unloaded || !loaded;
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
        map[i][j].addInteraction(new StopInteraction(&map[i][j]));
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
    else if (animType == AnimationsManager::DEFEAT) {
        map[i][j].setCollider();
        map[i][j].addInteraction(new DefeatInteraction(&map[i][j]));
    }
}

void TileMap::applyInteraction(int nameType, int operatorType, int actionType) {
     int type = nameType - AnimationsManager::N_SPRITES;
     for (int i = 0; i < mapHeight; ++i) {
         for (int j = 0; j < mapWidth; ++j) {
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

    // free cells
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            map[i][j].free();
        }
    }
    
    // free sound 
    if (engine) {
       // engine->stopAllSounds();
    }
   
}

void TileMap::findInteractions(std::pair<int, int> namePos, Direction const& dir) {
   
    auto operatorPos = Direction::move(namePos, dir);
    if (insideMap(operatorPos.first, operatorPos.second) ){
        if (map[operatorPos.first][operatorPos.second].isCateogry(AnimationsManager::OPERATOR)) {
            auto actionPos = Direction::move(operatorPos, dir);
            if (insideMap(actionPos.first, actionPos.second)) {
                if (map[actionPos.first][actionPos.second].isCateogry(AnimationsManager::PROPERTY)
                    || map[actionPos.first][actionPos.second].isCateogry(AnimationsManager::NAME)) {
                    int nameType = getUpperType(namePos);
                        int operatorType = getUpperType(operatorPos);
                        int actionType = getUpperType(actionPos);
                        map[namePos.first][namePos.second].setIlum(2.0f);
                        map[operatorPos.first][operatorPos.second].setIlum(2.0f);
                        map[actionPos.first][actionPos.second].setIlum(2.0f);
                        applyInteraction(nameType / 10, operatorType / 10, actionType);
                }
            }
        }
    }
   
}

void TileMap::resetInteractions() {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (map[i][j].isCateogry(AnimationsManager::SPRITE)) {
                map[i][j].unsetCollider();
                map[i][j].resetInteractions();
            }
            if (!map[i][j].isCateogry(AnimationsManager::SPRITE))
                map[i][j].setIlum(1.0);
        }
    }
}

void TileMap::updateInteractions() {

    resetInteractions();
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
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
            if(engine)engine->play2D(WIN_SOUND.c_str(), false);
            unloaded = false;
        }
    }
    
    return moved;
}



void TileMap::move() {
    bool moved = moveTile(currentDirection, currentTile.first, currentTile.second);
    if (moved) {
        if(engine)
            engine->play2D(BABA_MOVE_SOUND[std::rand() % BABA_MOVE_SOUND.size()].c_str(), false);
    }
} 

void TileMap::escape(int enemyType) {
    std::vector<Direction> directions{ Direction(DirectionType::LEFT), Direction(DirectionType::RIGHT),
                     Direction(DirectionType::UP), Direction(DirectionType::DOWN) };
    for (auto const& dir : directions) {
        auto newPos = Direction::move(currentTile, dir);
        
        if (insideMap(newPos.first, newPos.second)) {
            int type = getUpperType(newPos);
            if (enemyType == type / 10) {
                bool moved = moveTile(-dir, currentTile.first, currentTile.second);
            }
        }
        
    }
}

void TileMap::reset() {
    if (engine)engine->play2D(RESET_SOUND.c_str(), false);
    restarted = true;
    unloaded = false;
}

void TileMap::upPath(Direction const& dir) {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            currentTile.first = i;
            currentTile.second = j;
            currentDirection = dir;
            map[i][j].interact();
        }
    }
}

void TileMap::downPath(Direction const& dir) {
    for (int i = mapHeight - 1; i >= 0; --i) {
        for (int j = 0; j < mapWidth; ++j) {
            currentTile.first = i;
            currentTile.second = j;
            map[i][j].interact();
        }
    }
}

void TileMap::leftPath(Direction const& dir) {
    for (int j = 0; j < mapWidth; ++j) {
for (int i = 0; i < mapHeight; ++i) {
    currentTile.first = i;
    currentTile.second = j;
    map[i][j].interact();
}
    }
}

void TileMap::rightPath(Direction const& dir) {
    for (int j = mapWidth - 1; j >= 0; --j) {
        for (int i = 0; i < mapHeight; ++i) {
            currentTile.first = i;
            currentTile.second = j;
            map[i][j].interact();
        }
    }
}


void TileMap::movePlayerTiles(Direction const& dir) {
    bool playerIsAlive = false;
    if (loaded) {
        currentDirection = dir;
        if (dir.isType(DirectionType::UP)) {
            upPath(dir);
        }
        else if (dir.isType(DirectionType::DOWN)) {
            downPath(dir);
        }
        else if (dir.isType(DirectionType::LEFT)) {
            leftPath(dir);
        }
        else {
            rightPath(dir);
        }
        updateInteractions();
    }
}


bool TileMap::renderRow(int row) {
    int dir = cols[row].second;
    int iterations = 0;
    if (dir < 0) {
        for (int i = cols[row].first; i < mapWidth; ++i) {
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

    if (iterations < mapWidth)return false;
    return true;
}



void TileMap::loadMap() {

    for (int i = 0; i < LOAD_SPEED; ++i) {
        int selectedRow = std::rand() % mapHeight;
        if (cols[selectedRow].second == 0) {
            int direction = std::rand() % 2;
            if (direction == 0) {
                cols[selectedRow] = { mapWidth - 1 , -1 };
            }
            else {
                cols[selectedRow] = { 0, 1 };
            }
        }
        else {
            cols[selectedRow].first += cols[selectedRow].second;
            if (cols[selectedRow].first < 0)cols[selectedRow].first = 0;
            else if (cols[selectedRow].first >= mapWidth)cols[selectedRow].first = mapWidth - 1;
        }
    }

    loaded = true;
    for (int i = 0; i < mapWidth; ++i) {
        if (cols[i].second != 0)loaded = renderRow(i) & loaded;
    }
}


void TileMap::renderTiles() {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            map[i][j].render();
        }
    }

}


bool TileMap::unloadMap() {
    for (int i = 0; i < LOAD_SPEED; ++i) {
        int selectedRow = std::rand() % mapHeight;
        if ((cols[selectedRow].first == 0 && cols[selectedRow].second == 1) 
            || (cols[selectedRow].first == mapWidth - 1 && cols[selectedRow].second == -1)){
            cols[selectedRow].second = 0;
        }
        else {
            cols[selectedRow].first -= cols[selectedRow].second;
            if (cols[selectedRow].first < 0)cols[selectedRow].first = 0;
            else if (cols[selectedRow].first >= mapWidth)cols[selectedRow].first = mapWidth - 1;
        }
    }

    unloaded = true;
    for (int i = 0; i < mapWidth; ++i) {
        if (cols[i].second != 0)unloaded = renderRow(i) & unloaded;
    }
    return unloaded;
}


void TileMap::render() {
 
    if (!loaded) {
        if (!restarted && firstLoad && engine){
            engine->play2D(LOAD_SOUND.c_str(), false);
            firstLoad = false;
        }
        loadMap();
        if(loaded)updateInteractions();
    }
    else if (!unloaded) {
        if(unloadMap())ServiceLocator::endGame();
    }
    else {
        restarted = false;
        renderTiles();
    }
    
   
}