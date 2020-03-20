#ifndef INTERACTIONS_TABLE
#define INTERACTIONS_TABLE

#include <vector>

#include "Type.h"
#include "NullInteraction.h"


/**
       Interactions table represents a dictionary for 
	   interactions with a perfect "hash function" where 
	   each interaction saves its position 
*/
class InteractionsTable{


public:

	typedef std::vector<Interaction*> InteractionsVector;
	typedef std::vector<InteractionsVector> InteractionsMatrix;

	static void init();

	static void free();

	static void insert(Type const& t, Interaction* it);

	static bool find(Type const& t, int goal);

	static InteractionsVector const& getInteractions(Type const& t) ;



private:

	static const int N_INTERACTIONS = 6;

	

	static InteractionsMatrix table;

};



#endif 
