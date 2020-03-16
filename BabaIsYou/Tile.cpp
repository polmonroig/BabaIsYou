#include <GL/glew.h>
#include <GL/gl.h>
#include "Tile.h"

Tile::Tile() {
	isActive = false;
	types = std::stack<int>();
}

void Tile::setBorders(int borderLeft, int borderRight, int borderTop, int borderBottom) {
	bLeft = borderLeft;
	bRight = borderRight;
	bTop = borderTop;
	bBottom = borderBottom;
}

void Tile::insideBorders() {
	if (xPos < bLeft)xPos = bRight - tileWidth/2;
	else if (xPos >= bRight)xPos = bLeft;
	if (yPos < bTop)yPos = bBottom - tileHeight/2;
	else if (yPos >= bBottom)yPos = bTop ;
}

Tile::Tile(float x, float y, float width, float height, int tileType){
	xPos = x;
	yPos = y;
	tileWidth = width;
	tileHeight = height;
	collisionType = CollisionType::None;
	types = std::stack<int>();
	pushType(tileType);
}


int Tile::getType() const {
	if (types.empty()) {
		return 9;
	}
	else {
		return types.top();
	}
	
}

void Tile::resetInteractions() {
	for (auto & it : interactions)delete it;
	interactions.clear();
	collisionType = CollisionType::None;
	resetTypes();
}

void Tile::init() {
	isActive = true;
	float* vertices = calculateVertices();
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	sendVertices();
	auto shaderM = ServiceLocator::getShaderManager();
	posLocation = shaderM->bindVertexAttribute("position", 3, 5 * sizeof(float), 0);
	texCoordLocation = shaderM->bindVertexAttribute( "texCoord", 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

}

void Tile::setCollisionType(CollisionType const& t) {
	collisionType = t;
}

CollisionType Tile::getCollisionType() const {
	return collisionType;
}


float* Tile::calculateVertices() {
	float* texCoords = animation->getTextureCoordinates();

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
	insideBorders();
	sendVertices();
}

void Tile::pushType(int type) {
	types.push(type);
	setAnimation();
	
}

void Tile::resetTypes() {
	animation->removeReference();
	while (types.size() > 1)types.pop();
	setAnimation();
}

void Tile::setAnimation() {
	int animType = (types.top() / 10) - 1;
	auto manager = ServiceLocator::getAnimationsManager();
	animation = &manager->getAnimatedSprite(animType);
	animation->addReference();
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
		auto color = animation->getColor();
		ServiceLocator::getShaderManager()->setUniform( "color", color.x, color.y, color.z);
		animation->render();
		glBindVertexArray(vao);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
}

void Tile::interact() {
	for (auto it = interactions.begin(); interactions.size() > 0 && it != interactions.end(); ++it) {
		(*it)->interact();
	}
}

bool Tile::isCategory(int t) const {
	if (types.empty())return false;
	return (types.top() % 10) == t;
}


// pre: the two tiles are adjecent and the current tile is 
//		moved toward the second tile => thus it collides unles 
//		it is inactive 
CollisionType Tile::collide(Tile const& other) const {
	if (collisionType == CollisionType::Win)return collisionType;
	return other.getCollisionType();
}

void Tile::free(){
	animation->removeReference();
	glDeleteBuffers(1, &vbo);
}

