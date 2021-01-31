#include "HuntAndParityAlg.h"

HuntAndParityAlg::HuntAndParityAlg(BoardHub* boardHub)
{
	this->boardHub = boardHub;
}

bool HuntAndParityAlg::contains(const std::vector<std::pair<int, int>>& list, std::pair<int, int> x)
{
	return std::find(list.begin(), list.end(), x) != list.end();
}

std::vector<std::pair<int, int>> HuntAndParityAlg::getBoard(BoardHub* boardHub)
{
	char** board = boardHub->getBoardEngine()->getHiddenBoard();
	std::vector<std::pair<int, int>> boardV;
	for (int i = 0; i < TEN; i++) {
		for (int j = 0; j < TEN; j++) {
			std::pair<int, int> rowAndCol(i, j);
			boardV.push_back(rowAndCol);
		}
	}
	return boardV;
}
void HuntAndParityAlg::addTargetsToShootAt(BoardHub* boardHub)
{
	std::vector<std::pair<int, int>> boardV = getBoard(boardHub);
	for (auto it = begin(boardV); it != end(boardV); it += 2) {
		targetsToShooAt.push_back(*it);
	}
}

void HuntAndParityAlg::pushNeighborInStack(BoardHub* boardHub, int row, int col)
{
	std::pair<int, int> newTarget(row, col);
	if (contains(visitedTargets, newTarget)) {
		return;
	}
	else {
		targetNeighbors.push(newTarget);
	}
}


void HuntAndParityAlg::huntAndTarget(BoardHub* boardHub)  {
	char** board = boardHub->getBoardEngine()->getHiddenBoard();
	if (targetNeighbors.empty()) {
		int idx = rand() % targetsToShooAt.size();
		std::list<std::pair<int, int>>::iterator it = targetsToShooAt.begin();
		std::advance(it, idx);
		lastHitTarget = *it;
		visitedTargets.push_back(lastHitTarget);
		targetsToShooAt.remove(*it);
	}
	else {
		lastHitTarget = targetNeighbors.top();
		visitedTargets.push_back(lastHitTarget);
		targetNeighbors.pop();
	}
}

std::pair<int, int> HuntAndParityAlg::getPosition(BoardHub* boardHub)
{
	huntAndTarget(boardHub);
	return lastHitTarget;
}

void HuntAndParityAlg::setHitFlag(bool hitFlag)
{
	if (!hitFlag) {
		return;
	}

	int row = lastHitTarget.first;
	int col = lastHitTarget.second;
	char** board = boardHub->getBoardEngine()->getHiddenBoard();
	if (row - 1 >= 0) {
		pushNeighborInStack(boardHub, row - 1, col);
	}
	if (row + 1 <= TEN - 1) {
		pushNeighborInStack(boardHub, row + 1, col);
	}
	if (col - 1 >= 0) {
		pushNeighborInStack(boardHub, row, col - 1);
	}
	if (col + 1 <= TEN - 1) {
		pushNeighborInStack(boardHub, row, col + 1);
	}
}
