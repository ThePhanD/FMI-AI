#include "PNode.h"

PNode::PNode(PuzzleState state, PNode *parent, Action action) : state(state), parent(parent), action(action), f(0), g(0), h(0) {}

void PNode::deletePNode()
{
	delete parent;
}

PNode::~PNode()
{
	deletePNode();
}

void PNode::copyPNode(PNode const &p)
{
	state = p.state;
	parent = p.parent;
	action = p.action;
	f = p.f;
	g = p.g;
	h = p.h;
}

PNode::PNode(PNode const &p) : state(p.state.getSize()) {
	copyPNode(p);
}

PNode& PNode::operator=(PNode const &p)
{
	if (this != &p)
	{
		deletePNode();
		copyPNode(p);
	}

	return *this;
}

PuzzleState PNode::getState() const {
	return state;
}

PNode* PNode::getParent() const {
	return parent;
}

Action PNode::getAction() const {
	return action;
}

int PNode::getF() const {
	return f;
}

int PNode::getG() const {
	return g;
}

int PNode::getH() const {
	return h;
}

void PNode::setF(int f) {
	this->f = f;
}

void PNode::setG(int g) {
	this->g = g;
}

void PNode::setH(int h) {
	this->h = h;
}

// Get possible Puzzle State with possible actions
std::list<PNode*> PNode::getPossiblePNode()
{
	std::list<PNode*> nodes;
	for (Action &action : state.getPossibleActions())
	{
		PuzzleState copyState = state;
		copyState.move(action);
		PNode* node = new PNode(copyState, this, action);
		node->setG(g + 1);
		nodes.push_back(node);
	}

	return nodes;
}

// Create the path from the begging
std::list<PNode*> PNode::getPathFromRoot()
{
	std::list<PNode*> path;
	PNode *node = this;
	while (node != nullptr)
	{
		path.push_front(node);
		node = node->getParent();
	}

	return path;
}