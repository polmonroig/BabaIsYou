#ifndef ANIMATED_SPRITE_H 
#define ANIMATED_SPRITE_H 

#include <vector>
#include <glm/glm.hpp>

#include "Sprite.h"
#include "SpriteSheet.h"
#include "Direction.h"

class AnimatedSprite {

public:

	AnimatedSprite();


	void setFrameRate(int frameRate);
	void setSpritesSize(int spritesSize);
	void setTextureDimensions(float texWidth, float texHeight);
	void setInitialCoordinates(float initialX, float initialY);
	void setColor(glm::vec3 const& spriteColor);
	glm::vec3 getColor() const;
	void setDirection(Direction const& dir);
	void generateSprites(SpriteSheet& spriteSheet);
	float* getTextureCoordinates() ;
	void addReference();
	void removeReference();
	void render();

private:
	
	static int max_frame;
	static int size;
	int current_sprite, frame_counter;
	static float width, height;
	float initX, initY;
	int references;
	static Direction direction;

	std::vector<Sprite> sprites;

	glm::vec3 color;

};


#endif 