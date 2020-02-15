#include "Sprite.h"



Sprite::Sprite(SpriteSheet const& spritesReference) {
	*parent = spritesReference;
}

void Sprite::render() const {
	parent->render();
}


void Sprite::setTextureCoordinates(glm::vec2 const& coordinates) {
	textureCoordinates = coordinates;
}


glm::vec2 Sprite::getTextureCoordinates() const {
	return textureCoordinates;
}