// WinkChess2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "masks.h"


int main()
{
	initMasks();
	initMoves();
	std::vector<short> movelist = H_MOVES_E[12].at(0);
	for (int i = 0; i < movelist.size(); i++) {
		std::cout << movelist[i] << '\n';
	}
	return 0;
}