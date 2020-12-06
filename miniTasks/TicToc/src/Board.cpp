#include "Board.h"

Board::Board() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j)
			board[i][j] = EMPTY_MARKER;
	}
}

VectorPoints Board::getAllPossiblePositions() const {
	VectorPoints availablePositions;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != AI_MARKER && board[i][j] != PLAYER_MARKER) {
				availablePositions.push_back(Vector2(i, j));
			}
		}
	}

	return availablePositions;
}

bool Board::isPositionOccupied(Vector2 const &position) {
	if (board[position.row][position.col] == EMPTY_MARKER)
		return false;

	return true;
}

// Get all board positions occupied by the given marker
VectorPoints Board::getAllOccupiedPositionsWithMarker(char const &marker) const {
	VectorPoints occupiedPositions;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (marker == board[i][j]) {
				occupiedPositions.push_back(Vector2(i, j));
			}
		}
	}

	return occupiedPositions;
}

bool Board::isFull() const {
	VectorPoints possiblePositions = getAllPossiblePositions();

	if (possiblePositions.size() == 0)
		return true;

	return false;
}

// Check if the current state is in the occupied positions
bool isFound(Vector2 currentState, VectorPoints occupiedPositions) {

	for (Vector2 vec2 : occupiedPositions) {
		if (currentState.row == vec2.row && currentState.col == vec2.col) {
			return true;
		}
	}
	return false;
}

// Check if the game has been won
bool Board::isBoardWinnigState(VectorPoints occupiedPositions) const {
	bool gameState;

	for (int i = 0; i < winningStates.getSize(); i++) {
		gameState = true;

		VectorPoints currentState = winningStates.getAt(i);
		for (int j = 0; j < 3; j++) {	// Check if requirement of the three marks is met
			if (!isFound(currentState[j], occupiedPositions)) {
				gameState = false;
				break;
			}
		}

		if (gameState) {
			break;
		}
	}

	return gameState;
}

char  Board::getOppositeMarker(char const &marker) const {
	if (marker == AI_MARKER) {
		return PLAYER_MARKER;
	}

	return AI_MARKER;
}

int Board::getState(char const &marker) const {
	VectorPoints occupiedPositions = getAllOccupiedPositionsWithMarker(marker);
	bool isWon = isBoardWinnigState(occupiedPositions);

	if (isWon) {
		return WIN;
	}

	char oppositeMarker = getOppositeMarker(marker);
	occupiedPositions = getAllOccupiedPositionsWithMarker(oppositeMarker);
	bool isLost = isBoardWinnigState(occupiedPositions);

	if (isLost) {
		return LOSS;
	}

	if (isFull()) {
		return DRAW;
	}

	return DRAW;
}

void Board::setAt(Vector2 position, char marker) {
	board[position.row][position.col] = marker;
}

void Board::print() const {
	cout << endl;
	cout << "-------------" << endl;
	cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |" << endl;
	cout << "-------------" << endl;
	cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |" << endl;
	cout << "-------------" << endl;
	cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |" << endl;
	cout << "-------------" << endl << endl;
}