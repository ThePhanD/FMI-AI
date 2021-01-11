#pragma once
#include "Constants.h"

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