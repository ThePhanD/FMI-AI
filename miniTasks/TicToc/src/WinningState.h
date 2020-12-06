#pragma once
#include <vector>
using namespace std;

struct Vector2 {
	int row;
	int col;

	Vector2(int row = 0, int col = 0) : row(row), col(col) {}
};

using VectorPoints = vector<Vector2>;	// Vector of Vector2


class WinningState {
private:
	std::vector<VectorPoints> winningStates;

	void initWinningStates();
public:
	WinningState();

	int getSize() const;
	std::vector<VectorPoints> getVectorPoints(); // Get winning states
	VectorPoints getAt(int i) const;
};
