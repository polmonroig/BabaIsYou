#include "Sprite.h"



Sprite::Sprite(SpriteSheet & spritesReference) {
	parent = &spritesReference;
}

void Sprite::render() const {
	parent->render();
}


void Sprite::setLeftTop(float coordX, float coordY) {
	textureCoordinates[TOP_LEFT_X] = coordX;
	textureCoordinates[TOP_LEFT_Y] = coordY;
}

void Sprite::setLeftBottom(float coordX, float coordY) {
	textureCoordinates[BOTTOM_LEFT_X] = coordX;
	textureCoordinates[BOTTOM_LEFT_Y] = coordY;
}

void Sprite::setRightTop(float coordX, float coordY) {
	textureCoordinates[TOP_RIGHT_X] = coordX;
	textureCoordinates[TOP_RIGHT_Y] = coordY;
}

void Sprite::setRightBottom(float coordX, float coordY) {
	textureCoordinates[BOTTOM_RIGHT_X] = coordX;
	textureCoordinates[BOTTOM_RIGHT_Y] = coordY;
}



float* Sprite::getTextureCoordinates()  {
	return textureCoordinates;
}