#pragma once
#include "Solution.h"
#include "Puzzle.h"
#include <queue>
#include <unordered_map>
#include <string>

struct DistanceCompare
{
	bool operator()(const PNode* a, const PNode* b)
	{
		return a->getF() > b->getF();
	}
};

class IDAStar
{
private:

	int size;
	std::priority_queue<PNode *, std::vector<PNode*>, DistanceCompare> expMin;

	int manhattanCalc(PNode *);
	bool isNeighborDuplication(PNode *, PNode *);
	Solution* DFS(PNode*, Puzzle, int);

public:

	IDAStar(int);
	Solution* search(Puzzle);
};
