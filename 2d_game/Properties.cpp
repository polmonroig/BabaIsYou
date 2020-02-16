#include "Properties.h"



void Properties::setAnimation(AnimatedSprite & anim) {
	animatedSprite = &anim;
}

bool Properties::getCanMove() const {
	return canMove;
}

void Properties::setCanMove(bool move) {
	canMove = move;
}

void Properties::render()const {
	animatedSprite->render();
}


bool Properties::getIsActive() const {
	return isActive;
}

void Properties::setIsActive(bool active) {
	isActive = active;
}


float* Properties::getTextureCoordinates() const {
	return animatedSprite->getTextureCoordinates();
}