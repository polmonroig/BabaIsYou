#include "Type.h"

Type::Type(int code) {
	category = code % 10;
	id = code / 10;
}

Type::Type(int i, int c) {
	category = c;
	id = i;
}
