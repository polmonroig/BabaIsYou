#ifndef ANIMATED_SPRITE_H 
#define ANIMATED_SPRITE_H 

#include <vector>
#include <glm/glm.hpp>

#include "Sprite.h"

class AnimatedSprite {

public:

	AnimatedSprite();


	void setFrameRate(int frameRate);
	void setSpritesSize(int spritesSize);
	void setTextureDimensions(float texWidth, float texHeight);
	void setInitialCoordinates(float initialX, float initialY);
	void setDirection(float dirX, float dirY);
	void generateSprites(SpriteSheet& spriteSheet);

	float* getTextureCoordinates() ;
	void render();

private:
	
	int max_frame, current_sprite, frame_counter, size;
	float width, height;
	float initX, initY;
	float directionX, directionY;

	std::vector<Sprite> sprites;

};


#endif 