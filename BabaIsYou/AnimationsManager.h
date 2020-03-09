#ifndef ANIMATIONS_MANAGER_H
#define ANIMATIONS_MANAGER_H

#include <vector>

#include "SpriteSheet.h"
#include "AnimatedSprite.h"
#include "Direction.h"

class AnimationsManager{
	
public:

	const float SPRITE_WIDTH = 768.0;
	const float SPRITE_HEIGHT = 1584.0;
	const float WALK_SIZE = 24.5;

	void init();

	AnimatedSprite& getAnimatedSprite(int id) ;

private:

	SpriteSheet sprites;

	std::vector<AnimatedSprite> animatedSprites;

};


#endif

