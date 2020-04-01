#ifndef MOVEMENT_PARTICLE_H
#define MOVEMENT_PARTICLE_H

#include "AnimatedSprite.h"
#include "ServiceLocator.h"

class MovementParticle{

public:

	MovementParticle() = default;

	MovementParticle(float x, float y, float size);
	
	void init();

	void render(glm::vec3 const& color);



private:

	float xPos, yPos, particleSize;
	GLuint vao, vbo;
	GLuint posLocation, texCoordLocation;
	float* calculateVertices();
	void sendVertices();
	AnimatedSprite* animation;

};


#endif 

