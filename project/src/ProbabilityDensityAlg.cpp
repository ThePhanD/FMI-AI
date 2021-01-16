#include "ProbabilityDensityAlg.h"

bool ProbabilityDensityAlg::isHorizontal(int row, int col, int shipSize) {
	if ((TEN - col) < shipSize)
		return false;

	char **board = boardHub->getBoardEngine()->getHiddenBoard();
	for (int i = 0; i < shipSize; ++i, col++) {
		if (board[row][col] != EMPTY_FIELD)
			return false;
	}
	return true;
}

bool ProbabilityDensityAlg::isVertical(int row, int col, int shipSize) {
	if ((TEN - row) < shipSize)
		return false;

	char **board = boardHub->getBoardEngine()->getHiddenBoard();
	for (int i = 0; i < shipSize; ++i, row++) {
		if (board[row][col] != EMPTY_FIELD)
			return false;
	}
	return true;
}

std::vector<std::vector<int>> ProbabilityDensityAlg::calculateDensity() {
	std::vector<std::vector<int>> calcBoard;
	initBoard(calcBoard);
	std::vector<ShipPosition> ships = boardHub->getShips();
	for (ShipPosition sp : ships) {
		Ship *ship = sp.getShip();
		int shipSize = ship->getSize();
		for (int i = 0; i < TEN; ++i) {
			for (int j = 0; j < TEN; ++j) {
				if (isHorizontal(i, j, shipSize)) {
					int k = j;
					for (int l = 0; l < shipSize; l++) {
						calcBoard[i][k] += ship->getSize(); // LOW_PROBABILITY;
						k++;
					}
				}

				if (isVertical(i, j, shipSize)) {
					int k = i;
					for (int l = 0; l < shipSize; l++) {
						calcBoard[k][j] += LOW_PROBABILITY;
						k++;
					}
				}
			}
		}
	}

	char **board = boardHub->getBoardEngine()->getHiddenBoard();
	for (int i = 0; i < TEN; ++i) {
		for (int j = 0; j < TEN; ++j) {
			if (board[i][j] != EMPTY_FIELD) {
				calcBoard[i][j] = 0;
			}
		}
	}

	return calcBoard;
}

void ProbabilityDensityAlg::initBoard(std::vector<std::vector<int>> &board) {
	board.clear();
	for (int i = 0; i < TEN; ++i) {
		std::vector<int> row;
		for (int j = 0; j < TEN; ++j)
			row.push_back(0);

		board.push_back(row);
	}
}

ProbabilityDensityAlg::ProbabilityDensityAlg(BoardHub *boardHub) {
	this->destroyMode = false;
	this->hitFlag = false;
	this->shipNumber = 0;
	this->hitHorizontal = 0;
	this->hitVertical = 0;
	this->boardHub = boardHub;
	this->shipNumber = boardHub->getShips().size();
}

void ProbabilityDensityAlg::setMaxShipSize() {
	int max = 0;
	for (ShipPosition sp : boardHub->getShips()) {
		int shipSize = sp.getShip()->getSize();
		if (max < shipSize)
			max = shipSize;
	}

	maxShipSize = max;
}

void ProbabilityDensityAlg::initBestPosition() {
	int max = -1;
	possiblePositions.clear();

	for (int i = 0; i < TEN; ++i) {
		for (int j = 0; j < TEN; ++j) {
			if (max < densityBoard[i][j]) {
				possiblePositions.clear();
				max = densityBoard[i][j];
				possiblePositions.push_back(std::make_pair(i, j));
			}
			else if (max == densityBoard[i][j]) {
				possiblePositions.push_back(std::make_pair(i, j));
			}
		}
	}
}

void ProbabilityDensityAlg::calcDensityDestroyMode() {
	int row = lastPredicPosisition.first;
	int col = lastPredicPosisition.second;
	char **board = boardHub->getBoardEngine()->getHiddenBoard();
	int chance = HIGH_PROBABILITY;

	int cnt = 0;
	int i = row - 1;
	while (cnt < maxShipSize && i >= 0) {
		if (board[i][col] != EMPTY_FIELD)
			break;

		densityBoard[i][col] += (chance - hitHorizontal);
		chance -= 5;
		cnt++;
		i--;
	}

	chance = HIGH_PROBABILITY;
	cnt = 0;
	i = row + 1;
	while (cnt < maxShipSize && i < TEN) {
		if (board[i][col] != EMPTY_FIELD)
			break;

		densityBoard[i][col] += (chance - hitHorizontal);
		chance -= 5;
		cnt++;
		i++;
	}

	chance = HIGH_PROBABILITY;
	cnt = 0;
	i = col - 1;
	while (cnt < maxShipSize && i >= 0) {
		if (board[row][i] != EMPTY_FIELD)
			break;

		densityBoard[row][i] += (chance - hitVertical);
		chance -= 5;
		i--;
		cnt++;
	}

	chance = HIGH_PROBABILITY;
	cnt = 0;
	i = col + 1;
	// Horizontal Right
	while (cnt < maxShipSize && i < TEN) {
		if (board[row][i] != EMPTY_FIELD)
			break;

		densityBoard[row][i] += (chance - hitVertical);
		chance -= 5;
		i++;
		cnt++;
	}
}

void ProbabilityDensityAlg::initDestroyMode() {
	int row = lastPredicPosisition.first;
	int col = lastPredicPosisition.second;
	densityBoard[row][col] = ZERO;
	calcDensityDestroyMode();
	initBestPosition();
}

std::pair<int, int> ProbabilityDensityAlg::getHighestProbabilityPos() {
	int idx = rand() % possiblePositions.size();
	lastPredicPosisition = possiblePositions[idx];
	possiblePositions.erase(possiblePositions.begin() + idx);
	densityBoard[lastPredicPosisition.first][lastPredicPosisition.second] = ZERO;
	return lastPredicPosisition;
}

std::pair<int, int> ProbabilityDensityAlg::getPosition(BoardHub *boardHub) {
	if (boardHub->getShips().size() == ZERO)
		return std::make_pair(-1, -1);

	this->boardHub = boardHub;
	srand((unsigned)time(NULL));

	if (isSink()) {
		setMaxShipSize();
		if (!checkHitShipButNotSink())
			destroyMode = false;
	}
	else if (hitFlag) {
		if (!destroyMode) {
			setMaxShipSize();
			initBoard(densityBoard);
		}

		destroyMode = true;
	}
	else if (!hitFlag && destroyMode) {
		checkMiss();
	}

	if (destroyMode) {

		if (hitFlag) {
			initDestroyMode();

			printDensityBoard();

			return getHighestProbabilityPos();
		}

		initBestPosition();

		printDensityBoard();

		return getHighestProbabilityPos();
	}
	else {
	
		hitHorizontal = 0;
		hitVertical = 0;
		initBoard(densityBoard);
		this->densityBoard = calculateDensity();
		initBestPosition();

		printDensityBoard();

		return getHighestProbabilityPos();
	}
}

bool ProbabilityDensityAlg::isSink() {
	int currShipNumber = boardHub->getShips().size();
	if (shipNumber > currShipNumber) {
		shipNumber = currShipNumber;
		return true;
	}

	return false;
}

void ProbabilityDensityAlg::setHitFlag(bool hitFlag) {
	this->hitFlag = hitFlag;
	if (destroyMode && hitFlag)
		checkOrient();
}

void ProbabilityDensityAlg::checkOrient() {
	char **board = boardHub->getBoardEngine()->getHiddenBoard();
	int row = lastPredicPosisition.first;
	int col = lastPredicPosisition.second;

	// Up
	if (row - 1 >= 0 && board[row - 1][col] == HIT_SHIP_FIELD) {
		hitVertical++;
		if (row - 2 >= 0 && board[row - 2][col] == EMPTY_FIELD)
			densityBoard[row - 2][col] += HIGH_PROBABILITY;
	}
	// Down
	else if (row + 1 <= 9 && board[row + 1][col] == HIT_SHIP_FIELD) {
		hitVertical++;
		if (row + 2 <= 9 && board[row + 2][col] == EMPTY_FIELD)
			densityBoard[row + 2][col] += HIGH_PROBABILITY;
	}
	// Left
	else if (col - 1 >= 0 && board[row][col - 1] == HIT_SHIP_FIELD) {
		hitHorizontal++;
		if (col - 2 >= 0 && board[row][col - 2] == EMPTY_FIELD)
			densityBoard[row][col - 2] += HIGH_PROBABILITY;
	}
	// Right
	else if (col + 1 <= 9 && board[row][col + 1] == HIT_SHIP_FIELD) {
		hitHorizontal++;
		if (col + 2 <= 9 && board[row][col + 2] == EMPTY_FIELD)
			densityBoard[row][col + 2] += HIGH_PROBABILITY;
	}
}

void ProbabilityDensityAlg::checkMiss() {
	char **board = boardHub->getBoardEngine()->getHiddenBoard();
	int row = lastPredicPosisition.first;
	int col = lastPredicPosisition.second;

	// UP
	if (row - 1 >= 0 && board[row - 1][col] == HIT_SHIP_FIELD) {
		for (int i = row + 1; i < TEN; i++)
			densityBoard[i][col] = LOW_PROBABILITY;

		for (int i = row - 2; i >= 0; i--) {
			if (board[i][col] == HIT_EMPTY_FIELD) {
				break;
			}
			else if (board[i][col] == EMPTY_FIELD) {
				densityBoard[i][col] += HIGH_PROBABILITY;
				break;
			}
		}
	}

	if (row + 1 <= 9 && board[row + 1][col] == HIT_SHIP_FIELD) {
		for (int i = row - 1; i >= 0; i--)
			densityBoard[i][col] = LOW_PROBABILITY;

		for (int i = row + 2; i < TEN; i++) {
			if (board[i][col] == HIT_EMPTY_FIELD) {
				break;
			}
			else if (board[i][col] == EMPTY_FIELD) {
				densityBoard[i][col] += HIGH_PROBABILITY;
				break;
			}
		}
	}

	if (col - 1 >= 0 && board[row][col - 1] == HIT_SHIP_FIELD) {
		for (int i = col + 1; i < TEN; i++)
			densityBoard[row][i] = LOW_PROBABILITY;

		for (int i = col - 2; i >= 0; i--) {
			if (board[row][i] == HIT_EMPTY_FIELD) {
				break;
			}
			else if (board[row][i] == EMPTY_FIELD) {
				densityBoard[row][i] += HIGH_PROBABILITY;
				break;
			}
		}
	}

	if (col + 1 <= 9 && board[row][col + 1] == HIT_SHIP_FIELD) {
		for (int i = col - 1; i >= 0; i--)
			densityBoard[row][i] = LOW_PROBABILITY;

		for (int i = col + 2; i < TEN; i++) {
			if (board[row][i] == HIT_EMPTY_FIELD) {
				break;
			}
			else if (board[row][i] == EMPTY_FIELD) {
				densityBoard[row][i] += HIGH_PROBABILITY;
				break;
			}
		}
	}
}

bool ProbabilityDensityAlg::checkHitShipButNotSink() {
	char **board = boardHub->getBoardEngine()->getHiddenBoard();
	bool flag = false;
	for (int i = 0; i < TEN; i++) {
		for (int j = 0; j < TEN; j++) {
			if (board[i][j] == HIT_SHIP_FIELD) {
				flag = true;
				int value = 2 * HIGH_PROBABILITY;
				for (int k = i + 1; k < TEN; k++) {
					if (board[k][j] != EMPTY_FIELD)
						break;

					if (k < TEN && board[k][j] == EMPTY_FIELD) {
						densityBoard[k][j] += value;
						value -= 5;
					}
				}

				value = 2 * HIGH_PROBABILITY;
				for (int k = i - 1; k >= 0; k--) {
					if (board[k][j] != EMPTY_FIELD)
						break;

					if (k >= 0 && board[k][j] == EMPTY_FIELD) {
						densityBoard[k][j] += value;
						value -= 5;
					}
				}

				value = 2 * HIGH_PROBABILITY;
				for (int k = j + 1; k < TEN; k++) {
					if (board[i][k] != EMPTY_FIELD)
						break;

					if (k < TEN && board[i][k] == EMPTY_FIELD) {
						densityBoard[i][k] += value;
						value -= 5;
					}
				}

				value = 2 * HIGH_PROBABILITY;
				for (int k = j - 1; k >= 0; k--) {
					if (board[i][k] != EMPTY_FIELD)
						break;

					if (k >= 0 && board[i][k] == EMPTY_FIELD) {
						densityBoard[i][k] += value;
						value -= 5;
					}
				}
			}
		}
	}

	return flag;
}

void ProbabilityDensityAlg::checkHitDensity() {
	char **board = boardHub->getBoardEngine()->getHiddenBoard();
	int row = lastPredicPosisition.first;
	int col = lastPredicPosisition.second;

	if (hitVertical > hitHorizontal) {
		// Up side: the center is from up side. The current position is below the center position
		if (row - 1 >= 0 && board[row - 1][col] == HIT_SHIP_FIELD) {
			if (row - 1 >= 0 && col - 1 >= 0)
				densityBoard[row - 1][col - 1] -= 5;

			if (row - 1 >= 0 && col + 1 < TEN)
				densityBoard[row - 1][col + 1] -= 5;
		}
		// Down side: the center is from down side. The current position is above the center position
		else if (row + 1 < TEN && board[row + 1][col] == HIT_SHIP_FIELD) {
			if (row + 1 < TEN && col - 1 >= 0)
				densityBoard[row + 1][col - 1] -= 5;

			if (row + 1 < TEN && col + 1 < TEN)
				densityBoard[row + 1][col + 1] -= 5;
		}
	}
	else if (hitVertical < hitHorizontal) {
		// Left side: the center is from left side. The current position is right next to the center position
		if (col - 1 >= 0 && board[row][col - 1] == HIT_SHIP_FIELD) {
			if (row - 1 >= 0 && col - 1 >= 0)
				densityBoard[row - 1][col - 1] -= 5;

			if (row + 1 < TEN && col - 1 >= 0)
				densityBoard[row + 1][col - 1] -= 5;
		}
		// Right size: the center is from right side. The current position is left next to the center position
		else if (col + 1 < TEN && board[row][col + 1] == HIT_SHIP_FIELD) {
			if (row - 1 >= 0 && col + 1 < TEN)
				densityBoard[row - 1][col + 1] -= 5;

			if (row + 1 < TEN && col + 1 < TEN)
				densityBoard[row + 1][col + 1] -= 5;
		}
	}
}

void ProbabilityDensityAlg::printDensityBoard() const {
	std::cout << std::endl;
	if(destroyMode)
		std::cout << "Destroy Mode" << std::endl;
	else
		std::cout << "Hunt Mode" << std::endl;
	for (int i = 0; i < TEN; ++i) {
		for (int j = 0; j < TEN; ++j)
			std::cout << std::setw(3) << densityBoard[i][j] << " ";

		std::cout << std::endl;
	}
	std::cout << "========================================" << std::endl;
}