#include "AnimationsManager.h"

#include <iostream> // debug


void AnimationsManager::init() {
	sprites = std::make_shared<SpriteSheet>();
	sprites->loadFromFile("images/sprite-sheet.png");

	createSprites();
	createNames();
	createOperators();
	createProperties();
	createLibrary();
}


// A B C D E F G H I     L M N O     R S T U V W X Y Z 
//                   J K         P Q
void AnimationsManager::createLibrary() {
	int nLetters = 25;
	float initX = 0;
	for (int i = 0; i < nLetters; ++i) {
		std::shared_ptr<AnimatedSprite> letter = std::make_shared<AnimatedSprite>();
		letter->setInitialCoordinates(initX, sizeY * 36);
		letter->setColor(glm::vec3(1, 1, 1));
		letter->generateSprites(sprites);
		if(i != 9 && i != 10 && i != 15 && i != 16)initX += sizeX;
		library.push_back(letter);
	}
}

std::shared_ptr<AnimatedSprite> AnimationsManager::getAnimatedLetter(int id) {
	return library[id];
}


void AnimationsManager::createSprites() {
	// create BABA

	std::shared_ptr<AnimatedSprite> animationBaba = std::make_shared<AnimatedSprite>();
	animationBaba->setFrameRate(9);
	animationBaba->setSpritesSize(3);
	animationBaba->setTextureDimensions(sizeX, sizeY);
	animationBaba->setInitialCoordinates(0, 0);
	animationBaba->setDirection(Direction(DirectionType::DOWN));
	animationBaba->generateSprites(sprites);
	animationBaba->setColor(glm::vec3(1, 1, 1));
	animatedSprites.push_back(animationBaba);


	// create Rock
	std::shared_ptr<AnimatedSprite>  animationRock = std::make_shared<AnimatedSprite>();
	animationRock->setInitialCoordinates(sizeX * 15, sizeY * 21);
	animationRock->generateSprites(sprites);
	animationRock->setColor(glm::vec3(0.65, 0.52, 0.23));
	animatedSprites.push_back(animationRock);

	// create wall
	std::shared_ptr<AnimatedSprite>  animationWall = std::make_shared<AnimatedSprite>();
	animationWall->setInitialCoordinates(sizeX * 19, sizeY * 21);
	animationWall->generateSprites(sprites);
	animationWall->setColor(glm::vec3(0.16, 0.19, 0.25));
	animatedSprites.push_back(animationWall);

	// create SKULL 
	std::shared_ptr<AnimatedSprite>  animationLava = std::make_shared<AnimatedSprite>();
	animationLava->setInitialCoordinates(sizeX * 11, sizeY * 15);
	animationLava->generateSprites(sprites);
	animationLava->setColor(glm::vec3(0.7, 0.3, 0.3));
	animatedSprites.push_back(animationLava);

	// create flag 
	std::shared_ptr<AnimatedSprite>  animationFlag = std::make_shared<AnimatedSprite>();
	animationFlag->setInitialCoordinates(sizeX * 6, sizeY * 21);
	animationFlag->generateSprites(sprites);
	animationFlag->setColor(glm::vec3(0.92, 0.87, 0.5333333));
	animatedSprites.push_back(animationFlag);

	// create grass 
	std::shared_ptr<AnimatedSprite> animationGrass = std::make_shared<AnimatedSprite>();
	animationGrass->setInitialCoordinates(0, sizeY * 51);
	animationGrass->generateSprites(sprites);
	animationGrass->setColor(glm::vec3(0.164, 0.19215, 0.14117));
	animatedSprites.push_back(animationGrass);
}


void AnimationsManager::createProperties() {
	// create WIN 
	std::shared_ptr<AnimatedSprite>  animationWin = std::make_shared<AnimatedSprite>();
	animationWin->setInitialCoordinates(sizeX * 17, sizeY * 42);
	animationWin->generateSprites(sprites);
	animationWin->setColor(glm::vec3(0.46, 0.435, 0.25));
	animatedSprites.push_back(animationWin);

	// create YOU 
	std::shared_ptr<AnimatedSprite>  animationYou = std::make_shared<AnimatedSprite>();
	animationYou->setInitialCoordinates(sizeX * 20, sizeY * 42);
	animationYou->generateSprites(sprites);
	animationYou->setColor(glm::vec3(0.358, 0.115, 0.205));
	animatedSprites.push_back(animationYou);

	// create PUSH 
	std::shared_ptr<AnimatedSprite>  animationPush = std::make_shared<AnimatedSprite>();
	animationPush->setInitialCoordinates(sizeX * 2, sizeY * 42);
	animationPush->generateSprites(sprites);
	animationPush->setColor(glm::vec3(0.38, 0.5, 0.5));
	animatedSprites.push_back(animationPush);

	// create STOP 
	std::shared_ptr<AnimatedSprite>  animationStop = std::make_shared<AnimatedSprite>();
	animationStop->setInitialCoordinates(sizeX * 12, sizeY * 42);
	animationStop->generateSprites(sprites);
	animationStop->setColor(glm::vec3(0.19, 0.32, 0.15));
	animatedSprites.push_back(animationStop);

	// create DEFEAT 
	std::shared_ptr<AnimatedSprite>  animationDefeat = std::make_shared<AnimatedSprite>();
	animationDefeat->setInitialCoordinates(sizeX * 5, sizeY * 39);
	animationDefeat->generateSprites(sprites);
	animationDefeat->setColor(glm::vec3(0.35, 0.15, 0.14));
	animatedSprites.push_back(animationDefeat);

	// create PLAY 
	std::shared_ptr<AnimatedSprite>  animationPlay = std::make_shared<AnimatedSprite>();
	animationPlay->setInitialCoordinates(sizeX * 7, sizeY * 33);
	animationPlay->generateSprites(sprites);
	animationPlay->setColor(glm::vec3(0.46, 0.435, 0.25));
	animatedSprites.push_back(animationPlay);

	// create SINK 
	std::shared_ptr<AnimatedSprite>  animationSink = std::make_shared<AnimatedSprite>();
	animationSink->setInitialCoordinates(sizeX * 9, sizeY * 42);
	animationSink->generateSprites(sprites);
	animationSink->setColor(glm::vec3(0.46, 0.435, 0.25));
	animatedSprites.push_back(animationSink);
}

void AnimationsManager::createOperators() {
	// create IS 
	std::shared_ptr<AnimatedSprite>  animationIs = std::make_shared<AnimatedSprite>();
	animationIs->setInitialCoordinates(sizeX * 18, sizeY * 30);
	animationIs->generateSprites(sprites);
	animationIs->setColor(glm::vec3(0.5, 0.5, 0.5));
	animatedSprites.push_back(animationIs);

	// create MAKE 
	std::shared_ptr<AnimatedSprite>  animationMake = std::make_shared<AnimatedSprite>();
	animationMake->setInitialCoordinates(sizeX * 29, sizeY * 30);
	animationMake->generateSprites(sprites);
	animationMake->setColor(glm::vec3(0.5, 0.5, 0.5));
	animatedSprites.push_back(animationMake);
}

void AnimationsManager::createNames() {
	// create BABA
	std::shared_ptr<AnimatedSprite>  animationBaba = std::make_shared<AnimatedSprite>();
	animationBaba->setInitialCoordinates(sizeX * 6, sizeY * 27);
	animationBaba->generateSprites(sprites);
	animationBaba->setColor(glm::vec3(0.717, 0.23, 0.41));
	animatedSprites.push_back(animationBaba);

	// create Rock
	std::shared_ptr<AnimatedSprite>  animationRock = std::make_shared<AnimatedSprite>();
	animationRock->setInitialCoordinates(sizeX * 11, sizeY * 33);
	animationRock->generateSprites(sprites);
	animationRock->setColor(glm::vec3(0.325, 0.26, 0.115));
	animatedSprites.push_back(animationRock);

	// create wall
	std::shared_ptr<AnimatedSprite>  animationWall = std::make_shared<AnimatedSprite>();
	animationWall->setInitialCoordinates(sizeX * 27, sizeY * 33);
	animationWall->generateSprites(sprites);
	animationWall->setColor(glm::vec3(0.3, 0.3, 0.375));
	animatedSprites.push_back(animationWall);

	// create SKULL 
	std::shared_ptr<AnimatedSprite>  animationLava = std::make_shared<AnimatedSprite>();
	animationLava->setInitialCoordinates(sizeX * 16, sizeY * 33);
	animationLava->generateSprites(sprites);
	animationLava->setColor(glm::vec3(0.45, 0.17, 0.135)); 
	animatedSprites.push_back(animationLava);

	// create flag 
	std::shared_ptr<AnimatedSprite>  animationFlag = std::make_shared<AnimatedSprite>();
	animationFlag->setInitialCoordinates(sizeX, sizeY * 30);
	animationFlag->generateSprites(sprites);
	animationFlag->setColor(glm::vec3(0.46, 0.435, 0.25));
	animatedSprites.push_back(animationFlag);

	// create grass 
	std::shared_ptr<AnimatedSprite>  animationGrass = std::make_shared<AnimatedSprite>();
	animationGrass->setInitialCoordinates(sizeX * 9, sizeY * 30);
	animationGrass->generateSprites(sprites);
	animationGrass->setColor(glm::vec3(0.5, 0.5, 0.5));
	animatedSprites.push_back(animationGrass);


	
}



std::shared_ptr<AnimatedSprite>  AnimationsManager::getAnimatedSprite(int id) { 
	return animatedSprites[id];
}