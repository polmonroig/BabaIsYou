#include "Text.h"


float Text::backgroundWidth;
float Text::backgroundPosX;


void Text::init(std::string const& text, int posX, int posY, int size) {
	selected = false;
	auto shader = ServiceLocator::getShaderManager();
	shader->use(ShaderManager::TEXT_PROGRAM);
	xPos = posX;
	yPos = posY;
	this->size = size;
	auto animManager = ServiceLocator::getAnimationsManager(); 
	vaos.reserve(text.size());
	vbos.reserve(text.size()); 
	int animPos = 0;
	for (int i = 0; i < text.size(); ++i) {
		int letterNumber = int(text[i]) - 65;
		if (text[i] != ' ') {
			auto a = animManager->getAnimatedLetter(letterNumber);
			a->addReference();
			textAnimation.push_back(a);
			vaos.push_back(i);
			vbos.push_back(i);
			glGenVertexArrays(1, &vaos[animPos]);
			glGenBuffers(1, &vbos[animPos]);
			sendVertices(i, animPos);
			auto shaderM = ServiceLocator::getShaderManager();
			posLocation = shaderM->bindVertexAttribute("position", 3, 5 * sizeof(float), 0);
			texCoordLocation = shaderM->bindVertexAttribute("texCoord", 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			animPos++;
		}
	}
	shader->use(ShaderManager::BACKGROUND_PROGRAM);
	background = Background(backgroundPosX, posY, backgroundWidth, size);
	background.init();

}

void Text::free() {
	for (int i = 0; i < textAnimation.size(); ++i) {
		textAnimation[i]->removeReference();
		glDeleteBuffers(1, &vbos[i]);
	}
	textAnimation.clear();
	vbos.clear();
	vaos.clear();

}


float* Text::calculateVertices(int i, int animPos) {
	float* texCoords = textAnimation[animPos]->getTextureCoordinates();
	int i_minus_one = i;
	i++;
	float vertices[30] = { xPos + size * i_minus_one, yPos, 0.0,
							texCoords[Sprite::TOP_LEFT_X], texCoords[Sprite::TOP_LEFT_Y], // ok
						 xPos + size *i , yPos, 0.0,
							texCoords[Sprite::TOP_RIGHT_X], texCoords[Sprite::TOP_RIGHT_Y],
						 xPos  + size*i, yPos + size, 0.0,
							texCoords[Sprite::BOTTOM_RIGHT_X], texCoords[Sprite::BOTTOM_RIGHT_Y], // ok
						 xPos + size * i_minus_one, yPos, 0.0,
							texCoords[Sprite::TOP_LEFT_X], texCoords[Sprite::TOP_LEFT_Y], // ok
						 xPos + size*i, yPos + size,  0.0,
							texCoords[Sprite::BOTTOM_RIGHT_X], texCoords[Sprite::BOTTOM_RIGHT_Y], // ok
						 xPos + size* i_minus_one, yPos + size, 0.0,
							texCoords[Sprite::BOTTOM_LEFT_X], texCoords[Sprite::BOTTOM_LEFT_Y] };

	return vertices;
}

void Text::sendVertices(int i, int animPos) {
	auto vertices = calculateVertices(i, animPos);
	glBindVertexArray(vaos[animPos]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[animPos]);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), vertices, GL_STATIC_DRAW);
}


void Text::setBackgroundWidth(float w) {
	backgroundWidth = w;
}

void Text::setBackgroundPosX(float x) {
	backgroundPosX = x;
}

void Text::setSelected(bool value) {
	selected = value;
}


void Text::render() {
	
	auto shader = ServiceLocator::getShaderManager(); 
	if (selected) {
		shader->use(ShaderManager::BACKGROUND_PROGRAM);
		background.render();
	}
	
	
	shader->use(ShaderManager::TEXT_PROGRAM);
	for (int i = 0; i < textAnimation.size(); ++i) {
		auto anim = textAnimation[i];
		auto color = anim->getColor();
		shader->setUniform("color", color.x, color.y, color.z);
		anim->render();
		
		glBindVertexArray(vaos[i]);
		glEnableVertexAttribArray(posLocation);
		glEnableVertexAttribArray(texCoordLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}
}