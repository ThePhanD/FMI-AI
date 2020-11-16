#include "Puzzle.h"

Puzzle::Puzzle(int size, PuzzleState startState, PuzzleState goalState) : size(size), startState(startState), goalState(goalState) {
	actions = new Action[4]{ Action::UP, Action::DOWN, Action::RIGHT, Action::LEFT };
}

int Puzzle::getSize() const
{
	return size;
}

PuzzleState Puzzle::getStartState() const
{
	return startState;
}

PuzzleState Puzzle::getGoalState() const
{
	return goalState;
}

Action* Puzzle::getActions() const
{
	return actions;
}

bool Puzzle::isSolvable() const	// Check if the puzzle can be solve
{
	int length = size * size;
	int countInversion = 0;
	std::vector<int> board = startState.getBoard();

	// Counting of inversions
	for (int i = 0; i < length - 1; ++i)
	{
		for (int j = i + 1; j < length; ++j)
		{

			if (board[i] > board[j] && board[j] != 0 && board[i] != 0)
				countInversion++;
		}
	}

	// Check the board size
	if (size % 2 == 0)
	{
		// Even size board - sum of number of inversions plus the row of the blank
		// square must be odd number to be solvable
		return (startState.getZeroRowPos() + countInversion) % 2 == 1;
	}
	else {
		// Odd size board - number of inversions must be even to be solvable
		return countInversion % 2 == 0;
	}
}

// Check if the given state is the goal state
bool Puzzle::isGoalState(PuzzleState const &state) const
{
	return goalState.isEquals(state);
}