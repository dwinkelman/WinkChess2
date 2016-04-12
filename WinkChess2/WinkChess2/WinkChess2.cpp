// WinkChess2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "masks.h"


int main()
{
	initMasks();
	printMasks(WP_MASK[12]);
	printMasks(WP_MASK[16]);
	printMasks(WP_MASK[15]);
	printMasks(WP_MASK[53]);
	return 0;
}