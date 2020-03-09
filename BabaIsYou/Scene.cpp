#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"




void Scene::init(){

	initShaders();
	initTextures();
	map = TileMap(SIZE, MARGIN_LEFT, MARGIN_TOP);
	map.init(quadProgram, backgroundProgram, CAMERA_WIDTH - 1, CAMERA_HEIGHT - 1);

	projectionMatrix = glm::ortho(0.0f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.0f, 0.0f, 100.0f);
	currentTime = 0.0f;

}

void Scene::move(Direction const& direction) {
	map.movePlayerTiles(direction);
}

void Scene::update(int deltaTime){
	currentTime += deltaTime;
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
	map.render();
}


void Scene::initTextures() {
	ServiceLocator::getAnimationsManager()->init();
}


void Scene::initShaders(){
	auto shaderManager = ServiceLocator::getShaderManager();
	backgroundProgram = shaderManager->addProgram("shaders/background.vert", "shaders/background.frag");
	quadProgram = shaderManager->addProgram("shaders/simple.vert", "shaders/simple.frag");


}

