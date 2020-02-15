#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>

#include "SpriteSheet.h"


class Sprite{

public:

	static const int TOP_LEFT_X = 0;
	static const int TOP_LEFT_Y = 1;
	static const int TOP_RIGHT_X = 2;
	static const int TOP_RIGHT_Y = 3;
	static const int BOTTOM_LEFT_X = 4;
	static const int BOTTOM_LEFT_Y = 5;
	static const int BOTTOM_RIGHT_X = 6;
	static const int BOTTOM_RIGHT_Y = 7;


	Sprite(SpriteSheet & spritesReference);

	void render() const;

	void setLeftTop(float coordX, float coordY);
	void setLeftBottom(float coordX, float coordY);
	void setRightTop(float coordX, float coordY);
	void setRightBottom(float coordX, float coordY);

	float* getTextureCoordinates();

private:

	float textureCoordinates[8];
	SpriteSheet* parent;

};

#endif

