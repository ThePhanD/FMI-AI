#include "Solution.h"

void Solution::initPath(PNode *node)
{
	if (node != nullptr)
		path = node->getPathFromRoot();
}

Solution::Solution(PNode *node) : node(node) 
{
	initPath(node);
}

PNode* Solution::getPNode() const {
	return node;
}

std::list<PNode*> Solution::getPath()
{
	return path;
}

std::string getAction(Action action)
{
	switch (action)
	{
	case Action::UP: return "UP";
	case Action::DOWN: return "DOWN";
	case Action::RIGHT: return "RIGHT";
	case Action::LEFT: return "LEFT";
	default: return "NULL";
	}
}

void Solution::printResult() const
{
	std::string result;

	if (!path.empty())
	{
		int size = path.size() - 1;
		result.append("Resolved in " + std::to_string(size));
		result.append(" moves.\n");
		result.append("\nSolution:\n");

		for (PNode *node : path)
		{
			result.append(getAction(node->getAction()) + "\n");
		}
		result.erase(32, 5);
	}
	else {
		result.append("No solution found\n");
	}

	std::cout << result << std::endl;
}