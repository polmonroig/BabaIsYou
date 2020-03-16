#include "Text.h"


void Text::init(std::string const& text, int posX, int posY, int size) {
	xPos = posX;
	yPos = posY;
	this->size = size;
	auto animManager = ServiceLocator::getAnimationsManager(); 
	vaos = std::vector<GLuint>(text.size());
	vbos = std::vector<GLuint>(text.size());
	for (int i = 0; i < text.size(); ++i) {
		int letterNumber = int(text[i]) - 65;
		std::cout << "Getting letter: " << letterNumber << std::endl;
		auto a = animManager->getAnimatedLetter(letterNumber);
		a->addReference();
		textAnimation.push_back(a);

		glGenVertexArrays(1, &vaos[i]);
		glGenBuffers(1, &vbos[i]);
		sendVertices(i);
		auto shaderM = ServiceLocator::getShaderManager();
		posLocation = shaderM->bindVertexAttribute("position", 3, 5 * sizeof(float), 0);
		texCoordLocation = shaderM->bindVertexAttribute("texCoord", 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	}
}


float* Text::calculateVertices(int i) {
	float* texCoords = textAnimation[i]->getTextureCoordinates();
	i++;
	float vertices[30] = { xPos * i, yPos, 0.0,
							texCoords[Sprite::TOP_LEFT_X], texCoords[Sprite::TOP_LEFT_Y], // ok
						 xPos * i + size, yPos, 0.0,
							texCoords[Sprite::TOP_RIGHT_X], texCoords[Sprite::TOP_RIGHT_Y],
						 xPos * i + size, yPos + size, 0.0,
							texCoords[Sprite::BOTTOM_RIGHT_X], texCoords[Sprite::BOTTOM_RIGHT_Y], // ok
						 xPos * i, yPos, 0.0,
							texCoords[Sprite::TOP_LEFT_X], texCoords[Sprite::TOP_LEFT_Y], // ok
						 xPos* i + size, yPos + size,  0.0,
							texCoords[Sprite::BOTTOM_RIGHT_X], texCoords[Sprite::BOTTOM_RIGHT_Y], // ok
						 xPos * i, yPos + size, 0.0,
							texCoords[Sprite::BOTTOM_LEFT_X], texCoords[Sprite::BOTTOM_LEFT_Y] };

	return vertices;
}

void Text::sendVertices(int i) {
	auto vertices = calculateVertices(i);
	glBindVertexArray(vaos[i]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), vertices, GL_STATIC_DRAW);
}



void Text::render() {
	auto shader = ServiceLocator::getShaderManager(); 
	shader->use(ShaderManager::TILE_PROGRAM);
	for (int i = 0; i < textAnimation.size(); ++i) {
		auto anim = textAnimation[i];
		anim->render();
		auto color = anim->getColor();
		shader->setUniform("color", color.x, color.y, color.z);
		glBindVertexArray(vaos[i]);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}