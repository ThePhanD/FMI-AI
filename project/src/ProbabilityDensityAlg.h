#pragma once

#include "BoardHub.h"
#include <utility> 
#include <time.h>
#include <cstdlib>

class ProbabilityDensityAlg
{
private:
	BoardHub *boardHub;
	bool destroyMode;
	bool hitFlag;
	int maxShipSize;
	int shipNumber;
	int hitHorizontal;
	int hitVertical;
	std::pair<int, int> lastPredicPosisition;
	std::vector<std::vector<int>> densityBoard;
	std::vector<std::pair<int, int>> possiblePositions;

	bool isHorizontal(int row, int col, int shipSize);
	bool isVertical(int row, int col, int shipSize);
	std::vector<std::vector<int>> calculateDensity();
	void setMaxShipSize();
	void initBoard(std::vector<std::vector<int>> &board);
	void initBestPosition();
	bool isSink();
	void initDestroyMode();
	void calcDensityDestroyMode();
	void checkOrient();
	void checkMiss();
	void checkHitDensity();
	bool checkHitShipButNotSink();
	std::pair<int, int> getHighestProbabilityPos();
	
public:
	ProbabilityDensityAlg(BoardHub *boardHub);

	std::pair<int, int> getPosition(BoardHub *boardHub);
	void setHitFlag(bool hitFlag);
	void printDensityBoard() const;
};

