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

	std::pair<bool, bool> move(Cell& dir);
	void moveTo(Cell& other, Direction const& dir);
	std::pair<bool, bool> moveMarked(Cell& dir);

	void render();

	std::vector<Type> getTypes() const;

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

