#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "Text.h"


class GameMenu{

public:

	void init(float windowWidth, float windowHeight);

	void render();

	void free();

private:

	Text instructionsTitle;
	Text creditsTitle;
	Text playTitle;
	Text gameTitle;

};

#endif 

