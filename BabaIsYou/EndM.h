#ifndef END_M_H
#define END_M_H

#include <memory>

#include "Text.h"


class EndM {

public:

	void init(float windowWidth, float windowHeight);

	void render();

	void move(Direction const& dir);

	int select();


private:

	std::vector<std::unique_ptr<Text>> titles;

	int currentTitle;

};

#endif 

