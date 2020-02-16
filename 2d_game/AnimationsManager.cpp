#include "AnimationsManager.h"

#include <iostream> // DEBUGGING

void AnimationsManager::init() {
	sprites.loadFromFile("images/sprite-sheet.png");
	
	float sizeX = WALK_SIZE / SPRITE_WIDTH;
	float sizeY = WALK_SIZE / SPRITE_HEIGHT;
	// create walking animation
	AnimatedSprite animation;
	animation.setFrameRate(5);
	animation.setSpritesSize(3);
	animation.setTextureDimensions(sizeX, sizeY);
	animation.setInitialCoordinates(0, 0);
	animation.setDirection(0, 1);
	animation.generateSprites(sprites);
	animatedSprites.push_back(animation);
}

void  AnimationsManager::setDeltaTime(float deltaTime) {
	for (auto& animation : animatedSprites) {
		animation.setDeltaTime(deltaTime);
	}
}


AnimatedSprite& AnimationsManager::getAnimatedSprite(int id) {
	return animatedSprites[id];
}