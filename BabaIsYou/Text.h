#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <iostream>
#include <vector>

#include "AnimatedSprite.h"
#include "ServiceLocator.h"


class Text{

public:


	void init(std::string const& text, int posX, int posY, int size);

	void render();

	void free();

private:


	void sendVertices(int i, int animPos);
	float* calculateVertices(int i, int animPos);

	std::vector<AnimatedSprite*> textAnimation;
	float xPos, yPos, size;
	std::vector<GLuint>vaos;
	std::vector<GLuint>vbos;

	GLuint posLocation;
	GLuint texCoordLocation;
	
};


#endif 
