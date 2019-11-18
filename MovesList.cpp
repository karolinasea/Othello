#include <vector>

#include "Move.h"
#include "MovesList.h"

void MovesList::addMove(Move* m) {
	list.push_back(*m);
}

void MovesList::delAll() {
	list.clear();
}