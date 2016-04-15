#pragma once

#include "bst.h";
#include <malloc.h>

class MoveTable {
public:
	MoveTable(int bitbuckets, int bitbucketsize) {
		// initialize bitbucket system
		_n_bitbuckets = 1 << bitbuckets;
		_bitbuckets = (BST<long long, void*>*)malloc(sizeof(BST<long long, void*>) * _n_bitbuckets);
		for (int i = 0; i < _n_bitbuckets; i++) {
			_bitbuckets[i] = BST<long long, void*>(bitbucketsize);
		}
	}

	

private:
	BST<long long, void*>* _bitbuckets;
	int _n_bitbuckets;
	int _bitbucketsize;
};