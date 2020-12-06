#include "MinMaxAlphaBetaAlg.h"

bool MinMaxAlphaBetaAlg::isGameFinished() const {
	if (board->isFull()) {						// Check if the board is full
		return true;
	}

	if (DRAW != board->getState(AI_MARKER)) {	// Check if 3 marks are met
		return true;
	}

	return false;
}

MinMaxAlphaBetaAlg::MinMaxAlphaBetaAlg(Board* board) {
	this->board = board;
}

pair<int, Vector2> MinMaxAlphaBetaAlg::alg(char marker, int depth, int alpha, int beta) {
	// Initialize best position
	Vector2 bestPosition(-1, -1);
	int bestScore = (marker == AI_MARKER) ? LOSS : WIN;

	// If we hit a terminal state (leaf node), return the best score and move
	int boardState = board->getState(AI_MARKER);
	if (board->isFull() || DRAW != boardState)
	{
		bestScore = boardState;
		return std::make_pair(bestScore, bestPosition);
	}

	VectorPoints possiblePositions = board->getAllPossiblePositions();

	for (int i = 0; i < possiblePositions.size(); i++) {
		Vector2 currPosition = possiblePositions[i];
		board->setAt(currPosition, marker);

		// Maximizing turn
		if (marker == AI_MARKER) {

			int score = alg(PLAYER_MARKER, depth + 1, alpha, beta).first;

			if (bestScore < score) {
				bestScore = score - depth * 10;
				bestPosition = currPosition;

				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				alpha = max(alpha, bestScore);
				board->setAt(currPosition, EMPTY_MARKER);

				if (beta <= alpha) {
					break;
				}
			}

		}
		else {	// Minimizing turn
		
			int score = alg(AI_MARKER, depth + 1, alpha, beta).first;

			// Get the best scoring move
			if (bestScore > score) {
				bestScore = score + depth * 10;
				bestPosition = currPosition;

				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				beta = min(beta, bestScore);
				board->setAt(currPosition, EMPTY_MARKER);
				if (beta <= alpha) {
					break;
				}
			}
		}

		board->setAt(currPosition, EMPTY_MARKER); // Undo move

	}

	return make_pair(bestScore, bestPosition);
}

void printGameResult(int result) {
	if (WIN == result) {
		cout << "WIN" << endl;
	}
	else if (DRAW == result) {
		cout << "DRAW" << endl;
	}
	else if (LOSS == result) {
		cout << "LOSS" << endl;
	}
}

void MinMaxAlphaBetaAlg::playerStart() {
	cout << "\nPlayer = X | AI-Computer = O" << endl;
	board->print();
	int depth = 0;
	cout << "Next optimal player position: " << "[1,1]" << endl;

	while (!isGameFinished()) {
		int row, col;
		cout << "Choose position: row=[1,2,3], col=[1,2,3]" << endl;
		cout << "input position: ";
		cin >> row >> col;
		cout << endl << endl;
		row--;
		col--;

		if (board->isPositionOccupied(Vector2(row, col))) {
			cout << "The position [" << (row + 1) << ", " << (col + 1) << "] is occupied." << endl;
			continue;
		}
		else {
			board->setAt(Vector2(row, col), PLAYER_MARKER);
			cout << "Player turn." << endl;
			board->print();
		}

		pair<int, Vector2> aiPosition = alg(AI_MARKER, depth, LOSS, WIN);
		cout << "Ai-Computer turn." << endl;
		board->setAt(aiPosition.second, AI_MARKER);
		board->print();

		if (isGameFinished())
			break;

		pair<int, Vector2> playerPosition = alg(PLAYER_MARKER, depth, LOSS, WIN);
		cout << "Next optimal player position: " << "[" << (playerPosition.second.row + 1) << "," << (playerPosition.second.col + 1) << "]" << endl;
	}

	cout << "GAME OVER" << endl;

	int playerState = board->getState(PLAYER_MARKER);

	printGameResult(playerState);
}

void MinMaxAlphaBetaAlg::aiStart() {
	cout << "\nPlayer = X | AI-Computer = O" << endl;
	board->print();
	int depth = 0;

	// Set Ai first move
	board->setAt(Vector2(0, 0), AI_MARKER);
	cout << "Ai-Computer turn." << endl;
	board->print();

	cout << "Next optimal player position: " << "[2,2]" << endl;

	while (!isGameFinished()) {
		int row, col;
		cout << "Choose position: row=[1,2,3], col=[1,2,3]" << endl;
		cout << "input position: ";
		cin >> row >> col;
		cout << endl;
		row--;
		col--;

		if (board->isPositionOccupied(Vector2(row, col))) {
			cout << "The position [" << (row + 1) << ", " << (col + 1) << "] is occupied. Try another one..." << endl;
			continue;
		}
		else {
			board->setAt(Vector2(row, col), PLAYER_MARKER);
			cout << "Player turn." << endl;
			board->print();
		}

		pair<int, Vector2> aiPosition = alg(AI_MARKER, depth, LOSS, WIN);
		board->setAt(aiPosition.second, AI_MARKER);
		cout << "Ai-Computer turn." << endl;
		board->print();

		if (isGameFinished())
			break;

		pair<int, Vector2> playerPosition = alg(PLAYER_MARKER, depth, LOSS, WIN);
		cout << "Next optimal player position: " << "[" << (playerPosition.second.row + 1) << "," << (playerPosition.second.col + 1) << "]" << endl;
	}

	cout << "GAME OVER" << endl << endl;

	int playerState = board->getState(PLAYER_MARKER);

	printGameResult(playerState);
}

void MinMaxAlphaBetaAlg::run() {
	cout << "Tic Toc - MinMaxAlphaBeta Pruning" << endl;
	cout << "Choose who is first." << endl;
	cout << "Choose 0 for AI-Computer or 1 for Player: ";
	int first;
	cin >> first;
	if (first)
		playerStart();
	else
		aiStart();
}