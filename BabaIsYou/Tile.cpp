#include <GL/glew.h>
#include <GL/gl.h>
#include "Tile.h"

Tile::Tile() {
	isActive = false;
	canMove = false;
	type = 9;
}

Tile::Tile(float x, float y, float width, float height, int tileType, int shaderProgramID){
	programID = shaderProgramID;
	xPos = x;
	yPos = y;
	tileWidth = width;
	tileHeight = height;
	collisionType = CollisionType::None;
	type = tileType;
	int animType = (type / 10) - 1;
	pushAnimation(animType);
}

void Tile::setCanMove(bool value) {
	canMove = value;
}

int Tile::getType() const {
	return type;
}

void Tile::resetInteractions() {
	for (auto & it : interactions)delete it;
	interactions.clear();
	// missing memory manaagement
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
	float* texCoords = animations.top()->getTextureCoordinates();

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

void Tile::pushAnimation(int animtype) {
	auto manager = ServiceLocator::getAnimationsManager();
	animations.push(&manager->getAnimatedSprite(animtype));
	animations.top()->addReference();
}

void Tile::popAnimation(int animtype) {
	animations.top()->removeReference();
	animations.pop();
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

void Tile::addInteraction(Interaction*inter) {
	interactions.push_back(inter);
}

void Tile::render(){
	if (isActive) {
		sendVertices();
		auto color = animations.top()->getColor();
		ServiceLocator::getShaderManager()->setUniform(1, "color", color.x, color.y, color.z);
		animations.top()->render();
		glBindVertexArray(vao);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
}

void Tile::interact() {
	if (!interactions.empty())std::cout << "Size: " << interactions.size() << std::endl;
	for (auto it = interactions.begin(); interactions.size() > 0 && it != interactions.end(); ++it) {
		
		(*it)->interact();
	}
}

bool Tile::isCategory(int t) const {
	return (type % 10) == t;
}


// pre: the two tiles are adjecent and the current tile is 
//		moved toward the second tile => thus it collides unles 
//		it is inactive 
CollisionType Tile::collide(Tile const& other) const {
	return other.getCollisionType();
}

void Tile::free(){
	animations.top()->removeReference();
	glDeleteBuffers(1, &vbo);
}

