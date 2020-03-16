#ifndef TILE_MAP_H 
#define TILE_MAP_H

#include <vector>
#include <list>
#include <iostream> // debug 
#include <fstream>
#include <random>
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")


#include "Direction.h"
#include "MoveInteraction.h"
#include "PushInteraction.h"
#include "DefeatInteraction.h"
#include "WinInteraction.h"
#include "FearInteraction.h"
#include "StopInteraction.h"
#include "Cell.h"



class TileMap {

public:

	TileMap() = default;

	TileMap(float leftMargin, float topMargin);

	void init(std::string const& fileName, float width, float height);
	void cleanMap();
	void movePlayerTiles(Direction const& dir);
	void move();
	void escape(int enemyType);
	void render();
	void free();

private:
	
	static const int LOAD_SPEED = 8;

	// typedefs to simplify expressions
	typedef std::vector<Cell> CellVector;
	typedef std::vector<CellVector> CellMatrix;

	void applyInteraction(int nameType, int operatorType, int actionType);
	int getUpperType(std::pair<int, int> pos)const;
	bool insideMap(int posX, int posY);

	bool moveTile(Direction const& dir,  int i, int j);
	void unloadMap();
	void resetInteractions();
	void applyInteractionType(int i, int j, int nameType, int operatorType, int actionType);
	void findInteractions(std::pair<int, int> namePos, Direction const& dir);
	void initSound();
	void updateInteractions();
	void renderRow(int row);
	void renderTiles();
	void loadMap();

	void upPath(Direction const& dir);
	void downPath(Direction const& dir);
	void leftPath(Direction const& dir);
	void rightPath(Direction const& dir);
	std::pair<int, int> currentTile;
	Direction currentDirection;
	int mapWidth;
	int windowHeight;
	int windowWidth;
	int mapHeight;

	bool loaded;
	bool unloaded;
	std::vector<std::pair<int, int>> cols;
	irrklang::ISoundEngine* engine;
	CellMatrix map;
};


#endif 