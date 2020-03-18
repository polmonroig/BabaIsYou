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

std::vector<Type> const& Cell::getTypes() const {
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


void Cell::move(Cell& dir) {
	for (auto& tile : tiles) {
		if (InteractionsTable::find(tile.getType(), YouInteraction::YOU_ID)) {
			for (auto& otherTile : dir.tiles) {
				auto interactions = InteractionsTable::getInteractions(otherTile.getType());
				for (auto const& it : interactions) {
					it->interact(tile, otherTile);
				}
			}
		}
	}
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

