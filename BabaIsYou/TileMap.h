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
#include "Text.h"
#include "Cell.h"



class TileMap {

public:

	TileMap() = default;

	TileMap(float leftMargin, float topMargin);

	void init(std::string const& fileName, float width, float height);
	void movePlayerTiles(Direction const& dir);
	void move();
	void escape(int enemyType);
	bool isRestarting() const;
	void reset();
	void render();
	void free();


private:
	
	

	// typedefs to simplify expressions
	typedef std::vector<Cell> CellVector;
	typedef std::vector<CellVector> CellMatrix;

	void applyInteraction(int nameType, int operatorType, int actionType);
	int getUpperType(std::pair<int, int> pos)const;
	bool insideMap(int posX, int posY);

	bool moveTile(Direction const& dir,  int i, int j);
	void resetInteractions();
	void applyInteractionType(int i, int j, int nameType, int operatorType, int actionType);
	void findInteractions(std::pair<int, int> namePos, Direction const& dir);
	void initSound();
	void updateInteractions();
	bool renderRow(int row);
	void renderTiles();
	void loadMap();
	bool unloadMap();

	void upPath(Direction const& dir);
	void downPath(Direction const& dir);
	void leftPath(Direction const& dir);
	void rightPath(Direction const& dir);


	static const int LOAD_SPEED = 8;
	std::vector<std::string> BABA_MOVE_SOUND = { "sound/043.ogg", "sound/044.ogg", "sound/045.ogg", "sound/046.ogg" };
	std::string  WIN_SOUND = "sound/042.ogg";
	std::string  RESET_SOUND = "sound/085.ogg";
	std::string  LOAD_SOUND = "sound/026.ogg"; // 26
	std::string  THEME_SOUND = "sound/theme_soundtrack.mp3";


	std::pair<int, int> currentTile;
	Direction currentDirection;
	int mapWidth;
	int windowHeight;
	int windowWidth;
	int mapHeight;

	bool loaded;
	bool unloaded;
	static bool restarted;
	bool firstLoad;
	
	std::vector<std::pair<int, int>> cols;
	static irrklang::ISoundEngine* engine;
	Text winText;
	CellMatrix map;
};


#endif 