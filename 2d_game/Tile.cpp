#include <GL/glew.h>
#include <GL/gl.h>
#include "Tile.h"

Tile::Tile() {
	properties.setIsActive(false);
}

Tile::Tile(float x, float y, float width, float height, int shaderProgramID){
	properties.setIsActive(true);
	properties.setAnimation(Managers::animationsManager.getAnimatedSprite(0));
	programID = shaderProgramID;
	xPos = x;
	yPos = y;
	tileWidth = width;
	tileHeight = height;
	float* vertices = calculateVertices();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = Managers::shaderManager.bindVertexAttribute(programID, "position", 2, 4 * sizeof(float), 0);
	texCoordLocation = Managers::shaderManager.bindVertexAttribute(programID, "texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

float* Tile::calculateVertices() {
	glm::vec2 texCoords = properties.getTextureCoordinates();
	float vertices[24] = { xPos, yPos, texCoords.x, texCoords.x,
						 xPos + tileWidth, yPos,texCoords.y, texCoords.x,
						 xPos + tileWidth, yPos + tileHeight, texCoords.y, texCoords.y,
						 xPos, yPos, texCoords.x, texCoords.x,
						 xPos + tileWidth, yPos + tileHeight, texCoords.y, texCoords.y,
						 xPos, yPos + tileHeight, texCoords.x, texCoords.y };

	return vertices;
}

void Tile::move(float moveX, float moveY) {
	if (properties.getCanMove()) {
		xPos += moveX * tileWidth;
		yPos += moveY * tileHeight;
		auto vertices = calculateVertices();
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
		posLocation = Managers::shaderManager.bindVertexAttribute(programID, "position", 2, 4 * sizeof(float), 0);
		texCoordLocation = Managers::shaderManager.bindVertexAttribute(programID, "texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	}
}


void Tile::render(){
	if (properties.getIsActive()) {

		properties.render();
		glBindVertexArray(vao);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
}


// pre: the two tiles are adjecent and the current tile is 
//		moved toward the second tile => thus it collides unles 
//		it is inactive 
bool Tile::collides(Tile const& other) const {
	return other.properties.getIsActive();
}

void Tile::free()
{
	glDeleteBuffers(1, &vbo);
}

