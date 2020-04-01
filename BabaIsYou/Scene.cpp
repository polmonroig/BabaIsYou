#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include <GL/glut.h>



void Scene::init(){
	currentLevel = 0;
	initShaders();
	initTextures();
	loadLevel(); 
}

void Scene::restart() {
	if (!map.isRestarting()) {
		map.reset();
		--currentLevel;
	}
	
}


void Scene::loadLevel() {
	std::string fileName = LEVEL_FILE_NAME + std::to_string(currentLevel) + ".txt";
	map.free();
	
	auto width = glutGet(GLUT_WINDOW_WIDTH);
	auto height = glutGet(GLUT_WINDOW_HEIGHT);
	map = TileMap(width, height);
	map.init(fileName);
	projectionMatrix = glm::ortho(0.0f, float(width - 1), float(height - 1), 0.0f, 0.0f, 100.0f);
	currentTime = 0.0f;
}

void Scene::move(Direction const& direction) {
	map.movePlayerTiles(direction);
}

void Scene::update(int deltaTime){
	currentTime += deltaTime;
	if (ServiceLocator::isGameEnd() && currentLevel < MAX_LEVEL) {
		currentLevel++;
		map.free();
		loadLevel();
	}

	
}

void Scene::render(){
	glm::mat4 modelviewMatrix = glm::mat4(1.0f);
	auto shaderManager = ServiceLocator::getShaderManager();
	shaderManager->use(ShaderManager::TILE_PROGRAM);
	shaderManager->setUniform("projectionMatrix", projectionMatrix);
	shaderManager->setUniform("modelViewMatrix", modelviewMatrix);
	shaderManager->use(ShaderManager::BACKGROUND_PROGRAM);
	shaderManager->setUniform("projectionMatrix", projectionMatrix);
	shaderManager->setUniform("modelViewMatrix", modelviewMatrix);
	shaderManager->use(ShaderManager::PARTICLE_PROGRAM);
	shaderManager->setUniform("projectionMatrix", projectionMatrix);
	shaderManager->setUniform("modelViewMatrix", modelviewMatrix);
	map.render();
}


void Scene::initTextures() {
	ServiceLocator::getAnimationsManager()->init();
}


void Scene::initShaders(){
	ServiceLocator::getShaderManager()->init();
}

