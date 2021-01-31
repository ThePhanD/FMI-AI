#include "Position.h"

int Position::getRowIndex(char &row) {
	if ('A' > row || row > 'J') {
		return -1;
	}

	return row - START_POSITION;
}

int Position::getColIndex(std::string &col) {
	int startPosition = 1;
	int colIndex = atoi(col.c_str()) - startPosition;
	if (0 > colIndex || colIndex > 9) {
		return -1;
	}

	return colIndex;
}

void Position::setCoordinates(std::string &position) {
	std::transform(position.begin(), position.end(), position.begin(), ::toupper);
	std::string realPosition = position;
	char row = realPosition[ROW];
	std::string col = position.substr(COL);
	this->row = getRowIndex(row);
	this->col = getColIndex(col);
}

Position::Position() : row(-1), col(-1) {}

Position::Position(std::string &position) {
	setCoordinates(position);
}

void Position::copyPosition(const Position &p) {
	this->row = p.row;
	this->col = p.col;
}

Position::Position(const Position &position) {
	copyPosition(position);
}

Position& Position::operator=(const Position &p) {
	if (this != &p) {
		copyPosition(p);
	}

	return *this;
}

int Position::getRow() const {
	return row;
}

int Position::getCol() const {
	return col;
}

bool operator== (Position &lhs, Position &rhs) {
	if (lhs.row != rhs.row) {
		return false;
	}
	if (lhs.col != rhs.col) {
		return false;
	}

	return true;
}