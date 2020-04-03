#include "GameMenu.h"


void GameMenu::init(float windowWidth, float windowHeight) {
	int size = 50;
	std::string text = "BABA IS U";
	gameTitle.init(text, (windowWidth - text.size() * size)  / 2, windowHeight * 0.25, size);
	text = "AAA";
	playTitle.init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25 + size, size);
	text = "INSTRUCTIONS";
	instructionsTitle.init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25 + size * 2, size);
	text = "CREDITS";
	creditsTitle.init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25 + size * 3, size);
	

}


void GameMenu::render() {
	gameTitle.render();
	playTitle.render();
	instructionsTitle.render();
	creditsTitle.render();
}


