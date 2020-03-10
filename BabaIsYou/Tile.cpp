#include <GL/glew.h>
#include <GL/gl.h>
#include "Tile.h"

Tile::Tile() {
	isActive = false;
	canMove = false;;
}

Tile::Tile(float x, float y, float width, float height, int tileType,  int shaderProgramID){
	auto manager = ServiceLocator::getAnimationsManager();
	animatedSprite = &manager->getAnimatedSprite(tileType);
	programID = shaderProgramID;
	xPos = x;
	yPos = y;
	tileWidth = width;
	tileHeight = height;
	collisionType = CollisionType::Fixed;
	type = tileType;
}

void Tile::setCanMove(bool value) {
	canMove = value;
}

void Tile::init() {
	isActive = true;
	canMove = true;
	float* vertices = calculateVertices();
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	sendVertices();
	auto shaderM = ServiceLocator::getShaderManager();
	posLocation = shaderM->bindVertexAttribute(programID, "position", 3, 5 * sizeof(float), 0);
	texCoordLocation = shaderM->bindVertexAttribute(programID, "texCoord", 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

}

void Tile::setCollisionType(CollisionType const& t) {
	collisionType = t;
}

CollisionType Tile::getCollisionType() const {
	return collisionType;
}

bool Tile::getCanMove() const {
	return canMove;
}


float* Tile::calculateVertices() {
	float* texCoords = animatedSprite->getTextureCoordinates();

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

void Tile::move(Direction const& dir) {
	auto dirPair = dir.getDir();
	xPos += dirPair.first * tileWidth;
	yPos += dirPair.second * tileHeight;
	sendVertices();
}



void Tile::sendVertices() {
	auto vertices = calculateVertices();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), vertices, GL_STATIC_DRAW);
}

void Tile::setActive(bool value) {
	isActive = value;
}

bool Tile::getActive() const{
	return isActive;
}

void Tile::render(){
	if (isActive) {
		sendVertices();
		animatedSprite->render();
		glBindVertexArray(vao);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
}


// pre: the two tiles are adjecent and the current tile is 
//		moved toward the second tile => thus it collides unles 
//		it is inactive 
CollisionType Tile::collide(Tile const& other) const {
	return other.getCollisionType();
}

void Tile::free(){
	animatedSprite->removeReference();
	glDeleteBuffers(1, &vbo);
}

