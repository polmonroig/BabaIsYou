#include <GL/glew.h>
#include <GL/gl.h>
#include "Tile.h"

Tile::Tile() {
	active = false;
}

Tile::Tile(float x, float y, float width, float height, int shaderProgramID, SpriteSheet const& spritesReference){
	active = true;
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
	// setup sprites 
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	animated_sprite = AnimatedSprite(5);
	animated_sprite.addSprite(Managers::BABA_00);


}

float* Tile::calculateVertices() {
	auto texCoords = animated_sprite.getTextureCoordinates();
	float vertices[24] = { xPos, yPos, texCoords[0], texCoords[0],
						 xPos + tileWidth, yPos,texCoords[1], texCoords[0],
						 xPos + tileWidth, yPos + tileHeight, texCoords[1], texCoords[1],
						 xPos, yPos, texCoords[0], texCoords[0],
						 xPos + tileWidth, yPos + tileHeight, texCoords[1], texCoords[1],
						 xPos, yPos + tileHeight, texCoords[0], texCoords[1], };
	return vertices;
}

void Tile::move(float moveX, float moveY) {
	xPos += moveX * tileWidth;
	yPos += moveY * tileHeight;
	auto vertices = calculateVertices();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = Managers::shaderManager.bindVertexAttribute(programID, "position", 2, 4 * sizeof(float), 0);
	texCoordLocation = Managers::shaderManager.bindVertexAttribute(programID, "texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}


void Tile::render(){
	if (active) {
		animated_sprite.render();
		glBindVertexArray(vao);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
}

void Tile::free()
{
	glDeleteBuffers(1, &vbo);
}

