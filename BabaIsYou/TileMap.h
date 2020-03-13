#ifndef TILE_MAP_H 
#define TILE_MAP_H

#include <vector>
#include <list>
#include <iostream> // debug 
#include <fstream>

#include "Background.h"
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

	TileMap(int s,float leftMargin, float topMargin);

	void init(std::string const& fileName, int shaderProgramID, int backgroundProgram, float width, float height);
	void movePlayerTiles(Direction const& dir);
	void move();
	void escape(int enemyType);
	void render();

private:
	
	// typedefs to simplify expressions
	typedef std::vector<Cell> CellVector;
	typedef std::vector<CellVector> CellMatrix;

	void applyInteraction(int nameType, int operatorType, int actionType);
	int getUpperType(std::pair<int, int> pos)const;
	bool insideMap(int posX, int posY);
	bool moveTile(Direction const& dir,  int i, int j);
	void resetInteractions();
	void findInteractions(std::pair<int, int> namePos, Direction const& dir);
	
	void updateInteractions();

	std::pair<int, int> currentTile;
	Direction currentDirection;
	int size;
	float marginLeft;
	float marginTop;
	int backgroundProgramID;

	Background background;

	CellMatrix map;
};


#endif 