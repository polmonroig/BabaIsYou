#include "AnimatedSprite.h"


Direction AnimatedSprite::direction;
int AnimatedSprite::max_frame;
int AnimatedSprite::size;
float AnimatedSprite::width, AnimatedSprite::height;


AnimatedSprite::AnimatedSprite() {
	current_sprite = 0;
	frame_counter = 0;
	initX = initY = 0;
	references = 0;
	
}

void AnimatedSprite::setFrameRate(int frameRate) {
	max_frame = frameRate;
}

void AnimatedSprite::setColor(glm::vec3 const& spriteColor) {
	color = spriteColor;
}

void AnimatedSprite::setSpritesSize(int spritesSize) {
	size = spritesSize;
}

void AnimatedSprite::setDirection(Direction const& dir) {
	direction = dir;
}

void AnimatedSprite::setInitialCoordinates(float initialX, float initialY) {
	initX = initialX;
	initY = initialY;
}

void AnimatedSprite::setTextureDimensions(float texWidth, float texHeight) {
	width = texWidth;
	height = texHeight;
}

void AnimatedSprite::generateSprites(std::shared_ptr<SpriteSheet> const& spriteSheet) {
	float posX = initX;
	float posY = initY;

	for (int i = 0; i < size; ++i) {
		// generate sprite
		Sprite sprite(spriteSheet);
		sprite.setLeftTop(posX, posY);
		sprite.setLeftBottom(posX, posY + height);
		sprite.setRightTop(posX + width, posY);
		sprite.setRightBottom(posX + width, posY + height);
		sprites.push_back(sprite);
		// update position 
		auto dirPair = direction.getDir();
		posX = posX + width * dirPair.first;
		posY = posY + height * dirPair.second;
	}
}

float* AnimatedSprite::getTextureCoordinates()  {
	return sprites[current_sprite].getTextureCoordinates();
}

void AnimatedSprite::addReference() {
	references++;
}

glm::vec3 AnimatedSprite::getColor() const {
	return color;
}

void AnimatedSprite::removeReference() {

	references--;
}

void AnimatedSprite::render() {
	
	if (frame_counter >= max_frame * references) {
		frame_counter = 0;
		current_sprite = (current_sprite + 1) % sprites.size();
	}
	sprites[current_sprite].render();
	frame_counter++;
}