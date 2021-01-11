#include "BoardEngine.h"

void BoardEngine::copyBoard(char** toCopyBoard) {
	board = new Board(toCopyBoard);
}

void BoardEngine::deleteBoard() {
	delete board;
}

void BoardEngine::setField(const int &atLine, const int &x, const int &y, bool checkRow, const char &symbol) {
	int from = std::min(x, y);
	int to = std::max(x, y);

	for (int i = from; i <= to; ++i) {
		if (checkRow) {
			board->setAtPosition(atLine, i, symbol);
		}
		else {
			board->setAtPosition(i, atLine, symbol);
		}
	}
}

void BoardEngine::changeShipFieldTo(const int &rowX, const int &colX, const int &rowY, const int &colY, const char &symbol) {
	if (rowX == rowY) {
		setField(rowX, colX, colY, true, symbol);
	}
	else if (colX == colY) {
		setField(colX, rowX, rowY, false, symbol);
	}
}

bool BoardEngine::modifyShipField(const int &rowX, const int &colX, const int &rowY, const int &colY, Ship *ship, const char &fromSymbol, const char &toSymbol) {
	char** oldBoard = board->getBoard();
	int shipSize = ship->getSize() - 1;

	if (isPositionCoordinatesCorrect(rowX, colX, rowY, colY, shipSize, fromSymbol)) {
		changeShipFieldTo(rowX, colX, rowY, colY, toSymbol);
	}
	else {
		copyBoard(oldBoard);
		return false;
	}

	return true;
}

bool BoardEngine::isCoordinatesCorrect(const int &row, const int &col) {
	if (row >= 0 && row <= 9) {
		if (col >= 0 && col <= 9) {
			return true;
		}
	}
	std::cerr << INCORRECT_COORDINATES << std::endl;
	return false;
}

bool BoardEngine::isPositionCoordinatesCorrect(const int &rowX, const int &colX, const int &rowY, const int &colY, const int &shipSize, const char &symbol) {
	bool flagX = isCoordinatesCorrect(rowX, colX);
	bool flagY = isCoordinatesCorrect(rowY, colY);

	if (!flagX || !flagY) {
		std::cerr << INCORRECT_COORDINATES << std::endl;
		return false;
	}

	if (rowX == rowY) {
		int fieldSize = std::abs(colX - colY);
		if (isChosenFieldEnough(fieldSize, shipSize)) {
			return isShipFieldCorrect(rowX, colX, colY, true, symbol);
		}
	}
	else if (colX == colY) {
		int fieldSize = std::abs(rowX - rowY);
		if (isChosenFieldEnough(fieldSize, shipSize)) {
			return isShipFieldCorrect(colX, rowX, rowY, false, symbol);
		}
	}

	std::cerr << FIELD_INTERRUPTION << std::endl;
	return false;
}

bool BoardEngine::isChosenFieldEnough(const int &shipSize, const int &fieldSize) {
	if (fieldSize == shipSize) {
		return true;
	}

	std::cerr << INCORRECT_SHIP_FIELD << std::endl;
	return false;
}

bool BoardEngine::isShipFieldCorrect(const int &atLine, const int &x, const int &y, bool checkRow, const char &symbol) {
	int from = std::min(x, y);
	int to = std::max(x, y);
	for (int i = from; i <= to; ++i) {
		if (checkRow) {
			if (board->getAtPosition(atLine, i) != symbol) {
				std::cerr << FIELD_INTERRUPTION << std::endl;
				return false;
			}
		}
		else {
			if (board->getAtPosition(i, atLine) != symbol) {
				std::cerr << FIELD_INTERRUPTION << std::endl;
				return false;
			}
		}
	}
	return true;
}

BoardEngine::BoardEngine() {
	board = new Board();
}

BoardEngine::~BoardEngine() {
	deleteBoard();
}

BoardEngine::BoardEngine(const Board &b) {
	board = new Board(b);
}

BoardEngine::BoardEngine(const BoardEngine &be) {
	copyBoard(be.getBoardMap());
}

BoardEngine& BoardEngine::operator=(const BoardEngine& be) {
	if (this != &be) {
		deleteBoard();
		copyBoard(be.getBoardMap());
	}

	return *this;
}


bool BoardEngine::setShip(const int &rowX, const int &colX, const int &rowY, const int &colY, Ship *ship) {
	return modifyShipField(rowX, colX, rowY, colY, ship, EMPTY_FIELD, SHIP_FIELD);
}

bool BoardEngine::removeShip(const int &rowX, const int &colX, const int &rowY, const int &colY, Ship *ship) {
	return modifyShipField(rowX, colX, rowY, colY, ship, SHIP_FIELD, EMPTY_FIELD);
}

bool BoardEngine::fireAtPosition(const int &row, const int &col) {
	char** oldBoard = board->getBoard();

	if (isCoordinatesCorrect(row, col)) {
		char fieldAt = board->getAtPosition(row, col);

		if (fieldAt == SHIP_FIELD) {
			setField(row, col, col, true, HIT_SHIP_FIELD);
			return true;
		}
		else if (fieldAt == EMPTY_FIELD) {
			setField(row, col, col, true, HIT_EMPTY_FIELD);
			return true;
		}
		else {
			std::cerr << FIELD_ALREADY_DESTROYED << std::endl;
			copyBoard(oldBoard);
			return false;
		}
	}
	return false;
}

bool BoardEngine::placeAtPosition(const int &row, const int &col, const char &symbol) {
	char** oldBoard = board->getBoard();
	
	if (isCoordinatesCorrect(row, col)) {
		setField(row, col, col, true, symbol);
	}
	else {
		copyBoard(oldBoard);
		return false;
	}
	return true;
}

void BoardEngine::printUncoverBoard() const {
	board->printUncoverMap();
}

void BoardEngine::printHiddenBoard() const {
	board->printHiddenMap();
}

Board* BoardEngine::getBoardPtr() const {
	return board;
}

char** BoardEngine::getBoardMap() const {
	return board->getBoard();
}

char** BoardEngine::getHiddenBoard() {
	return board->getHiddenBoard();
}