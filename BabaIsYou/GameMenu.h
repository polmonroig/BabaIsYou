#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "Text.h"


class GameMenu{

public:

	void init(float windowWidth, float windowHeight);

	void render();

	void move(Direction const& dir);

	void free();

private:


	std::vector<Text*> titles;

	int currentTitle;

};

#endif 

