#pragma once
#include "Constants.h"
#include <algorithm>
#include <iostream>

class Position
{
private:
	int row;
	int col;

	int getRowIndex(char &row);
	int getColIndex(std::string &col);
	void setCoordinates(std::string &position);
	void copyPosition(const Position &p);

public:
	Position();
	Position(std::string &position);
	Position(const Position &position);
	Position& operator=(const Position &p);

	int getRow() const;
	int getCol() const;

	friend bool operator== (Position &lhs, Position &rhs);
};

