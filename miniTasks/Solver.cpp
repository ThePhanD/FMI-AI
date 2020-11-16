#include "Solver.h"

Solver::Solver(Puzzle puzzle, IDAStar idaStar) : puzzle(puzzle), idaStar(idaStar) {}

Solution* Solver::solve()
{
	if (!puzzle.isSolvable())
		return new Solution(nullptr);

	return idaStar.search(puzzle);
}