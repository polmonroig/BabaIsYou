#include "TypeStack.h"

void TypeStack::push(Type const& t) {
	types.push(t);
}

Type const& TypeStack::top() const {
	return types.top();
}

void TypeStack::pop() {
	types.pop();
}

int TypeStack::getCategory() const {
	return types.top().category;
}

int TypeStack::getID() const {
	return types.top().id;
}

bool TypeStack::empty() const {
	return types.empty();
}