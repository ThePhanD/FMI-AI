#pragma once

#include <algorithm>
#include "Board.h"
#include "Ship.h"

const std::string FIELD_INTERRUPTION = "The chosen field is interrupted!";
const std::string FIELD_ALREADY_DESTROYED = "The chosen field is already destroyed, choose another one!";
const std::string INCORRECT_SHIP_FIELD = "The chosen field isn't correct size for the ship!";
const std::string INCORRECT_COORDINATESS = "The coordinates must be between row A to J and between col 1 to 10!";

const char EMPTY_FIELD = '-';
const char SHIP_FIELD = '*';
const char HIT_SHIP_FIELD = 'X';
const char HIT_EMPTY_FIELD = 'O';

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

