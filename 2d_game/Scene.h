#ifndef SCENE_H 
#define SCENE_H 

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#include <glm/glm.hpp>

#include "ShaderManager.h"
#include "SpriteSheet.h"
#include "TileMap.h"

class Scene {

public:

	void init();
	void move(float x, float y);

	void update(int deltaTime);

	void render();

private:

	void initTextures();
	void initShaders();


	int quadProgram;
	float currentTime;


	ShaderManager shaderManager;
	SpriteSheet sprites;
	
	glm::mat4 projectionMatrix;

	TileMap map;


};


#endif 