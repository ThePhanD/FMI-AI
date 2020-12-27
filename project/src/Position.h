#pragma once
#include <string>
#include <algorithm>
#include <iostream>

const std::string INCORRECT_COORDINATES = "The coordinates must be between row A to J, and between col 1 to 10!";
const char START_POSITION = 'A';
const int ROW = 0;
const int COL = 1;

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

