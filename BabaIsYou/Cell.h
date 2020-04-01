#ifndef CELL_H 
#define CELL_H

#include "Tile.h"
#include "Background.h"
#include "YouInteraction.h"
#include "PushInteraction.h"
#include "DefeatInteraction.h"
#include "WinInteraction.h"
#include "MakeInteraction.h"
#include "StopInteraction.h"
#include "InteractionsTable.h"
#include "SinkInteraction.h"

class Cell{

public:

	void add(Tile* t);
	void changeType(Type const& origin, Type const& pushed);
	bool selfInteract();
	std::pair<bool, bool> move(Cell& dir);
	void moveTo(Cell& other, Direction const& dir);
	std::pair<bool, bool> moveMarked(Cell& dir);

	void render();

	std::vector<Type> getTypes() const;

	bool hasCategory(int c) const;


	void setIlum(float ilum);

	void setBackground(float posX, float posY, float width, float height);

	void free();

private:


	std::list<Tile*> tiles;
	Background tileBackground;

	bool interacted;

};



#endif

