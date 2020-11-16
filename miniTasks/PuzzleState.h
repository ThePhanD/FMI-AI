#pragma once
#include "Action.h"
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

class PuzzleState
{
private:

	int size;
	int zeroRowPos;
	int zeroColPos;
	std::vector<int> board;

	void copyPuzzleState(PuzzleState const&);
	void moveTo(int, int, bool);

public:

	PuzzleState(int);
	PuzzleState(int, std::vector<int>, int);
	PuzzleState(PuzzleState const&);
	PuzzleState& operator=(PuzzleState const&);

	std::vector<int> getBoard() const;
	int getZeroRowPos() const;
	int getZeroColPos() const;
	int getSize() const;

	void move(Action);
	std::list<Action> getPossibleActions();
	bool isEquals(PuzzleState const&) const;
	std::string getStringFormat() const;

	void printState() const;
};

