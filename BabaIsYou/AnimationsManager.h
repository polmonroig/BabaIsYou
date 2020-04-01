#ifndef ANIMATIONS_MANAGER_H
#define ANIMATIONS_MANAGER_H

#include <vector>

#include "SpriteSheet.h"
#include "AnimatedSprite.h"
#include "Direction.h"


class AnimationsManager{
	
public:

	
	static const int N_SPRITES = 6;

	// sprites
	static const int SPRITE = 0;
	static const int BABA = 1;
	static const int ROCK = 2;
	static const int WALL = 3;
	static const int SKULL = 4;
	static const int FLAG = 5;
	static const int GRASS = 6;
	
	// names 
	static const int NAME = 1;
	static const int BABA_N = 7;
	static const int ROCK_N = 8;
	static const int WALL_N = 9;
	static const int SKULL_N = 10;
	static const int FLAG_N = 11;
	static const int GRASS_N = 12;

	// operators
	static const int OPERATOR = 2;
	static const int IS = 13;
	static const int MAKE = 14;

	// properties 
	static const int PROPERTY = 3;
	static const int WIN = 15;
	static const int YOU = 16;
	static const int PUSH = 17;
	static const int STOP = 18;
	static const int DEFEAT = 19;
	static const int PLAY = 20;
	static const int SINK = 21;

	// extras
	static const int MOVE_EFFECT = 21;
	

	void init();
	void free();

	AnimatedSprite* getAnimatedSprite(int id) ;
	AnimatedSprite* getAnimatedLetter(int id);

private:

	const float SPRITE_WIDTH = 768.0;
	const float SPRITE_HEIGHT = 1584.0;
	const float WALK_SIZE = 24;
	const float sizeX = WALK_SIZE / SPRITE_WIDTH;
	const float sizeY = WALK_SIZE / SPRITE_HEIGHT;


	void createSprites();
	
	void createNames();

	void createOperators();

	void createProperties();

	void createExtras();

	void createLibrary();

	SpriteSheet sprites;

	std::vector<AnimatedSprite*> animatedSprites;

	std::vector<AnimatedSprite*> library;

};


#endif

