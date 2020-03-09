#ifndef SCENE_H 
#define SCENE_H 

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

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

	void initTextures();
	void initShaders();

	int backgroundProgram;
	int quadProgram;
	float currentTime;

	
	glm::mat4 projectionMatrix;

	TileMap map;


};


#endif 