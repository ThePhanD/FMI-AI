#pragma once
#include <string>
#include "ShipType.h"

const static int NO_HEALTH = 0;

const int SUBMARINE_SIZE = 2;
const int DESTROYER_SIZE = 3;
const int CRUISER_SIZE = 4;
const int CARRIER_SIZE = 5;

const ShipType SUBMARINE = ShipType::SUBMARINE;
const ShipType DESTROYER = ShipType::DESTROYER;
const ShipType CRUISER = ShipType::CRUISER;
const ShipType CARRIER = ShipType::CARRIER;

class Ship
{
private:
	int shipID;
	int size;
	ShipType shipType;
	int health;

	void copyShip(const Ship &s);
	void setHealth(int health);

public:
	Ship();
	Ship(int shipID, int size, ShipType shipType);
	Ship(const Ship &s);
	Ship& operator=(const Ship &s);

	int getId() const;
	int getSize() const;
	ShipType getShipType() const;
	bool isAlive() const;
	int getHealth() const;
	void takeDamage();

	friend bool operator== (Ship &lhs, Ship &rhs);
};

class Carrier : public Ship {
public:
	Carrier(int shipId);
};

class Cruiser : public Ship {
public:
	Cruiser(int shipId);
};

class Destroyer : public Ship {
public:
	Destroyer(int shipId);
};

class Submarine : public Ship {
public:
	Submarine(int shipId);
};