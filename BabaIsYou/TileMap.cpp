#include "TileMap.h"


irrklang::ISoundEngine* TileMap::engine;
irrklang::ISound* TileMap::backgroundMusic;
bool TileMap::restarted = false;

TileMap::TileMap(float winWidth, float winHeight) {
    windowHeight = winHeight;
	windowWidth = winWidth;
    loaded = false;
    firstLoad = true;
    unloaded = true;
    playThemeSound = false;
}

void TileMap::initSound() {
    engine = irrklang::createIrrKlangDevice();
    
}

void TileMap::init(std::string const& fileName) {
    InteractionsTable::init();
    
    std::ifstream file;
    file.open(fileName);
    file >> mapWidth;
    file >> mapHeight;
    map = CellMatrix(mapHeight, CellVector(mapWidth));
    cols = std::vector<std::pair<int, int>>(mapWidth, { 0,0 });
    
    float tileWidth = windowWidth / 40.0;
    float tileHeight = windowWidth / 40.0;
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
            map[i][j] = Cell(i, j);
            if(tileCode != 0){
                Type currentType(tileCode);
                auto tile = Tile(posX, posY, tileWidth, tileHeight, tileCode);
                map[i][j].add(tile);
                if (currentType.category != AnimationsManager::SPRITE) {
                    InteractionsTable::insert(currentType, new PushInteraction());
                    if (currentType.category == AnimationsManager::NAME)names.push_back(&map[i][j]);
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

bool TileMap::insideMap(std::pair<int, int> const& pos)const {
    return pos.first >= 0 && pos.first < mapHeight && pos.second >= 0 && pos.second < mapWidth;
}


bool TileMap::isRestarting() const {
    return !unloaded || !loaded;
}

void TileMap::applyInteraction(Type const& nameType, Type const& operatorType, Type const& actionType) const{
    std::cout << "Start_applyInteraction" << std::endl;
   if (operatorType.id == AnimationsManager::FEAR) {
       std::cout << "A" << std::endl;
        InteractionsTable::insert(nameType, new FearInteraction(actionType.id - AnimationsManager::N_SPRITES));
    }
    else if (actionType.id == AnimationsManager::STOP) {
       std::cout << "B" << std::endl;
        InteractionsTable::insert(nameType, new StopInteraction());
    }
    else if (actionType.id == AnimationsManager::PUSH) {
       std::cout << "C" << std::endl;
        InteractionsTable::insert(nameType, new PushInteraction());
    }
    else if (actionType.id == AnimationsManager::YOU) {
       std::cout << "D" << std::endl;
        InteractionsTable::insert(nameType, new YouInteraction());
    }
    else if (actionType.id == AnimationsManager::WIN || actionType.id == AnimationsManager::PLAY) {
       std::cout << "F" << std::endl;
        InteractionsTable::insert(nameType, new WinInteraction());
    }
    else if (actionType.id == AnimationsManager::DEFEAT) {
       std::cout << "G" << std::endl;
        InteractionsTable::insert(nameType, new DefeatInteraction());
        std::cout << "G" << std::endl;
    }
    std::cout << "End_applyInteraction" << std::endl;
    // ELSE IF = > OPERATOR = IS AND ACTIONTYPE = NAME => PUSH TYPE 
}

void TileMap::free() {

    // free cells
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            map[i][j].free();
        }
    }
    
   
}

Type const& TileMap::getBottomType(std::pair<int, int> const& pos) const {
    auto types = map[pos.first][pos.second].getTypes();
    return types[0];
}


void TileMap::findInteractions(std::pair<int, int> namePos, Direction const& dir)  {
    auto operatorPos = Direction::move(namePos, dir);
    if (insideMap(operatorPos) ){
        if (map[operatorPos.first][operatorPos.second].hasCategory(AnimationsManager::OPERATOR)) {
            auto actionPos = Direction::move(operatorPos, dir);
            if (insideMap(actionPos)) {
                if (map[actionPos.first][actionPos.second].hasCategory(AnimationsManager::PROPERTY)
                    || map[actionPos.first][actionPos.second].hasCategory(AnimationsManager::NAME)) {
                    
                    auto nameType = getBottomType(namePos);
                    auto operatorType = getBottomType(operatorPos);
                    auto actionType = getBottomType(actionPos);
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

    for (int i = 0; i < names.size(); ++i) {
        findInteractions(names[i]->getIndex(), DirectionType::DOWN);
        findInteractions(names[i]->getIndex(), DirectionType::RIGHT);
    }

}


bool TileMap::moveTile(Direction const& dir, int i, int j) {
    bool moved = false;
   /* auto dirPair = dir.getDir();
    
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
            moved = true;
        }
        else if (collision == CollisionType::Win) {
            if(engine)engine->play2D(WIN_SOUND.c_str(), false);
            unloaded = false;
        }
    }
    */
    return moved;
}



void TileMap::move() {
   /* if (moved) {
       
    }*/
} 

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
    if (engine)engine->play2D(RESET_SOUND.c_str(), false);
    restarted = true;
    unloaded = false;
    InteractionsTable::free();

}

bool TileMap::moveMarked(std::pair<int, int> const& pos, Direction const& dir) {
    auto newPos = Direction::move(pos, dir);
    if (insideMap(newPos)) {
        auto canMove = map[pos.first][pos.second].moveMarked(map[newPos.first][newPos.second]);
        if (canMove.first && canMove.second) { // can be moved
            // move(pos.first, pos.second)
            if (engine)
                engine->play2D(BABA_MOVE_SOUND[std::rand() % BABA_MOVE_SOUND.size()].c_str(), false);
        }
        else if (canMove.first) { // can move if marked
            bool moved = moveMarked(newPos, dir);
            if (moved && engine) {
                // move(pos.first, pos.second)
                engine->play2D(BABA_MOVE_SOUND[std::rand() % BABA_MOVE_SOUND.size()].c_str(), false);
            }
                
        }
        else {
            bool moved = moveMarked(newPos, dir); // move marked
        }
    } 
}

void TileMap::tryMove(int i, int j, Direction const& dir) {
    auto newPos = Direction::move({ i, j }, dir);
    if (insideMap(newPos)) {
        auto canMove = map[i][j].move(map[newPos.first][newPos.second]);
        if (canMove.first && canMove.second) { // can be moved
            // move(i, j)
            if (engine)
                engine->play2D(BABA_MOVE_SOUND[std::rand() % BABA_MOVE_SOUND.size()].c_str(), false);
        }
        else if (canMove.first) { // can move if marked
            bool moved = moveMarked(newPos, dir);
            if (moved && engine) {
                // move(i, j)
                engine->play2D(BABA_MOVE_SOUND[std::rand() % BABA_MOVE_SOUND.size()].c_str(), false);
            }
                
        }
        else {
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


void TileMap::movePlayerTiles(Direction const& dir) {
    bool playerIsAlive = false;
    if (loaded) {
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

void TileMap::setBackgroundMusic(bool value) {
    playThemeSound = value;
}


void TileMap::render() {
 
    if (!loaded) {
        if (!restarted && firstLoad && engine){
            engine->play2D(LOAD_SOUND.c_str(), false);
            firstLoad = false;
        }
        loadMap();
        if (loaded) {
            if (engine && playThemeSound) {
                backgroundMusic = engine->play2D(THEME_SOUND.c_str(), true, false, true);
            }
                
            updateInteractions();
        }
    }
    else if (!unloaded) {
        if (engine && playThemeSound) {
            playThemeSound = false;
            backgroundMusic->stop();
            backgroundMusic->drop();
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