#ifndef SCENE_H 
#define SCENE_H 

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#include <glm/glm.hpp>

#include "TileMap.h"
#include "ServiceLocator.h"



class Scene {

public:


	void init();
	void move(float x, float y);

	void update(int deltaTime);

	void render();

private:

	static const int N_COLS = 10;
	static const int N_ROWS = 10;
	static const int MARGIN_LEFT = 100;
	static const int MARGIN_TOP = 100;

	void initTextures();
	void initShaders();

	int backgroundProgram;
	int quadProgram;
	float currentTime;

	
	glm::mat4 projectionMatrix;

	TileMap map;


};


#endif 