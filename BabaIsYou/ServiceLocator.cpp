#include "ServiceLocator.h"


ShaderManager* ServiceLocator::shaders = new ShaderManager();
AnimationsManager* ServiceLocator::animations = new AnimationsManager();
bool ServiceLocator::gameEnd = false;



ShaderManager* ServiceLocator::getShaderManager() {
	return shaders;
}

void ServiceLocator::endGame() {
	gameEnd = true;
}


bool ServiceLocator::isGameEnd() {
	bool realValue = gameEnd;
	gameEnd = false;
	return realValue;
}

AnimationsManager* ServiceLocator::getAnimationsManager() {
	return animations;
}
