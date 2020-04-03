#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <iostream>
#include <vector>

#include "AnimatedSprite.h"
#include "Background.h"
#include "ServiceLocator.h"


class Text{

public:


	void init(std::string const& text, int posX, int posY, int size);

	void render();

	void setSelected(bool value);

	void free();

	static void setBackgroundWidth(float w);

	static void setBackgroundPosX(float x);

private:


	static float backgroundPosX;
	static float backgroundWidth;


	bool selected;

	void sendVertices(int i, int animPos);
	float* calculateVertices(int i, int animPos);

	std::vector<AnimatedSprite*> textAnimation;
	float xPos, yPos, size;
	std::vector<GLuint>vaos;
	std::vector<GLuint>vbos;

	GLuint posLocation;
	GLuint texCoordLocation;

	Background background;
	
};


#endif 
