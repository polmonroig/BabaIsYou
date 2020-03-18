#include <GL/glew.h>
#include <GL/gl.h>
#include "Tile.h"


Tile::Tile(float x, float y, float width, float height, int tileType){
	xPos = x;
	iluminationMultiplier = 1;
	yPos = y;
	tileWidth = width;
	tileHeight = height;
	pushType(tileType);
}


Type const& Tile::getType() const {
	if (types.empty()) {
		std::cout << "ERRROOOR" << std::endl;
	}
	std::cout << types.top().id << std::endl;
	return types.top();
}


void Tile::init() {
	float* vertices = calculateVertices();
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	sendVertices();
	auto shaderM = ServiceLocator::getShaderManager();
	posLocation = shaderM->bindVertexAttribute("position", 3, 5 * sizeof(float), 0);
	texCoordLocation = shaderM->bindVertexAttribute( "texCoord", 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

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
	sendVertices();
}

void Tile::pushType(int type) {
	types.push(type);
	setAnimation();
	
}

void Tile::setAnimation() {
	int animType = types.getID() - 1;
	auto manager = ServiceLocator::getAnimationsManager();
	animation = manager->getAnimatedSprite(animType);
	animation->addReference();
}

void Tile::setIlum(float value) {
	iluminationMultiplier = value;
}


void Tile::sendVertices() {
	auto vertices = calculateVertices();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), vertices, GL_STATIC_DRAW);
}



void Tile::render(){
	sendVertices();
	auto color = animation->getColor();
	ServiceLocator::getShaderManager()->setUniform( "color", color.x *iluminationMultiplier, color.y * iluminationMultiplier, color.z * iluminationMultiplier);
	animation->render();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
}


void Tile::free(){
	//animation->removeReference();
	glDeleteBuffers(1, &vbo);
}

