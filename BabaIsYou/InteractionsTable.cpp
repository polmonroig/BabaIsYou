#include "InteractionsTable.h"

InteractionsTable::InteractionsMatrix InteractionsTable::table;

void InteractionsTable::init() {
	table = InteractionsMatrix(Type::N_TYPES,InteractionsVector(N_INTERACTIONS));
	for (int i = 0; i < Type::N_TYPES; ++i) {
		for (int j = 0; j < N_INTERACTIONS; ++j) {
			if (table[i][j] == nullptr) {
				std::shared_ptr<NullInteraction> pointer = std::make_shared<NullInteraction>();
				table[i][j] = pointer;
			}
				
		}
	}
}

InteractionsTable::InteractionsVector const& InteractionsTable::getInteractions(Type const& t) {
	return table[t.id - 1];
}

void InteractionsTable::insert(Type const& t, std::shared_ptr<Interaction> const& it) {
	if (!find(t, it->ID())) {
		table[t.id - 1][it->ID()] = it;
	}
		
}



bool InteractionsTable::find(Type const& t, int id) {
	return table[t.id - 1][id]->ID() != NullInteraction::NULL_ID;
}


void InteractionsTable::free() {
	
	for (int i = 0; i < AnimationsManager::N_SPRITES; ++i) {
		for (int j = 0; j < N_INTERACTIONS; ++j) {
			std::shared_ptr<NullInteraction> pointer = std::make_shared<NullInteraction>();
			table[i][j] = pointer;
		}
	}
}