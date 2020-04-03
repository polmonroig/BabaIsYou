#include "Background.h"


Background::Background(float xPos, float yPos, float width, float height) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->width = width;
	this->height = height;
	color = glm::vec3(0.031, 0.031, 0.031);
}


void Background::free() {
	glDeleteBuffers(1, &vbo);
}

void Background::setColor(glm::vec3 const& c) {
	color = c;
}

void Background::init() {

	float vertices[12] = { xPos, yPos,
						 xPos + width, yPos,
						 xPos + width, yPos + height,
						 xPos, yPos,
						 xPos + width, yPos + height,
						 xPos, yPos + height };


	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = ServiceLocator::getShaderManager()->bindVertexAttribute("position", 2, 2 * sizeof(float), 0);
	ServiceLocator::getShaderManager()->setUniform("color", color.x, color.y, color.z);
}

void Background::render() {
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}