#pragma once
#include "WinningState.h"
#include <iostream>

const int WIN = 10000;
const int DRAW = 0;
const int LOSS = -10000;

const char AI_MARKER = 'O';
const char EMPTY_MARKER = '-';
const char PLAYER_MARKER = 'X';

class Board
{
private:
	char board[3][3];
	WinningState winningStates;

public:

	Board();

	VectorPoints getAllPossiblePositions() const;
	bool isPositionOccupied(Vector2 const &position);
	VectorPoints getAllOccupiedPositionsWithMarker(char const &marker) const;
	bool isFull() const;
	bool isBoardWinnigState(VectorPoints occupiedPositions) const;
	char getOppositeMarker(char const &marker) const;
	int getState(char const &marker) const;
	void setAt(Vector2 position, char marker);
	void print() const;

};