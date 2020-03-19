#include "Cell.h"


Cell::Cell(int i, int j) {
	index = { i, j };
}

void Cell::setIlum(float ilum) {
	for (auto& tile : tiles) {
		tile.setIlum(ilum);
	}
}


void Cell::add(Tile & t) {
	t.init();
	tiles.insert(tiles.begin(), t);
}

void Cell::moveTo(Cell& other, Direction const& dir) {
	for (auto it = tiles.begin(); it != tiles.end(); ++it) {
		if (it->getFlag() == State::Move) {
			it->setFlag(State::Stop);
			it->move(dir);
			Tile current = *it;
			other.tiles.push_back(current);
			it = tiles.erase(it);
		}
	}
}

bool Cell::selfInteract() {
	bool win = false;
	for (auto t1 = tiles.begin(); t1 != tiles.end(); ++t1) {
		for (auto t2 = tiles.begin(); t2 != tiles.end(); ++t2) {
			if (&(*t1) != &(*t2)) {
				auto interactions = InteractionsTable::getInteractions(t2->getType());
				for (auto const& interaction : interactions) {
					interaction->interact(*t1, *t2);
				}
			}
		}
		if (t1->getFlag() == State::Win)win = true;
		else if (t1->getFlag() == State::Move)t1->setFlag(State::Stop);
		else if (t1->getFlag() == State::Death) {
			t1->free();
			t1 = tiles.erase(t1);
		}
	}
	return win;
}

std::vector<Type> Cell::getTypes() const {
	std::vector<Type> types;
	types.reserve(tiles.size());
	for (auto const& tile : tiles) {
		types.push_back(tile.getType());
	}
	return types;
}

std::pair<int, int>const& Cell::getIndex() const {
	return index;
}


void Cell::setBackground(float posX, float posY, float width, float height) {
	tileBackground = Background(posX, posY, width, height);
	tileBackground.init();
}

std::pair<bool, bool> Cell::moveMarked(Cell& dir) {
	std::pair<bool, bool> canMove{ false, false };
	for (auto it = tiles.begin(); it != tiles.end(); ++it) {
		auto tile = *it;
		if (tile.getFlag() == State::Move) {
			tile.setFlag(State::Move);
			canMove.first = true;
			canMove.second = true;
			for (auto& otherTile : dir.tiles) {
				auto interactions = InteractionsTable::getInteractions(otherTile.getType());
				for (auto const& interaction : interactions) {
					interaction->interact(tile, otherTile);
				}
				if (otherTile.getFlag() == State::Move)canMove.second = false;
			}
			if (tile.getFlag() == State::Death) {
				canMove.first = false;
				it->free();
				it = tiles.erase(it);
			}
			else if (tile.getFlag() == State::Stop) {
				canMove.first = false;
			}
		}
	}
	return canMove;
}

// canMove = {currentTile could move if the next tile can move, nextTile can Move or should move}
std::pair<bool, bool> Cell::move(Cell& dir) {
	std::pair<bool, bool> canMove{false, false};
	for (auto it = tiles.begin(); it != tiles.end(); ++it) {
		if (InteractionsTable::find(it->getType(), YouInteraction::YOU_ID)) {
			it->setFlag(State::Move);
			canMove.first = true;
			canMove.second = true;
			for (auto& otherTile : dir.tiles) {
				auto interactions = InteractionsTable::getInteractions(otherTile.getType());
				for (auto const& interaction : interactions) {
					interaction->interact(*it, otherTile);
				}
				if (otherTile.getFlag() == State::Move)canMove.second = false;
			}
			if (it->getFlag() == State::Death) {
				canMove.first = false;
				it->free();
				it = tiles.erase(it);
			}
			else if (it->getFlag() == State::Stop) {
				canMove.first = false;
			}
		}
	}
	return canMove;
}


bool Cell::hasCategory(int c) const {
	for (auto const& tile : tiles) {
		auto type = tile.getType();
		if (type.category == c)return true;
	}
	return false;
}

void Cell::free() {
	for (auto& tile : tiles)tile.free();
	tileBackground.free();
}

void Cell::render(){
	auto shaderManager = ServiceLocator::getShaderManager();
	shaderManager->use(ShaderManager::BACKGROUND_PROGRAM);
	tileBackground.render();
	shaderManager->use(ShaderManager::TILE_PROGRAM);
	for (auto& tile : tiles)tile.render();
}

