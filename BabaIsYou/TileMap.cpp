#include "TileMap.h"


TileMap::TileMap(int s, float leftMargin, float topMargin) {

    size = s;

    marginLeft = leftMargin;
    marginTop = topMargin;
    
    map = CellMatrix(s, CellVector(s));

    

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

    std::string fileName = "levels/level_0.txt";
    std::ifstream file;
    file.open(fileName);

    for (int i = 0; i < size; ++i) {
        int tileCode;
        for (int j = 0; j < size; ++j) {
            
            file >> tileCode;
            std::cout << tileCode;
            if (tileCode == 0) {
                map[i][j] = Cell();
            }
            else {
                int tileType = ((tileCode / 10) % 100) - 1; 
                map[i][j] = Cell(Tile(posX, posY, width, height, tileType, shaderProgramID));
            }
           
            posX += width;
            // read empty 

        }
        std::cout << std::endl;
        posY += height;
        posX = marginLeft;
    }
    map[0][0].setCollider();
    map[0][0].setCanMove(true);
}

bool TileMap::insideMap(int posX, int posY) {
    return posX >= 0 && posX < size && posY >= 0 && posY < size;
}


bool TileMap::moveTile(Direction const& dir, int i, int j) {
    auto dirPair = dir.getDir();
    bool moved = false;
    int xMove = dirPair.first;
    int yMove = dirPair.second;
    int newTileI = i + yMove;
    int newTileJ = j + xMove;
    std::list<Tile>::iterator movable;
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
            if (map[newI][newJ].getCanMove()) {
                bool moved = moveTile(dir, newI, newJ);
                playerIsAlive = true;
            }
        }
    }
    if (!playerIsAlive)std::cout << "############GAME OVER##############" << std::endl;
    
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