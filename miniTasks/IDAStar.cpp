#include "IDAStar.h"

IDAStar::IDAStar(int size) : size(size) {}

int IDAStar::manhattanCalc(PNode *node)
{
	int distance = 0;
	std::vector<int> board = node->getState().getBoard();

	for (int row = 0; row < size; ++row)
	{
		for (int col = 0; col < size; ++col)
		{
			int value = board[row * size + col];
			if (value != 0)
			{
				int targetRow = (value - 1) / size;
				int targetCol = (value - 1) % size;
				distance += abs(row - targetRow) + abs(col - targetCol);
			}
		}
	}

	return distance;
}

bool IDAStar::isNeighborDuplication(PNode *currentNode, PNode *neightborNode)
{
	if (currentNode->getParent() == nullptr)
		return false;

	PNode *parentNode = currentNode->getParent();
	
	return parentNode->getState().isEquals(neightborNode->getState());
}

Solution* IDAStar::DFS(PNode *selectNode, Puzzle puzzle, int currentCostBound)
{
	expMin.push(selectNode);
	while (!expMin.empty()) {
		PNode *select = expMin.top();
		expMin.pop();

		if (puzzle.isGoalState(select->getState()))
			return new Solution(select);

		std::list<PNode*> expansion = select->getPossiblePNode();
		for (PNode *node : expansion)
		{
			if (!isNeighborDuplication(select, node))	// The neighbor is not duplication
			{
				node->setH(manhattanCalc(node));
				node->setF(node->getG() + node->getH());
				int value = node->getF();
				if (value <= currentCostBound)
				{
					expMin.push(node);
				}
			}
		}
	}

	return new Solution(nullptr);
}


Solution* IDAStar::search(Puzzle puzzle)
{
	PNode *startNode = new PNode(puzzle.getStartState(), nullptr, Action::NUL);
	int nextCostBound = manhattanCalc(startNode);	// Calculate Manhattan distance of the board
	Solution *result = new Solution(nullptr);

	// Iterative Deepening A* search algoirthm
	while (result->getPNode() == nullptr)
	{
		result = DFS(startNode, puzzle, nextCostBound);
		if (result->getPNode() != nullptr && puzzle.isGoalState(result->getPNode()->getState()))
			return result;

		nextCostBound += 2; // Increase the bound if there is nothing
	}

	return new Solution(nullptr);
}
