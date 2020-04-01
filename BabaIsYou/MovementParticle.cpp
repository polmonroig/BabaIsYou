#include "MovementParticle.h"


MovementParticle::MovementParticle(float x, float y, float size) {
	xPos = x;
	yPos = y;
	particleSize = size;
}


void MovementParticle::init(){
	auto shader = ServiceLocator::getShaderManager();
	shader->use(ShaderManager::PARTICLE_PROGRAM);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	sendVertices();
	auto shaderM = ServiceLocator::getShaderManager();
	posLocation = shaderM->bindVertexAttribute("position", 3, 5 * sizeof(float), 0);
	texCoordLocation = shaderM->bindVertexAttribute("texCoord", 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void MovementParticle::render(glm::vec3 const& color) {
	auto shader = ServiceLocator::getShaderManager();
	shader->use(ShaderManager::PARTICLE_PROGRAM);
	sendVertices();
	ServiceLocator::getShaderManager()->setUniform("color", color.x, color.y , color.z);
	animation->render();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void MovementParticle::sendVertices() {
	auto vertices = calculateVertices();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), vertices, GL_STATIC_DRAW);
}

float* MovementParticle::calculateVertices() {
	float* texCoords = animation->getTextureCoordinates();

	float vertices[30] = { xPos, yPos, 0.0,
							texCoords[Sprite::TOP_LEFT_X], texCoords[Sprite::TOP_LEFT_Y], // ok
						 xPos + particleSize, yPos, 0.0,
							texCoords[Sprite::TOP_RIGHT_X], texCoords[Sprite::TOP_RIGHT_Y],
						 xPos + particleSize, yPos + particleSize, 0.0,
							texCoords[Sprite::BOTTOM_RIGHT_X], texCoords[Sprite::BOTTOM_RIGHT_Y], // ok
						 xPos, yPos, 0.0,
							texCoords[Sprite::TOP_LEFT_X], texCoords[Sprite::TOP_LEFT_Y], // ok
						 xPos + particleSize, yPos + particleSize,  0.0,
							texCoords[Sprite::BOTTOM_RIGHT_X], texCoords[Sprite::BOTTOM_RIGHT_Y], // ok
						 xPos, yPos + particleSize, 0.0,
							texCoords[Sprite::BOTTOM_LEFT_X], texCoords[Sprite::BOTTOM_LEFT_Y] };

	return vertices;
}