#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "AnimatedSprite.h"

class Properties{

public:

	void setAnimation(AnimatedSprite & anim);

	bool getCanMove() const;
	bool getIsActive() const;

	void setIsActive(bool active);
	void setCanMove(bool move);

	void render() const;

	float* getTextureCoordinates() const;

private:

	AnimatedSprite* animatedSprite;

	bool canMove, isActive;

};



#endif