#include "Cell.h"


void Cell::setIlum(float ilum) {
	for (auto& tile : tiles) {
		if(tile->getType().category != AnimationsManager::SPRITE)
		tile->setIlum(ilum);
	}
}


void Cell::changeType(Type const& origin, Type const& pushed) {
	for (auto& tile : tiles) {
		if (tile->getType().id == origin.id)
			tile->changeType(pushed);
	}
}

void Cell::add(std::shared_ptr<Tile> const& t) {
	t->init();
	tiles.insert(tiles.begin(), t);
}

void Cell::moveTo(Cell& other, Direction const& dir) {
	for (auto it = tiles.begin(); it != tiles.end(); ++it) {
		std::shared_ptr<Tile> current = *it;
		if (current->getFlag() == State::Move) {
			current->setFlag(State::Stop);
			
			current->move(dir);
			other.tiles.push_back(current);
			it = tiles.erase(it);
		}
	}
}

bool Cell::selfInteract() {
	bool win = false;
	std::list<std::shared_ptr<Tile>> spawnedTiles;
	for (auto t1 = tiles.begin(); t1 != tiles.end(); ++t1) {
		std::shared_ptr<Tile> tile1 = *t1;
		for (auto t2 = tiles.begin(); t2 != tiles.end(); ++t2) {
			std::shared_ptr<Tile> tile2 = *t2;
			auto interactions = InteractionsTable::getInteractions(tile2->getType());
			for (auto const& interaction : interactions) {
				interaction->interact(*tile1, *tile2);
			}
		}
		if (tile1->getFlag() == State::Win)win = true;
		else if (tile1->getFlag() == State::Move)tile1->setFlag(State::Stop);
		else if (tile1->getFlag() == State::Death) {
			tile1->free();
			t1 = tiles.erase(t1);
		}
		auto spawned = tile1->getSpawned();
		for (auto const& t : spawned) {
			std::shared_ptr<Tile> spawnedTile = std::make_shared<Tile>();
			*spawnedTile = tile1->copy();
			spawnedTile->init();
			spawnedTile->changeType(t);
			spawnedTiles.push_back(spawnedTile);
		}
	}
	tiles.insert(tiles.end(), spawnedTiles.begin(), spawnedTiles.end());
	return win;
}

std::vector<Type> Cell::getTypes() const {
	std::vector<Type> types;
	types.reserve(tiles.size());
	for (auto const& tile : tiles) {
		types.push_back(tile->getType());
	}
	return types;
}



void Cell::setBackground(float posX, float posY, float width, float height) {
	tileBackground = Background(posX, posY, width, height);
	tileBackground.init();
}

std::pair<bool, bool> Cell::moveMarked(Cell& dir) {
	std::pair<bool, bool> canMove{ false, false };
	for (auto it = tiles.begin(); it != tiles.end(); ++it) {
		std::shared_ptr<Tile> tile = *it;
		if (tile->getFlag() == State::Move) {
			tile->setFlag(State::Move);
			canMove.first = true;
			canMove.second = true;
			for (auto& otherTile : dir.tiles) {
				auto interactions = InteractionsTable::getInteractions(otherTile->getType());
				for (auto const& interaction : interactions) {
					interaction->interact(*tile, *otherTile);
				}
				if (otherTile->getFlag() == State::Move)canMove.second = false;
			}
			if (tile->getFlag() == State::Death) {
				canMove.first = false;
				tile->free();
				it = tiles.erase(it);
			}
			else if (tile->getFlag() == State::Stop) {
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
		std::shared_ptr<Tile> tile = *it;
		if (InteractionsTable::find(tile->getType(), YouInteraction::YOU_ID)) {
			tile->setFlag(State::Move);
			canMove.first = true;
			canMove.second = true;
			for (auto& otherTile : dir.tiles) {
				auto interactions = InteractionsTable::getInteractions(otherTile->getType());
				for (auto const& interaction : interactions) {
					interaction->interact(*tile, *otherTile);
				}
				if (otherTile->getFlag() == State::Move)canMove.second = false;
			}
			if (tile->getFlag() == State::Death) {
				canMove.first = false;
				tile->free();
				it = tiles.erase(it);
			}
			else if (tile->getFlag() == State::Stop) {
				canMove.first = false;
			}
		}
	}
	return canMove;
}


bool Cell::hasCategory(int c) const {
	for (auto const& tile : tiles) {
		auto type = tile->getType();
		if (type.category == c)return true;
	}
	return false;
}

void Cell::free() {
	for (auto& tile : tiles) {
		tile->free();
	}
	tiles.clear();
	tileBackground.free();
}

void Cell::render(){
	auto shaderManager = ServiceLocator::getShaderManager();
	shaderManager->use(ShaderManager::BACKGROUND_PROGRAM);
	tileBackground.render();
	shaderManager->use(ShaderManager::TILE_PROGRAM);
	for (auto& tile : tiles)tile->render();
}

