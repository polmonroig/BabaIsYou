#ifndef SCENE_H 
#define SCENE_H 

#define CAMERA_WIDTH 1000
#define CAMERA_HEIGHT 1000

#include <glm/glm.hpp>

#include "TileMap.h"
#include "Game.h"
#include "GameMenu.h"
#include "EndM.h"
#include "Credits.h"
#include "Instructions.h"
#include "Direction.h"
#include "ServiceLocator.h"

class Game;


enum class GameState{MENU, GAMING, END, CREDITS, INSTRUCTIONS};

class Scene {

public:


	void init();
	void move(Direction const& direction);
	void selectElement();

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
	void loadEnd();
	void loadCredits();
	void loadInstructions();
	

	int currentLevel;

	float currentTime;
	
	GameState state;

	glm::mat4 projectionMatrix;

	TileMap map;

	GameMenu menu;

	EndM end;

	Credits cred;

	Instructions inst;
};

#endif 