#include "GameMenu.h"


void GameMenu::init(float windowWidth, float windowHeight) {
	int size = 50;
	int maxTextSize = 12;
	Text::setBackgroundPosX((windowWidth - maxTextSize * size) / 2);
	Text::setBackgroundWidth(maxTextSize * size);
	std::string text = "BABA IS U";
	Text* title = new Text();
	title->init(text, (windowWidth - text.size() * size)  / 2, windowHeight * 0.25, size);
	titles.push_back(title);
	title = new Text();
	text = "AAA";
	title->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25 + size, size);
	titles.push_back(title);
	title = new Text();
	text = "INSTRUCTIONS";
	title->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25 + size * 2, size);
	titles.push_back(title);
	title = new Text();
	text = "CREDITS";
	title->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25 + size * 3, size);
	titles.push_back(title);
	title = new Text();
	currentTitle = 1;
	titles[currentTitle]->setSelected(true);
	
	

}

void GameMenu::move(Direction const& dir) {
	titles[currentTitle]->setSelected(false);
	auto direction = dir.getDir().second;
	currentTitle += direction;
	if (currentTitle < 1)currentTitle = 1;
	else if(currentTitle >= titles.size()) currentTitle = titles.size() - 1;
	titles[currentTitle]->setSelected(true);
}


void GameMenu::render() {
	for (auto& title : titles)title->render();
}




void GameMenu::free() {
	for (int i = 0; i < titles.size(); ++i) {
		titles[i]->free();
		delete titles[i];
	}
}