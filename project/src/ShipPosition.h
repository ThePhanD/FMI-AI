#pragma once

#include "Ship.h"
#include "Position.h"

class ShipPosition
{
private:
	Ship *ship;
	Position startPosition;
	Position endPosition;

	void copyShipPosition(const ShipPosition &sp);
	bool isWithinShipFields(int &startPositionField, int &endPositionField, int &field);

public:
	ShipPosition();
	ShipPosition(Ship *ship, std::string &startPosition, std::string &endPosition);
	ShipPosition(const ShipPosition &sp);
	ShipPosition& operator=(const ShipPosition &sp);

	Ship *getShip() const;
	Position getStartPosition() const;
	Position getEndPosition() const;
	bool isWithinShip(Position &position);

	friend bool operator== (ShipPosition &lhs, ShipPosition &rhs);

};

