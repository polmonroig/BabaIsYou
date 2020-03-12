#include "AnimationsManager.h"

#include <iostream> // debug


void AnimationsManager::init() {
	sprites.loadFromFile("images/sprite-sheet.png");
	
	float sizeX = WALK_SIZE / SPRITE_WIDTH;
	float sizeY = WALK_SIZE / SPRITE_HEIGHT;
	// create BABA
	AnimatedSprite animationBaba;
	animationBaba.setFrameRate(5);
	animationBaba.setSpritesSize(3);
	animationBaba.setTextureDimensions(sizeX, sizeY);
	animationBaba.setInitialCoordinates(0, 0);
	animationBaba.setDirection(Direction(DirectionType::DOWN));
	animationBaba.generateSprites(sprites);
	animationBaba.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationBaba);

	// create Rock
	AnimatedSprite animationRock;
	animationRock.setInitialCoordinates(sizeX * 15, sizeY * 21);
	animationRock.generateSprites(sprites);
	animationRock.setColor(glm::vec3(0.5, 0.4, 0.29));
	animatedSprites.push_back(animationRock);

	// create wall
	AnimatedSprite animationWall;
	animationWall.setInitialCoordinates(sizeX * 19, sizeY * 21);
	animationWall.generateSprites(sprites);
	animationWall.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationWall);

	// create lava 
	AnimatedSprite animationLava;
	animationLava.setInitialCoordinates(sizeX * 5, sizeY * 24);
	animationLava.generateSprites(sprites);
	animationLava.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationLava);

	// create flag 
	AnimatedSprite animationFlag;
	animationFlag.setInitialCoordinates(sizeX * 6, sizeY * 21);
	animationFlag.generateSprites(sprites);
	animationFlag.setColor(glm::vec3(1, 0.94, 0.41));
	animatedSprites.push_back(animationFlag);

	// create grass 
	AnimatedSprite animationGrass;
	animationGrass.setInitialCoordinates(sizeX * 14, sizeY * 24);
	animationGrass.generateSprites(sprites);
	animationGrass.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationGrass);

	// create IS 
	AnimatedSprite animationIs;
	animationIs.setInitialCoordinates(sizeX * 18, sizeY * 30);
	animationIs.generateSprites(sprites);
	animationIs.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationIs);

	// create FEAR 
	AnimatedSprite animationFear;
	animationFear.setInitialCoordinates(sizeX * 30, sizeY * 27);
	animationFear.generateSprites(sprites);
	animationFear.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationFear);


	// create WIN 
	AnimatedSprite animationWin;
	animationWin.setInitialCoordinates(sizeX * 17, sizeY * 42);
	animationWin.generateSprites(sprites);
	animationWin.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationWin);

	// create YOU 
	AnimatedSprite animationYou;
	animationYou.setInitialCoordinates(sizeX * 20, sizeY * 42);
	animationYou.generateSprites(sprites);
	animationYou.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationYou);

	// create PUSH 
	AnimatedSprite animationPush;
	animationPush.setInitialCoordinates(sizeX * 2, sizeY * 42);
	animationPush.generateSprites(sprites);
	animationPush.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationPush);

	// create STOP 
	AnimatedSprite animationStop;
	animationStop.setInitialCoordinates(sizeX * 12, sizeY * 42);
	animationStop.generateSprites(sprites);
	animationStop.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationStop);

	// create DEFEAT 
	AnimatedSprite animationDefeat;
	animationDefeat.setInitialCoordinates(sizeX * 5, sizeY * 39);
	animationDefeat.generateSprites(sprites);
	animationDefeat.setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationDefeat);

}




AnimatedSprite& AnimationsManager::getAnimatedSprite(int id) {
	return animatedSprites[id];
}