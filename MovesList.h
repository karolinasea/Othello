#ifndef MOVES_LIST_H
#define MOVES_LIST_H

#include <vector> //might change data structure later
#include "Move.h"

class MovesList {
public:
	MovesList();
	void addMove(Move* m);
	void delAll();

private:
	std::vector<Move> list;
	int size; // = number of possible moves

};

#endif