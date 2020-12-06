#pragma once
#include "Board.h"
#include <algorithm>
using namespace std;

class MinMaxAlphaBetaAlg
{
private:
	Board* board;

	bool isGameFinished() const;
	pair<int, Vector2> alg(char marker, int depth, int alpha, int beta);

	void playerStart();
	void aiStart();

public:
	MinMaxAlphaBetaAlg(Board* board);

	void run();
};


