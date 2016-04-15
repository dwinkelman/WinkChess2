// WinkChess2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "masks.h"
#include "bst.h"

int main()
{
	BST<long long, double> tree(10);
	tree.Add(0, -2);
	tree.Add(5, 7);
	tree.Add(-4, 6);
	tree.Add(-2, 6);
	tree.Add(-7, 6);

	BSTStatus _status;
	double x = tree.Get(0, &_status);
	double y = tree.Get(6, &_status);

	tree.Set(-2, 1000, &_status);
	tree.Set(-9, 3.4, &_status);

	BSTNode<long long, double>* min = tree.Max(&_status);

	return 0;
	/*initMasks();
	initMoves();
	std::vector<short> movelist = H_MOVES_E[12].at(0);
	for (int i = 0; i < movelist.size(); i++) {
		std::cout << movelist[i] << '\n';
	}
	return 0;*/
}