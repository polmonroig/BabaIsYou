#ifndef ANIMATIONS_MANAGER_H
#define ANIMATIONS_MANAGER_H

#include <vector>

#include "SpriteSheet.h"
#include "AnimatedSprite.h"
#include "Direction.h"

class AnimationsManager{
	
public:

	
	// names
	static const int BABA = 0;
	static const int ROCK = 1;
	static const int WALL = 2;
	static const int LAVA = 3;
	static const int FLAG = 4;
	static const int GRASS = 5;
	
	// operators
	static const int IS = 6;
	static const int FEAR = 7;

	// properties 
	static const int WIN = 8;
	static const int YOU = 9;
	static const int PUSH = 10;
	static const int STOP = 11;
	static const int DEFEAT = 12;
	

	void init();

	AnimatedSprite& getAnimatedSprite(int id) ;

private:

	const float SPRITE_WIDTH = 768.0;
	const float SPRITE_HEIGHT = 1584.0;
	const float WALK_SIZE = 24;

	SpriteSheet sprites;

	std::vector<AnimatedSprite> animatedSprites;

};


#endif

