#pragma once

#include "BoardHub.h"
#include "Constants.h"
#include <iterator>
#include <sstream>

class ControlPanel
{
private:
	void getTokens(std::vector<std::string> &tokens, std::string input);

public:

	bool isPlaceShipAction(std::string action);
	bool isMoveShipAction(std::string action);
	bool isAttackAction(std::string action);
	bool placeShip(BoardHub *boardHub, Ship *ship, std::string startPosition, std::string endPosition);
	bool moveShip(BoardHub *boardHub, std::string shipPosition, std::string newStartPosition, std::string newEndPosition);
	bool attack(BoardHub *boardHub, std::string position);
};

