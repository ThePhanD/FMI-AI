#pragma once

#include <vector>
#include <algorithm>
#include "ShipPosition.h"
#include "BoardEngine.h"

const std::string SHIP_UNREPAIRABLE = "The ship can't be repaired!";
const std::string SHIP_UNCHANGEABLE = "The ship can't change his position!";
const std::string SHIP_UNAVAILABLE = "This type of ship can't be placed anymore!";
const std::string SHIP_NOT_EXIST = "This ship doesn't exist!";
const std::string CHANGE_SHIP = "Please choose a different ship!";

class BoardHub
{
private: 
	int carrierNumbers;
	int cruiserNumbers;
	int destroyerNumbers;
	int submarineNumbers;

	BoardEngine* boardEngine;
	std::vector<ShipPosition> ships;

	void deleteAction();
	void copyAction(const BoardHub &a);
	bool modifyShipPosition(const ShipPosition &shipPosition, const bool &removeShip);
	bool changeShipToNewPosition(const ShipPosition &oldShipPosition, std::string &newStartPosition, std::string &newEndPosition);
	void attackShip(const ShipPosition &shipPosition);
	ShipPosition getShipPositionAt(Position &position);
	bool isShipAvailable(Ship *ship);
	void changeShipAvailableNumber(Ship *ship, const bool &reduce);
	bool isContainsShip(ShipPosition &shipPosition);

public:
	BoardHub();
	~BoardHub();
	BoardHub(const BoardHub &a);
	BoardHub& operator=(const BoardHub &a);

	bool placeShip(Ship *ship, std::string &startPosition, std::string &endPosition);
	bool changeShipPosition(std::string &shipPosition, std::string &newStartPosition, std::string &newEndPosition);
	bool attack(std::string &position);

	BoardEngine* getBoardEngine() const;
	bool isGameOver() const;
	int getShipAvailableNumber(const ShipType &shipType) const;
};

