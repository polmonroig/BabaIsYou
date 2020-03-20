#ifndef TYPE_H
#define TYPE_H

#include <stack>
#include <utility>


class Type {

public:

	static const int N_TYPES = 20;

	Type() = default;

	Type(int code);

	Type(int i, int c);


	int category, id;
};


#endif 

