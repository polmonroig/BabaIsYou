#include "AnimationsManager.h"



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
	animation.setDirection(Direction(DirectionType::DOWN));
	animation.generateSprites(sprites);
	animatedSprites.push_back(animation);

}




AnimatedSprite& AnimationsManager::getAnimatedSprite(int id) {
	animatedSprites[id].addReference();
	return animatedSprites[id];
}