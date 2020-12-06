#include "WinningState.h"

void WinningState::initWinningStates() {
	winningStates = {
		// Rows
		{ Vector2(0, 0), Vector2(0, 1), Vector2(0, 2) },
		{ Vector2(1, 0), Vector2(1, 1), Vector2(1, 2) },
		{ Vector2(2, 0), Vector2(2, 1), Vector2(2, 2) },

		// Cols
		{ Vector2(0, 0), Vector2(1, 0), Vector2(2, 0) },
		{ Vector2(0, 1), Vector2(1, 1), Vector2(2, 1) },
		{ Vector2(0, 2), Vector2(1, 2), Vector2(2, 2) },

		// Diagonals
		{ Vector2(0, 0), Vector2(1, 1), Vector2(2, 2) },
		{ Vector2(2, 0), Vector2(1, 1), Vector2(0, 2) }
	};
}

WinningState::WinningState() {
	initWinningStates();
}

int WinningState::getSize() const {
	return winningStates.size();
}

std::vector<VectorPoints> WinningState::getVectorPoints() {
	return winningStates;
}

VectorPoints WinningState::getAt(int i) const {
	return winningStates[i];
}