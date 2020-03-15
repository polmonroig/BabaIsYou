#ifndef SCENE_H 
#define SCENE_H 

#define CAMERA_WIDTH 720
#define CAMERA_HEIGHT 720

#include <glm/glm.hpp>

#include "TileMap.h"
#include "Direction.h"
#include "ServiceLocator.h"


class Scene {

public:


	void init();
	void move(Direction const& direction);

	void update(int deltaTime);

	void render();

private:

	static const int SIZE = 20;
	static const int MARGIN_LEFT = 20;
	static const int MARGIN_TOP = 20;
	static const int MAX_LEVEL = 4;
	const std::string LEVEL_FILE_NAME = "levels/level_";

	void initTextures();
	void initShaders();
	void loadLevel();

	int currentLevel;
	float currentTime;
	
	
	glm::mat4 projectionMatrix;

	TileMap map;


};


#endif 