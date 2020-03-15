#ifndef ANIMATED_SPRITE_SET
#define ANIMATED_SPRITE_SET

#include "AnimatedSprite.h"

class AnimatedSpriteSet : public AnimatedSprite{

public:

	float* getTextureCoordinates() ;
	void render();

private:

	AnimatedSprite upAnimation;
	AnimatedSprite downAnimation;
	AnimatedSprite leftAnimation;
	AnimatedSprite rightAnimation;
	AnimatedSprite* currentAnimation;

};


#endif 

