#include "Instructions.h"


void Instructions::init(float windowWidth, float windowHeight) {
	int size = 30;
	int maxTextSize = 12;
	Text::setBackgroundPosX((windowWidth - maxTextSize * size) / 2);
	Text::setBackgroundWidth(maxTextSize * size);
	std::string text = "INSTRUCTIONS";
	titles.push_back(std::make_unique<Text>());
	titles[0]->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.15, size);

	text = "ARROWS TO MOVE";
	titles.push_back(std::make_unique<Text>());
	titles[1]->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.15 + size * 4, size);


	text = "R TO RESET";
	titles.push_back(std::make_unique<Text>());
	titles[2]->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.15 + size * 6, size);


	text = "ESC TO CLOSE";
	titles.push_back(std::make_unique<Text>());
	titles[3]->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.15 + size * 8, size);

	text = "GO TO MENU";
	titles.push_back(std::make_unique<Text>());
	titles[4]->init(text, (windowWidth - text.size() * size) / 2, windowHeight * 0.15 + size * 12, size);

	currentTitle = 1;
	titles[currentTitle]->setSelected(true);
}

int Instructions::select() {
	return currentTitle;
}

void Instructions::move(Direction const& dir) {
	titles[currentTitle]->setSelected(false);
	auto direction = dir.getDir().second;
	currentTitle += direction;
	if (currentTitle < 1)currentTitle = 1;
	else if (currentTitle >= titles.size()) currentTitle = titles.size() - 1;
	titles[currentTitle]->setSelected(true);
}


void Instructions::render() {
	for (auto& title : titles)title->render();
}

