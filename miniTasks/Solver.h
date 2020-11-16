#pragma once
#include "Puzzle.h"
#include "Solution.h"
#include "IDAStar.h"

class Solver
{
private:

	Puzzle puzzle;
	IDAStar idaStar;

public:

	Solver(Puzzle, IDAStar);
	Solution* solve();
};
