#pragma once
#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

const int INF_CONFLICTS = 1000000;

class NQueens
{
private:
	int size;
	int* queens;		// Rows
	int* colums;
	int* risingDiag;	// '/'
	int* fallingDiag;	// '\'

	void initDefaultValues();
	void initQueensRandomly();
	void initQueensPositions();
	void initQueensPrimaryDiagoanl();

	bool isSolvable() const;
	int getAllConflicts();
	int getRowWithMaxConflicts();
	void setQueenWithMaxConfRowToMinConfCol();
	void solveNQueens();
	void printResult() const;
public:
	NQueens(int size);
	~NQueens();

	void solve();
};