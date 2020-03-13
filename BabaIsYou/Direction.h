#ifndef DIRECTION_H 
#define DIRECTION_H 

#include <utility>

// represents the direction of a movement 

enum class DirectionType { LEFT, RIGHT, UP, DOWN };

class Direction{

public:

	Direction() = default;

	Direction(DirectionType const& type);

	std::pair<int, int> getDir() const;

	bool isType(DirectionType const& t) const;

	static std::pair<int, int> move(std::pair<int, int> pos, Direction const& dir);

private:

	DirectionType type;
	std::pair<int, int> dir;

};


#endif 
