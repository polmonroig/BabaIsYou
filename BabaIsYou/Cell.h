#ifndef CELL_H 
#define CELL_H

#include "Tile.h"
#include "Background.h"
#include "YouInteraction.h"
#include "PushInteraction.h"
#include "DefeatInteraction.h"
#include "WinInteraction.h"
#include "FearInteraction.h"
#include "StopInteraction.h"
#include "InteractionsTable.h"

class Cell{

public:

	Cell() = default;

	Cell(int i, int j);

	void add(Tile& t);

	void move(Cell& dir);

	void pushType(Type const& old, Type const& newT) {

	}

	void render();

	std::vector< Type>const& getTypes() const;

	bool hasCategory(int c) const;


	void setIlum(float ilum);

	void setBackground(float posX, float posY, float width, float height);

	std::pair<int, int>const& getIndex() const;

	void free();

private:

	std::pair<int, int> index;

	std::list<Tile> tiles;
	Background tileBackground;

	bool interacted;

};



#endif

