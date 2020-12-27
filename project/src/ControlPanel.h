#pragma once

#include "BoardHub.h"
#include <string>
#include <iterator>
#include <sstream>

const std::string MOVE = "move";
const std::string PLACE = "place";
const std::string ATTACK = "attack";

const int PLACE_ARG_COUNT = 4;
const int MOVE_ARG_COUNT = 4;
const int ATTACK_ARG_COUNT = 2;

const int ACTION_NAME = 0;

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

