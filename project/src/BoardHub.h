#pragma once

#include "ShipPosition.h"
#include "BoardEngine.h"
#include <vector>

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
	void lineAttack(const ShipPosition &sp);
	bool attack(std::string &position);

	BoardEngine* getBoardEngine() const;
	bool isGameOver() const;
	int getShipAvailableNumber(const ShipType &shipType) const;
	std::vector<ShipPosition> getShips() const;
};

