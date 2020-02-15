#ifndef ANIMATED_SPRITE_H 
#define ANIMATED_SPRITE_H 

#include <vector>
#include <glm/glm.h>

#include "Sprite.h"

class AnimatedSprite {

public:

	AnimatedSprite() = default;

	AnimatedSprite(int max_frame_counter);

	void addSprite(Sprite const& sprite);

	glm::vec2 getTextureCoordinates() const;

	void render();

private:
	
	int max_frame, current_sprite, frame_counter;

	std::vector<Sprite> sprites;

};


#endif 