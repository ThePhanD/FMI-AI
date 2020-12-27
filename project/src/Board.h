#pragma once
#include <string>
#include <iostream>

const std::string INCORRECT_BOARD = "The board can't be null!";
const std::string INIT_DEFAULT_BOARD = "The board couldn't be copied.\nA default board was created.";
const char INCORRECT_FIELD = '#';

const int ZERO = 0;
const int TEN = 10;

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

