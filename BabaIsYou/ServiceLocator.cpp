#include "ServiceLocator.h"


ShaderManager* ServiceLocator::shaders = new ShaderManager();
AnimationsManager* ServiceLocator::animations = new AnimationsManager();

ShaderManager* ServiceLocator::getShaderManager() {
	return shaders;
}

AnimationsManager* ServiceLocator::getAnimationsManager() {
	return animations;
}
