#ifndef TYPE_H
#define TYPE_H

#include <stack>
#include <utility>


struct Type {
	int category;
	int id;
	Type() = default;

	Type(int code) {
		category = code % 10;
		id = code / 10;
	}

	Type(int i, int c) {
		category = c;
		id = i;
	}

};


class TypeStack{

public:

	bool empty() const;

	void push(Type const& t);

	void pop();

	void clear();

	int getCategory() const;

	int getID() const;

	Type const& top() const;

	static const int N_TYPES = 20;


private:

	std::stack<Type> types;

};

#endif 

