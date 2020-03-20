#ifndef TILE_MAP_H 
#define TILE_MAP_H

#include <vector>
#include <list>
#include <iostream> // debug 
#include <fstream>
#include <random>

#include "Direction.h"
#include "SoundManager.h"
#include "Cell.h"



class TileMap {

public:

	TileMap() = default;

	TileMap(float winWidth, float winHeight);

	void init(std::string const& fileName);
	void movePlayerTiles(Direction const& dir);
	void escape(int enemyType);
	bool isRestarting() const;
	void reset();
	void render();
	void free();
	void setBackgroundMusic(bool value);


private:
	
	

	// typedefs to simplify expressions
	typedef std::vector<Cell> CellVector;
	typedef std::vector<Tile*> TileRefVector;
	typedef std::vector<CellVector> CellMatrix;


	// Interactions 
	void applyInteraction(Type const& nameType, Type const& operatorType, Type const& actionType);
	void interactWithSelfCell();
	void resetInteractions();
	Type getNonSpriteType(std::pair<int, int> const& pos)const;
	void findInteractions(std::pair<int, int> const& namePos, Direction const& dir);
	void updateInteractions();
	void changeType(Type const& origin, Type const& pushed);

	// MOVEMENT
	bool insideMap(std::pair<int, int> const& pos)const;
	void moveTile(std::pair<int, int> const& initialPos, Direction const& dir);
	bool moveMarked(std::pair<int, int> const& pos, Direction const& dir);
	void tryMove(int i, int j, Direction const& dir);
	void upPath(Direction const& dir);
	void downPath(Direction const& dir);
	void leftPath(Direction const& dir);
	void rightPath(Direction const& dir);

	// RENDERING
	static const int LOAD_SPEED = 8;
	bool renderRow(int row);
	void renderTiles();
	void loadMap();
	bool unloadMap();
	
	// map characteristics 
	int mapWidth;
	int windowHeight;
	int windowWidth;
	int mapHeight;

	// map states 
	bool loaded;
	bool unloaded;
	bool playThemeSound;
	static bool restarted;
	bool firstLoad;
	
	// saves rendering columns for loading and unloading 
	std::vector<std::pair<int, int>> cols;
	
	// manages the sound of the game 
	SoundManager sound;
	// contains the cells of the map 
	CellMatrix map;
	// reference to tiles 
	TileRefVector names;
	TileRefVector operators;
	TileRefVector properties;
};


#endif 