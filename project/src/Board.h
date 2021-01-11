#pragma once

#include "Constants.h"
#include <iostream>

class Board
{
private:
	char** board;

	void fillBoard();
	void initDefaultBoard(char** &board);
	void copyBoard(char** fromBoard, char** &toBoard);
	void deleteBoard();
	char** hideShips();
	bool isPositionCorrect(int &row, int &col);
	void printNumbers()  const;

public:
	Board();
	~Board();
	Board(char** board);
	Board(const Board &b);
	Board& operator=(const Board &b);

	char getAtPosition(int row, int col);
	void setAtPosition(int row, int col, char symbol);
	char** getBoard() const;
	char** getHiddenBoard();
	void printUncoverMap() ;
	void printHiddenMap() const;
};

