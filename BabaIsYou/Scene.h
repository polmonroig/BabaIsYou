#ifndef SCENE_H 
#define SCENE_H 

#define CAMERA_WIDTH 1000
#define CAMERA_HEIGHT 1000

#include <glm/glm.hpp>

#include "TileMap.h"
#include "Game.h"
#include "GameMenu.h"
#include "Direction.h"
#include "ServiceLocator.h"

class Game;

class Scene {

public:


	void init();
	void move(Direction const& direction);

	void update(int deltaTime);

	void render();
	void restart();

private:

	static const int MAX_LEVEL = 6;
	const std::string LEVEL_FILE_NAME = "levels/level_";

	void initTextures();
	void initShaders();
	void loadLevel();
	void loadMenu();
	

	int currentLevel;

	float currentTime;
	
	
	glm::mat4 projectionMatrix;

	TileMap map;

	GameMenu menu;


};


#endif 