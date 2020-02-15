#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>

#include "SpriteSheet.h"


class Sprite{

public:

	Sprite(SpriteSheet & spritesReference);

	void render() const;

	void setTextureCoordinates(glm::vec2 const& coordinates);

	glm::vec2 getTextureCoordinates() const;

private:

	glm::vec2 textureCoordinates;
	SpriteSheet* parent;

};

#endif

