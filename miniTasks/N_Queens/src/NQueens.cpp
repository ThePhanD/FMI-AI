#include "NQueens.h"

void NQueens::initDefaultValues()
{
	for (int i = 0; i < size; i++) {
		colums[i] = 0;
	}

	for (int i = 0; i < 2 * size - 1; i++) {
		risingDiag[i] = 0;
		fallingDiag[i] = 0;
	}
}

// Place queens with mininal conflict
void NQueens::initQueensPositions()
{
	vector<int> minConflictCols;			// Store collums with mininal conflict
	int minConflicts;
	int conflCounter;

	// Place first queen randomly
	queens[0] = rand() % size;	// from 0 to size - 1 

	colums[queens[0]] += 1;
	risingDiag[queens[0]] += 1;
	fallingDiag[(size - queens[0]) - 1] += 1;

	for (int row = 1; row < size; row++) {
		minConflictCols.clear();
		minConflicts = INF_CONFLICTS;

		for (int col = 0; col < size; col++) {				// Add one for conflict (n+1)*n/2
			conflCounter = ((colums[col] + 1) * colums[col]) / 2;
			conflCounter += ((risingDiag[col + row] + 1) * risingDiag[col + row]) / 2;
			conflCounter += ((fallingDiag[(size - col) + row - 1] + 1) * fallingDiag[(size - col) + row - 1]) / 2;

			if (conflCounter < minConflicts) {				// Find the smallest conflicts number
				minConflicts = conflCounter;
				minConflictCols.clear();
				minConflictCols.push_back(col);
			}
			else if (conflCounter == minConflicts) {		// Insert col with the same conflict number
				minConflictCols.push_back(col);
			}
		}

		int colPosition = rand() % minConflictCols.size();		// Choose randomly collum
		queens[row] = minConflictCols[colPosition];

		colums[queens[row]] += 1;
		risingDiag[queens[row] + row] += 1;
		fallingDiag[(size - queens[row]) + row - 1] += 1;
	}
}

void NQueens::initQueensPrimaryDiagoanl()
{
	for (int i = 0; i < size; ++i)
		queens[i] = i;
}

void NQueens::initQueensRandomly()
{
	for (int i = 0; i < size; ++i)
		queens[i] = rand() % size;
}

NQueens::NQueens(int size) : size(size)
{
	queens = new int[size];
	colums = new int[size];
	risingDiag = new int[(2 * size) - 1];
	fallingDiag = new int[(2 * size) - 1];

	initDefaultValues();
	initQueensPositions();			// Place queens with minimal conflict
	//initQueensPrimaryDiagoanl();	// Place queens in the primary diagonal
	//initQueensRandomly();			// Place queens randomly in every collums
}

NQueens::~NQueens() {
	delete[] queens;
	delete[] colums;
	delete[] risingDiag;
	delete[] fallingDiag;
}

// Get number of all conflicts
int NQueens::getAllConflicts()
{
	int conflCounter = 0;

	initDefaultValues();

	// Set all queens properties
	for (int i = 0; i < size; i++) {
		colums[queens[i]] += 1;
		risingDiag[queens[i] + i] += 1;
		fallingDiag[(size - queens[i]) + i - 1] += 1;
	}

	for (int i = 0; i < 2 * size - 1; i++) {		// Remove one because because one is on right place: (n-1)n/2
		if (i < size) {
			conflCounter += ((colums[i] - 1) * colums[i]) / 2;
		}
		conflCounter += ((risingDiag[i] - 1) * risingDiag[i]) / 2;
		conflCounter += ((fallingDiag[i] - 1) * fallingDiag[i]) / 2;
	}

	return conflCounter;
}

// Get row with most conflicts
int NQueens::getRowWithMaxConflicts() {
	int maxRowConflicts = 0;
	int conflCounter;
	vector<int> maxConflictRows;

	for (int i = 0; i < size; i++) {
		conflCounter = ((colums[queens[i]] - 1) * colums[queens[i]]) / 2;
		conflCounter += ((risingDiag[queens[i] + i] - 1) * risingDiag[queens[i] + i]) / 2;
		conflCounter += ((fallingDiag[(size - queens[i]) + i - 1] - 1) * fallingDiag[(size - queens[i]) + i - 1]) / 2;

		if (conflCounter > maxRowConflicts) {
			maxRowConflicts = conflCounter;
			maxConflictRows.clear();
			maxConflictRows.push_back(i);
		}
		else if (conflCounter == maxRowConflicts) {
			maxConflictRows.push_back(i);
		}
	}

	int rowPosition = rand() % maxConflictRows.size();	// Get random row with highest number of conflicts
	return maxConflictRows[rowPosition];
}

// Choose randomly queen with max conflicts and place it randomly at min conflicts col
void NQueens::setQueenWithMaxConfRowToMinConfCol()
{
	int rowWithMaxConfl = getRowWithMaxConflicts();
	int minConflicts = INF_CONFLICTS;
	int conflCounter;

	vector<int> minConflictCols;		// min conflicts cols for queen

	for (int col = 0; col < size; col++) {
		conflCounter = ((colums[col] + 1) * colums[col]) / 2;
		conflCounter += ((risingDiag[col + rowWithMaxConfl] + 1) * risingDiag[col + rowWithMaxConfl]) / 2;
		conflCounter += ((fallingDiag[(size - col) + rowWithMaxConfl - 1] + 1) * fallingDiag[(size - col) + rowWithMaxConfl - 1]) / 2;

		if (conflCounter < minConflicts) {
			minConflicts = conflCounter;
			minConflictCols.clear();
			minConflictCols.push_back(col);
		}
		else if (conflCounter == minConflicts) {
			minConflictCols.push_back(col);
		}
	}

	int colPosition = rand() % minConflictCols.size();
	queens[rowWithMaxConfl] = minConflictCols[colPosition];
}

void NQueens::solveNQueens()
{
	auto start = chrono::high_resolution_clock::now();

	int currentConflicts = getAllConflicts();
	int newConflicts;
	int count = 0;

	// MinConflicts algorithm
	while (currentConflicts != 0) {
		setQueenWithMaxConfRowToMinConfCol();
		newConflicts = getAllConflicts();
		if (currentConflicts == newConflicts) {
			count++;
			if (count > 1) {		// If the number of new conflicts is the same then change random queen to random position
				queens[rand() % size] = rand() % size;
				count = 0;
			}
		}
		currentConflicts = newConflicts;
	}

	auto finish = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(finish - start);
	cout << size << "-Queens was solved in " << duration.count() << " milliseconds.\n\n";
}

void NQueens::printResult() const
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < queens[i]; j++) {
			cout << "_ ";
		}
		cout << "* ";
		for (int j = 0; j < size - queens[i] - 1; j++) {
			cout << "_ ";
		}
		cout << "\n";
	}
}

bool NQueens::isSolvable() const {
	return size == 1 || size > 3;
}

void NQueens::solve()
{
	if (isSolvable()) {
		solveNQueens();

		if (size <= 50) {
			printResult();
		}
	}
	else {
		cout << size << "-Queens is Unsolvable!\n";
	}
}