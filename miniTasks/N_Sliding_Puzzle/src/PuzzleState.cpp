#include "PuzzleState.h"

void PuzzleState::copyPuzzleState(PuzzleState const& ps)
{
	size = ps.size;
	zeroRowPos = ps.zeroRowPos;
	zeroColPos = ps.zeroColPos;
	board = ps.board;
}

PuzzleState::PuzzleState(int size) : size(size)
{
	for (int i = 1; i < size * size; ++i)
	{
		board.push_back(i);
	}
	board.push_back(0);
	zeroRowPos = size - 1;
	zeroColPos = size - 1;
}

PuzzleState::PuzzleState(int size, std::vector<int> board, int zeroPosition) : size(size)
{
	this->board = board;
	zeroRowPos = zeroPosition / size;
	zeroColPos = zeroPosition % size;
}

PuzzleState::PuzzleState(PuzzleState const& ps)
{
	copyPuzzleState(ps);
}

PuzzleState& PuzzleState::operator=(PuzzleState const &ps)
{
	if (this != &ps)
	{
		copyPuzzleState(ps);
	}

	return *this;
}

std::vector<int> PuzzleState::getBoard() const
{
	return board;
}

int PuzzleState::getZeroRowPos() const
{
	return zeroRowPos;
}

int PuzzleState::getZeroColPos() const
{
	return zeroColPos;
}

int PuzzleState::getSize() const {
	return size;
}

void PuzzleState::moveTo(int row, int col, bool isVertical)
{
	int fromPos = (zeroRowPos * size) + zeroColPos;					//Zero position
	int toPos = ((zeroRowPos + row) * size) + (zeroColPos + col);	//Destination position

	board[fromPos] = board[toPos];	// Zero position = number
	board[toPos] = 0;				// Number position = 0

	if (isVertical) {
		zeroRowPos += row;
	}
	else {
		zeroColPos += col;
	}
}

void PuzzleState::move(Action action)
{
	if (action == Action::UP && zeroRowPos != 0)
	{
		moveTo(-1, 0, true);
	}

	if (action == Action::DOWN && zeroRowPos != size - 1)
	{
		moveTo(1, 0, true);
	}

	if (action == Action::RIGHT && zeroColPos != size - 1)
	{
		moveTo(0, 1, false);
	}

	if (action == Action::LEFT && zeroColPos != 0)
	{
		moveTo(0, -1, false);
	}
}

std::list<Action> PuzzleState::getPossibleActions()
{
	std::list<Action> possibleActions;

	if (zeroRowPos != 0)
		possibleActions.push_back(Action::UP);

	if (zeroRowPos != size - 1)
		possibleActions.push_back(Action::DOWN);
		
	if (zeroColPos != size - 1)
		possibleActions.push_back(Action::RIGHT);
		
	if (zeroColPos != 0)
		possibleActions.push_back(Action::LEFT);
		

	return possibleActions;
}

bool PuzzleState::isEquals(PuzzleState const &ps) const
{
	return size == ps.size
		&& zeroRowPos == ps.zeroRowPos
		&& zeroColPos == ps.zeroColPos
		&& board == ps.board;
}

std::string PuzzleState::getStringFormat() const {
	std::stringstream ss;
	std::copy(board.begin(), board.end(), std::ostream_iterator<int>(ss, ""));
	std::string s = ss.str();

	return s;
}

void PuzzleState::printState() const
{
	std::cout << std::endl;
	for (int i = 0; i < size * size; ++i)
	{
		if (i % size == 0)
			std::cout << std::endl;

		std::cout << board[i] << " ";
	}
}