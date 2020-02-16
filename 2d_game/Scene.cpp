#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"




void Scene::init(){
	initShaders();
	initTextures();
	map = TileMap(10, 10, 100, 100);
	map.init(quadProgram, backgroundProgram, CAMERA_WIDTH - 1, CAMERA_HEIGHT - 1);

	projectionMatrix = glm::ortho(0.0f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.0f, 0.0f, 100.0f);
	currentTime = 0.0f;

}

void Scene::move(float x, float y) {
	map.moveTile(0, 0, x, y);
}

void Scene::update(int deltaTime){
	currentTime += deltaTime;
	Managers::animationsManager.setDeltaTime(1);
}

void Scene::render(){
	glm::mat4 modelviewMatrix = glm::mat4(1.0f);
	Managers::shaderManager.setUniform(quadProgram, "projectionMatrix", projectionMatrix);
	Managers::shaderManager.setUniform(quadProgram, "modelViewMatrix", modelviewMatrix);
	Managers::shaderManager.setUniform(backgroundProgram, "projectionMatrix", projectionMatrix);
	Managers::shaderManager.setUniform(backgroundProgram, "modelViewMatrix", modelviewMatrix);
	map.render();
}


void Scene::initTextures() {
	Managers::animationsManager.init();
}


void Scene::initShaders(){
	backgroundProgram = Managers::shaderManager.addProgram("shaders/background.vert", "shaders/background.frag");
	quadProgram = Managers::shaderManager.addProgram("shaders/simple.vert", "shaders/simple.frag");


}

