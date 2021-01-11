#pragma once

#include "Board.h"
#include "Ship.h"
#include <algorithm>

class BoardEngine
{
private:
	Board *board;

	void copyBoard(char** toCopyBoard);
	void deleteBoard();
	void setField(const int &atLine, const int &x, const int &y, bool checkRow, const char &symbol);
	void changeShipFieldTo(const int &rowX, const int &colX, const int &rowY, const int &colY, const char &symbol);
	bool modifyShipField(const int &rowX, const int &colX, const int &rowY, const int &colY, Ship *ship, const char &fromSymbol, const char &toSymbol);
	bool isCoordinatesCorrect(const int &row, const int &col);
	bool isPositionCoordinatesCorrect(const int &rowX, const int &colX, const int &rowY, const int &colY, const int &shipSize, const char &symbol);
	bool isChosenFieldEnough(const int &shipSize, const int &fieldSize);
	bool isShipFieldCorrect(const int &atLine, const int &x, const int &y, bool checkRow, const char &symbol);

public:
	BoardEngine();
	~BoardEngine();
	BoardEngine(const Board &b);
	BoardEngine(const BoardEngine &be);
	BoardEngine& operator=(const BoardEngine& be);

	bool setShip(const int &rowX, const int &colX, const int &rowY, const int &colY, Ship *ship);
	bool removeShip(const int &rowX, const int &colX, const int &rowY, const int &colY, Ship *ship);
	bool fireAtPosition(const int &row, const int &col);
	bool placeAtPosition(const int &row, const int &col, const char &symbol);
	void printUncoverBoard() const;
	void printHiddenBoard() const;
	Board* getBoardPtr() const;
	char** getBoardMap() const;
	char** getHiddenBoard();
};

