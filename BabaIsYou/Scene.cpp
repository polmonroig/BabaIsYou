#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include <GL/glut.h>



void Scene::init(){
	currentLevel = 0;
	initShaders();
	initTextures();
	loadMenu();
	state = GameState::MENU;
	// loadLevel(); 
}

void Scene::loadMenu() {
	auto width = glutGet(GLUT_WINDOW_WIDTH);
	auto height = glutGet(GLUT_WINDOW_HEIGHT);
	projectionMatrix = glm::ortho(0.0f, float(width - 1), float(height - 1), 0.0f, 0.0f, 100.0f);
	menu.init(width, height);
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

void Scene::selectElement() {
	if (state == GameState::MENU) {
		bool play = menu.select();
		if (play) {
			state = GameState::GAMING;
			loadLevel();
		}
	}
}

void Scene::move(Direction const& direction) {
	if (state == GameState::MENU) {
		menu.move(direction);
	}
	else {
		map.movePlayerTiles(direction);
	}
	
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
	auto shaderManager = ServiceLocator::getShaderManager();
	glm::mat4 modelviewMatrix = glm::mat4(1.0f);
	
	shaderManager->use(ShaderManager::BACKGROUND_PROGRAM);
	shaderManager->setUniform("projectionMatrix", projectionMatrix);
	shaderManager->setUniform("modelViewMatrix", modelviewMatrix);

	if (state == GameState::MENU) {
		shaderManager->use(ShaderManager::TEXT_PROGRAM);
		shaderManager->setUniform("projectionMatrix", projectionMatrix);
		shaderManager->setUniform("modelViewMatrix", modelviewMatrix);
		menu.render();
	}
	else {
		shaderManager->use(ShaderManager::TILE_PROGRAM);
		shaderManager->setUniform("projectionMatrix", projectionMatrix);
		shaderManager->setUniform("modelViewMatrix", modelviewMatrix);
		map.render();
	}
	
}


void Scene::initTextures() {
	ServiceLocator::getAnimationsManager()->init();
}


void Scene::initShaders(){
	ServiceLocator::getShaderManager()->init();
}

