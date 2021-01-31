#pragma once

#include "BoardHub.h"

#include <stack>
#include <list>

class HuntAndParityAlg{
private:
	BoardHub* boardHub;
	std::pair<int, int> lastHitTarget;
	std::list<std::pair<int, int>> targetsToShooAt;
	std::vector<std::pair<int, int>> visitedTargets;
	std::stack<std::pair<int, int>> targetNeighbors;
	bool contains(const std::vector<std::pair<int, int>>& list, std::pair<int, int> x);
	std::vector<std::pair<int, int>> getBoard(BoardHub* boardHub);
	void pushNeighborInStack(BoardHub* boardHub, int row, int col);

public:
	HuntAndParityAlg(BoardHub* boardHub);
	void addTargetsToShootAt(BoardHub* boardHub);
	void huntAndTarget(BoardHub* boardHub);
	std::pair<int, int> getPosition(BoardHub* boardHub);
	void setHitFlag(bool hitFlag);

};