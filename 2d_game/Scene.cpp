#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"




void Scene::init(){
	initShaders();
	initTextures();
	map = TileMap(15, 15, 50, 50);
	map.init(quadProgram, CAMERA_WIDTH - 1, CAMERA_HEIGHT - 1);

	projectionMatrix = glm::ortho(0.0f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.0f);
	currentTime = 0.0f;

}

void Scene::move(float x, float y) {
	map.moveTile(0, 0, x, y);
}

void Scene::update(int deltaTime){
	currentTime += deltaTime;
}

void Scene::render(){
	Managers::shaderManager.use();
	glm::mat4 modelviewMatrix = glm::mat4(1.0f);
	Managers::shaderManager.setUniform(quadProgram, "projectionMatrix", projectionMatrix);
	Managers::shaderManager.setUniform(quadProgram, "modelViewMatrix", modelviewMatrix);
	map.render();
}


void Scene::initTextures() {
	Managers::animationsManager.init();
}


void Scene::initShaders(){

	quadProgram = Managers::shaderManager.addProgram("shaders/simple.vert", "shaders/simple.frag");

}

