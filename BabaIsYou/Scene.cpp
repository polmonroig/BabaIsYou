#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"




void Scene::init(){
	currentLevel = 0;
	initShaders();
	initTextures();
	loadLevel(); 
}



void Scene::loadLevel() {
	std::string fileName = LEVEL_FILE_NAME + std::to_string(currentLevel) + ".txt";
	map.free();
	map = TileMap(SIZE, MARGIN_LEFT, MARGIN_TOP);
	map.init(fileName, quadProgram, backgroundProgram, CAMERA_WIDTH - 1, CAMERA_HEIGHT - 1);
	projectionMatrix = glm::ortho(0.0f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.0f, 0.0f, 100.0f);
	currentTime = 0.0f;
}

void Scene::move(Direction const& direction) {
	map.movePlayerTiles(direction);
}

void Scene::update(int deltaTime){
	currentTime += deltaTime;
	if (ServiceLocator::isGameEnd() && currentLevel < MAX_LEVEL) {
		currentLevel++;
		loadLevel();
	}
}

void Scene::render(){
	glm::mat4 modelviewMatrix = glm::mat4(1.0f);
	auto shaderManager = ServiceLocator::getShaderManager();
	shaderManager->use(quadProgram);
	shaderManager->setUniform(quadProgram, "projectionMatrix", projectionMatrix);
	shaderManager->setUniform(quadProgram, "modelViewMatrix", modelviewMatrix);
	shaderManager->use(backgroundProgram);
	shaderManager->setUniform(backgroundProgram, "projectionMatrix", projectionMatrix);
	shaderManager->setUniform(backgroundProgram, "modelViewMatrix", modelviewMatrix);
	shaderManager->use(textProgram);
	shaderManager->setUniform(textProgram, "projectionMatrix", projectionMatrix);
	shaderManager->setUniform(textProgram, "modelViewMatrix", modelviewMatrix);
	map.render();
}


void Scene::initTextures() {
	ServiceLocator::getAnimationsManager()->init();
}


void Scene::initShaders(){
	auto shaderManager = ServiceLocator::getShaderManager();
	textProgram = shaderManager->addProgram("shaders/text.vert", "shaders/text.frag");
	backgroundProgram = shaderManager->addProgram("shaders/background.vert", "shaders/background.frag");
	quadProgram = shaderManager->addProgram("shaders/simple.vert", "shaders/simple.frag");
	

}

