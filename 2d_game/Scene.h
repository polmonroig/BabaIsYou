#ifndef SCENE_H 
#define SCENE_H 

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#include <glm/glm.hpp>

#include "TileMap.h"
#include "Managers.h"



class Scene {

public:


	void init();
	void move(float x, float y);

	void update(int deltaTime);

	void render();

private:

	void initTextures();
	void initShaders();

	int backgroundProgram;
	int quadProgram;
	float currentTime;

	
	glm::mat4 projectionMatrix;

	TileMap map;


};


#endif 