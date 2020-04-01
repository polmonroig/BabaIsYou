#include "TileMap.h"



bool TileMap::restarted = false;

TileMap::TileMap(float winWidth, float winHeight) {
    windowHeight = winHeight;
	windowWidth = winWidth;
    loaded = false;
    firstLoad = true;
    unloaded = true;
    playThemeSound = true;
}


void TileMap::init(std::string const& fileName) {
    InteractionsTable::init();
    
    std::ifstream file;
    file.open(fileName);
    file >> mapWidth;
    file >> mapHeight;
    map = CellMatrix(mapHeight, CellVector(mapWidth));
    cols = std::vector<std::pair<int, int>>(mapWidth, { 0,0 });
    
    float tileWidth = (windowWidth / float(mapWidth)) * 0.6;
    float tileHeight = (windowWidth / float(mapWidth)) * 0.6;
    std::cout << tileHeight << std::endl;
    float marginLeft = (windowWidth - tileWidth * mapWidth) / 2.0;
    float marginTop = (windowHeight - tileHeight * mapHeight) / 2.0;
    float posX = marginLeft;
    float posY = marginTop;
    float borderRight = (windowWidth - marginLeft * 2);
    float borderBottom = (windowHeight - marginTop * 2);

   
    for (int i = 0; i < mapHeight; ++i) {
        int tileCode;
        for (int j = 0; j < mapWidth; ++j) {
            
            file >> tileCode;
            map[i][j] = Cell();
            if(tileCode != 0){
                Type currentType(tileCode);
                auto tile = new Tile(posX, posY, tileWidth, tileHeight, tileCode);
                tile->setIndex(i, j);
                map[i][j].add(tile);
                if (currentType.category != AnimationsManager::SPRITE) {
                    InteractionsTable::insert(currentType, new PushInteraction());
                    if (currentType.category == AnimationsManager::NAME)names.push_back(tile);
                    else if (currentType.category == AnimationsManager::OPERATOR)operators.push_back(tile);
                    else if (currentType.category == AnimationsManager::PROPERTY) properties.push_back(tile);
                }
            }
            map[i][j].setBackground(posX, posY, tileWidth, tileHeight);
            posX += tileWidth;
            // read empty 

        }
        posY += tileHeight;
        posX = marginLeft;
    }
 
    sound.init();
}

bool TileMap::insideMap(std::pair<int, int> const& pos)const {
    return pos.first >= 0 && pos.first < mapHeight && pos.second >= 0 && pos.second < mapWidth;
}


bool TileMap::isRestarting() const {
    return !unloaded || !loaded;
}

void TileMap::changeType(Type const& origin, Type const& pushed) {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            map[i][j].changeType(origin, pushed);
        }
    }
}

void TileMap::applyInteraction(Type const& nameType, Type const& operatorType, Type const& actionType) {
    Type realType = Type(nameType.id - AnimationsManager::N_SPRITES, AnimationsManager::SPRITE);
    Type pushedType = Type(actionType.id - AnimationsManager::N_SPRITES, AnimationsManager::SPRITE);
   if (operatorType.id == AnimationsManager::MAKE) {
        InteractionsTable::insert(realType, new MakeInteraction(pushedType));
    }
    else if (actionType.id == AnimationsManager::STOP) {
        InteractionsTable::insert(realType, new StopInteraction());
    }
    else if (actionType.id == AnimationsManager::PUSH) {
        InteractionsTable::insert(realType, new PushInteraction());
    }
    else if (actionType.id == AnimationsManager::YOU) {
        InteractionsTable::insert(realType, new YouInteraction());
    }
    else if (actionType.id == AnimationsManager::WIN || actionType.id == AnimationsManager::PLAY) {
        InteractionsTable::insert(realType, new WinInteraction());
    }
    else if (actionType.category == AnimationsManager::NAME) {
       
       changeType(realType, pushedType);
   }
    else if (actionType.id == AnimationsManager::SINK) {
       InteractionsTable::insert(realType, new SinkInteraction());
   }
    else if (actionType.id == AnimationsManager::DEFEAT) {
        InteractionsTable::insert(realType, new DefeatInteraction());
    }
}

void TileMap::free() {
    // free cells
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            map[i][j].free();
        }
    }
   
}

Type TileMap::getNonSpriteType(std::pair<int, int> const& pos) const {
    auto types = map[pos.first][pos.second].getTypes();
    for (auto const& type : types) {
        if (type.category != AnimationsManager::SPRITE) {
            return types[0];
        }
    }
    return -1;
}


void TileMap::findInteractions(std::pair<int, int> const& namePos, Direction const& dir)  {
    auto operatorPos = Direction::move(namePos, dir);
    
    if (map[namePos.first][namePos.second].hasCategory(AnimationsManager::NAME) && insideMap(operatorPos) ){
        if (map[operatorPos.first][operatorPos.second].hasCategory(AnimationsManager::OPERATOR)) {
            auto actionPos = Direction::move(operatorPos, dir);
            if (insideMap(actionPos)) {
                if (map[actionPos.first][actionPos.second].hasCategory(AnimationsManager::PROPERTY)
                    || map[actionPos.first][actionPos.second].hasCategory(AnimationsManager::NAME)) {
                    auto nameType = getNonSpriteType(namePos);
                    auto operatorType = getNonSpriteType(operatorPos);
                    auto actionType = getNonSpriteType(actionPos);
                    map[namePos.first][namePos.second].setIlum(2.0f);
                    map[operatorPos.first][operatorPos.second].setIlum(2.0f);
                    map[actionPos.first][actionPos.second].setIlum(2.0f);
                    applyInteraction(nameType, operatorType, actionType);
                }
            }
        }
    }
}

void TileMap::updateInteractions()  {
    resetInteractions();
    for (int i = 0; i < names.size(); ++i) {
        auto index = names[i]->getIndex();
        findInteractions(index, DirectionType::DOWN);
        findInteractions(index, DirectionType::RIGHT);
    }
}


// 1. 

void TileMap::escape(int enemyType) {
   /* std::vector<Direction> directions{ Direction(DirectionType::LEFT), Direction(DirectionType::RIGHT),
                     Direction(DirectionType::UP), Direction(DirectionType::DOWN) };
    for (auto const& dir : directions) {
        auto newPos = Direction::move(currentTile, dir);
        
        if (insideMap(newPos.first, newPos.second)) {
            int type = getUpperType(newPos);
            if (enemyType == type / 10) {
                bool moved = moveTile(-dir, currentTile.first, currentTile.second);
            }
        }
        
    }*/
}

void TileMap::reset() {
    sound.playReset();
    restarted = true;
    unloaded = false;
    InteractionsTable::free();
}

void TileMap::moveTile(std::pair<int, int> const& initialPos, Direction const& dir) {
    auto dirPair = dir.getDir();
    int xMove = dirPair.first;
    int yMove = dirPair.second;
    int newTileI = initialPos.first + yMove;
    int newTileJ = initialPos.second + xMove;
   /*std::cout << "IntitialPos: " << initialPos.first << ", " << initialPos.second << std::endl;
    std::cout << "Newpos: " << newTileI << ", " << newTileJ << std::endl;*/
    map[initialPos.first][initialPos.second].moveTo(map[newTileI][newTileJ], dir);
}

bool TileMap::moveMarked(std::pair<int, int> const& pos, Direction const& dir) {
    auto dirPair = dir.getDir();
    int xMove = dirPair.first;
    int yMove = dirPair.second;
    int newTileI = pos.first + yMove;
    int newTileJ = pos.second + xMove;
    std::pair<int, int> newPos = { newTileI, newTileJ };
    bool moved = false;
    if (insideMap(newPos)) {
        auto canMove = map[pos.first][pos.second].moveMarked(map[newPos.first][newPos.second]);
        if (canMove.first && canMove.second) { // can be moved
            moved = true;
            moveTile(pos, dir);
        }
        else if (canMove.first) { // can move if marked
            moved = moveMarked(newPos, dir);
            if (moved) {
                moveTile(pos, dir);
            }
                
        }
        else if(canMove.second){
            moved = moveMarked(newPos, dir); // move marked
        }
    } 
    return moved;
}

void TileMap::interactWithSelfCell() {
   for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            bool win = map[i][j].selfInteract();
            if (win) {
                sound.playWin();
                unloaded = false;
            }
        }
    }
}

void TileMap::tryMove(int i, int j, Direction const& dir) {
    auto dirPair = dir.getDir();
    int xMove = dirPair.first;
    int yMove = dirPair.second;
    int newTileI = i + yMove;
    int newTileJ = j + xMove;
    std::pair<int, int> newPos = { newTileI, newTileJ };
    if (insideMap(newPos)) {
        auto canMove = map[i][j].move(map[newPos.first][newPos.second]);
        if (canMove.first && canMove.second) { // can be moved
            moveTile({ i, j}, dir);
            sound.playMove();
        }
        else if (canMove.first) { // can move if marked
            bool moved = moveMarked(newPos, dir);
            
            if (moved) {
                moveTile({ i, j }, dir);
                sound.playMove();
            }
                
        }
        else if (canMove.second) {
            bool moved = moveMarked(newPos, dir); // move marked
        }
    }
}

void TileMap::upPath(Direction const& dir) {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            tryMove(i, j, dir);
        }
    }
}

void TileMap::downPath(Direction const& dir) {
    for (int i = mapHeight - 1; i >= 0; --i) {
        for (int j = 0; j < mapWidth; ++j) {
            tryMove(i, j, dir);
        }
    }
}

void TileMap::leftPath(Direction const& dir) {
    for (int j = 0; j < mapWidth; ++j) {
        for (int i = 0; i < mapHeight; ++i) {
            tryMove(i, j, dir);
        }
    }
}

void TileMap::rightPath(Direction const& dir) {
    for (int j = mapWidth - 1; j >= 0; --j) {
        for (int i = 0; i < mapHeight; ++i) {
            tryMove(i, j, dir);
        }
    }
}

void TileMap::resetInteractions() {
    for (int i = 0; i < properties.size(); ++i)properties[i]->setIlum(1.0f);
    for (int i = 0; i < operators.size(); ++i)operators[i]->setIlum(1.0f);
    for (int i = 0; i < names.size(); ++i)names[i]->setIlum(1.0f);
    InteractionsTable::free();
    
    
}


void TileMap::movePlayerTiles(Direction const& dir) {
    bool playerIsAlive = false;
    if (loaded && unloaded) {
        // update interactions before
        updateInteractions();
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
        // update interacitons after
        updateInteractions();
        interactWithSelfCell();
        sound.init();
       
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

void TileMap::setBackgroundMusic(bool value) {
    playThemeSound = value;
}


void TileMap::render() {
 
    if (!loaded) {
        if (!restarted && firstLoad ){
            sound.playLoad();
            firstLoad = false;
        }
        loadMap();
        if (loaded) {
            if (playThemeSound) {
                sound.playBackground();
            }
            updateInteractions();
        }
    }
    else if (!unloaded) {
        if (playThemeSound) {
            sound.stopBackground();
            playThemeSound = false;
        }
        if (unloadMap()) {
            ServiceLocator::endGame();
        }
    }
    else {
        restarted = false;
        
        renderTiles();
        
    }
    
   
}