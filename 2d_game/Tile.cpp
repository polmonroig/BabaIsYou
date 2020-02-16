#include <GL/glew.h>
#include <GL/gl.h>
#include "Tile.h"

Tile::Tile() {
	properties.setIsActive(false);
}

Tile::Tile(int i, int j, float x, float y, float width, float height, int shaderProgramID){
	properties.setAnimation(Managers::animationsManager.getAnimatedSprite(0));
	programID = shaderProgramID;
	xPos = x;
	yPos = y;
	tileWidth = width;
	iIndex = i;
	jIndex = j;
	tileHeight = height;
}

void Tile::init() {
	properties.setIsActive(true);
	properties.setCanMove(true);
	float* vertices = calculateVertices();
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	sendVertices();
	posLocation = Managers::shaderManager.bindVertexAttribute(programID, "position", 3, 5 * sizeof(float), 0);
	texCoordLocation = Managers::shaderManager.bindVertexAttribute(programID, "texCoord", 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

}





float* Tile::calculateVertices() {
	float* texCoords = properties.getTextureCoordinates();

	float vertices[30] = { xPos, yPos, 0.0, 
							texCoords[Sprite::TOP_LEFT_X], texCoords[Sprite::TOP_LEFT_Y], // ok
						 xPos + tileWidth, yPos, 0.0, 
							texCoords[Sprite::TOP_RIGHT_X], texCoords[Sprite::TOP_RIGHT_Y],
						 xPos + tileWidth, yPos + tileHeight, 0.0, 
							texCoords[Sprite::BOTTOM_RIGHT_X], texCoords[Sprite::BOTTOM_RIGHT_Y], // ok
						 xPos, yPos, 0.0, 
							texCoords[Sprite::TOP_LEFT_X], texCoords[Sprite::TOP_LEFT_Y], // ok
						 xPos + tileWidth, yPos + tileHeight,  0.0, 
							texCoords[Sprite::BOTTOM_RIGHT_X], texCoords[Sprite::BOTTOM_RIGHT_Y], // ok
						 xPos, yPos + tileHeight, 0.0, 
							texCoords[Sprite::BOTTOM_LEFT_X], texCoords[Sprite::BOTTOM_LEFT_Y] };

	return vertices;
}

void Tile::move(float moveX, float moveY) {
	if (properties.getCanMove()) {
		xPos += moveX * tileWidth;
		yPos += moveY * tileHeight;
		iIndex += moveY;
		jIndex += moveX;
		sendVertices();
	}
}

int Tile::getIIndex() const {
	return iIndex;
}

int Tile::getJIndex() const {
	return jIndex;
}

void Tile::sendVertices() {
	auto vertices = calculateVertices();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), vertices, GL_STATIC_DRAW);
}

void Tile::render(){
	if (properties.getIsActive()) {
		sendVertices();
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

