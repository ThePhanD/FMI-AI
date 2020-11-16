#pragma once
#include "PNode.h"
#include <string>
#include <iostream>

class Solution
{
private:

	PNode *node;
	std::list<PNode*> path;

	void initPath(PNode *node);

public:

	Solution(PNode *node);

	PNode* getPNode() const;
	std::list<PNode*> getPath();

	void printResult() const;
};

