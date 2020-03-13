#include "Direction.h"


Direction::Direction(DirectionType const& type) {
	switch (type)
	{
	case DirectionType::UP:
		dir = std::make_pair<int, int>(0, -1);
		break;
	case DirectionType::DOWN:
		dir = std::make_pair<int, int>(0, 1);
		break;
	case DirectionType::LEFT:
		dir = std::make_pair<int, int>(-1, 0);
		break;
	case DirectionType::RIGHT:
		dir = std::make_pair<int, int>(1, 0);
		break;
	}
	this->type = type;
}

bool Direction::isType(DirectionType const& t) const {
	return type == t;
}

std::pair<int, int> Direction::getDir() const {
	return dir;
}


std::pair<int, int> Direction::move(std::pair<int, int> pos, Direction const& dir) {
	pos.first += dir.dir.first;
	pos.second += dir.dir.second;
	return pos;
}