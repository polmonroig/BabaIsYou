#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(int max_frame_counter) {
	max_frame = max_frame_counter;
	current_sprite = 0;
	frame_counter = 0;
}

void AnimatedSprite::addSprite(Sprite const& sprite) {
	sprites.push_back(sprite);
}


glm::vec2 AnimatedSprite::getTextureCoordinates() const {
	return sprites[current_sprite].getTextureCoordinates();
}

void AnimatedSprite::render() {
	if (frame_counter >= max_frame) {
		frame_counter = 0;
		current_sprite = (current_sprite + 1) % sprites.size();
	}
	sprites[current_sprite].render();
	frame_counter++;
}