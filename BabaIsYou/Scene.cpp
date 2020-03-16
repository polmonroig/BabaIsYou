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



void Scene::loadLevel() {
	std::string fileName = LEVEL_FILE_NAME + std::to_string(currentLevel) + ".txt";
	map.free();
	map = TileMap(SIZE, MARGIN_LEFT, MARGIN_TOP);
	map.init(fileName, CAMERA_WIDTH - 1, CAMERA_HEIGHT - 1);
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

void Scene::checkInput() {
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		move(Direction(DirectionType::RIGHT));
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		move(Direction(DirectionType::LEFT));
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		move(Direction(DirectionType::UP));
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		move(Direction(DirectionType::DOWN));
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
	shaderManager->use(ShaderManager::TEXT_PROGRAM);
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

