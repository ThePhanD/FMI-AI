#include "Board.h"

void Board::fillBoard() {
	for (int i = ZERO; i < TEN; ++i) {
		for (int j = ZERO; j < TEN; ++j)
			board[i][j] = EMPTY_FIELD;
	}
}

void Board::initDefaultBoard(char** &board) {
	board = new char*[TEN];
	for (int i = ZERO; i < TEN; ++i)
		board[i] = new char[TEN];
}

void Board::deleteBoard() {
	for (int i = ZERO; i < TEN; ++i)
		delete[] board[i];

	delete[] board;
}

void Board::copyBoard(char** fromBoard, char** &toBoard) {
	initDefaultBoard(toBoard);
	for (int i = ZERO; i < TEN; ++i) {
		for (int j = ZERO; j < TEN; ++j)
			toBoard[i][j] = fromBoard[i][j];
	}
}

char** Board::hideShips() {
	char** newBoard = new char*[TEN];
	for (int i = ZERO; i < TEN; ++i)
		newBoard[i] = new char[TEN];

	copyBoard(getBoard(), newBoard);

	for (int i = ZERO; i < TEN; ++i) {
		for (int j = ZERO; j < TEN; ++j) {
			if (newBoard[i][j] == SHIP_FIELD) {
				newBoard[i][j] = EMPTY_FIELD;
			}
		}
	}

	return newBoard;
}

bool Board::isPositionCorrect(int &row, int &col) {
	if (row < ZERO || row >= TEN) {
		return false;
	}
	else {
		return col >= ZERO && col < TEN;
	}
}

void Board::printNumbers() const {
	std::cout << std::endl;
	std::cout<< "   ";
	for (int i = 1; i <= TEN; ++i) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

Board::Board() {
	initDefaultBoard(board);
	fillBoard();
}

Board::~Board() {
	deleteBoard();
}

Board::Board(char** board) {
	if (board == nullptr) {
		initDefaultBoard(this->board);
		fillBoard();
	}
	else
		copyBoard(board, this->board);
}

Board::Board(const Board &b) {
	copyBoard(b.getBoard(), this->board);
}

Board& Board::operator=(const Board &b) {
	if (this != &b) {
		deleteBoard();
		copyBoard(b.getBoard(), this->board);
	}

	return *this;
}

char Board::getAtPosition(int row, int col) {
	if (isPositionCorrect(row, col)) {
		return board[row][col];
	}

	return INCORRECT_FIELD;
}

void Board::setAtPosition(int row, int col, char symbol) {
	if (isPositionCorrect(row, col)) {
		board[row][col] = symbol;
	}
}

char** Board::getBoard() const {
	return board;
}

char** Board::getHiddenBoard() {
	return hideShips();
}

void Board::printUncoverMap() {
	if (board == nullptr) {
		copyBoard(Board().getBoard(), this->board);
	}

	printNumbers();

	for (int i = ZERO; i < TEN; ++i) {
		char s = (char)('A' + i);
		std::cout<< s << " ";
		for (int j = ZERO; j < TEN; ++j) {
			std::cout << "|" << board[i][j];
		}
		std::cout << "|\n";
	}
}

void Board::printHiddenMap() const {
	printNumbers();

	for (int i = ZERO; i < TEN; ++i) {
		char s = (char)('A' + i);
		std::cout << s << " ";
		for (int j = ZERO; j < TEN; ++j) {
			if (board[i][j] != '*') {
				std::cout << "|" << board[i][j];
			}
			else {
				std::cout << "|-";
			}
		}
		std::cout << "|\n";
	}
}