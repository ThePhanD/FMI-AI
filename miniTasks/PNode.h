#pragma once
#include "PuzzleState.h"

class PNode
{
private:

	PuzzleState state;
	PNode *parent;
	Action action;
	int f, g, h;

	void copyPNode(PNode const&);
	void deletePNode();

public:

	PNode(PuzzleState, PNode *, Action);
	~PNode();
	PNode(PNode const&);
	PNode& operator=(PNode const&);

	PuzzleState getState() const;
	PNode* getParent() const;
	Action getAction() const;
	int getF() const;
	int getG() const;
	int getH() const;
	void setF(int);
	void setG(int);
	void setH(int);

	std::list<PNode*> getPossiblePNode();
	std::list<PNode*> getPathFromRoot();

};