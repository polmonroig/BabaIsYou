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
	void setColor(glm::vec3 const& spriteColor);
	glm::vec3 getColor() const;
	void setDirection(Direction const& dir);
	void generateSprites(SpriteSheet& spriteSheet);
	void setInitialCoordinates(float initialX, float initialY);
	void addReference();
	void removeReference();
	
	
	// DERIVED
	float* getTextureCoordinates();
	void render();

protected:
	
	static int max_frame; // frame rate
	static int size;
	static Direction direction;

	int current_sprite, frame_counter;
	static float width, height;
	float initX, initY;
	int references;
	
	glm::vec3 color;


	std::vector<Sprite> sprites;

	

};


#endif 