#include "GameMenu.h"


void GameMenu::init(float windowWidth, float windowHeight) {
	int size = 50;
	int maxTextSize = 12;
	Text::setBackgroundPosX((windowWidth - maxTextSize * size) / 2);
	Text::setBackgroundWidth(maxTextSize * size);
	std::string text = "BABA IS U";
	titles.push_back(std::make_unique<Text>());
	titles[0]->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25, size);

	text = "AAA";
	titles.push_back(std::make_unique<Text>());
	titles[1]->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25 + size, size);
	

	text = "INSTRUCTIONS";
	titles.push_back(std::make_unique<Text>());
	titles[2]->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25 + size * 2, size);


	text = "CREDITS";
	titles.push_back(std::make_unique<Text>());
	titles[3]->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.25 + size * 3, size);
	
	currentTitle = 1;
	titles[currentTitle]->setSelected(true);
	
	

}

bool GameMenu::select() {
	if (currentTitle == 1)return true;

	return false;
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

