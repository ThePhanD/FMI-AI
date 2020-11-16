#pragma once
#include "Solver.h"
#include <iostream>

class NPuzzleApp
{
private:

	int size;
	int zeroPosition;
	std::vector<int> board;

	void initSize();
	void initZero();
	void insertBoard();
	Puzzle initPuzzle();
	IDAStar initAlg();

	void init3Puzzle();
	void init4Puzzle();
	void init5Puzzle();

public:

	NPuzzleApp();
	void init();
};


