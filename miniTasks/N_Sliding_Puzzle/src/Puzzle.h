#pragma once
#include "PuzzleState.h"

class Puzzle
{
private:

	int size;
	PuzzleState startState;
	PuzzleState goalState;
	Action* actions;

public:

	Puzzle(int, PuzzleState, PuzzleState);

	int getSize() const;
	PuzzleState getStartState() const;
	PuzzleState getGoalState() const;
	Action* getActions() const;
	bool isSolvable() const;
	bool isGoalState(PuzzleState const &state) const;
};