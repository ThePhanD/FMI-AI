#include "Ship.h"

void Ship::copyShip(const Ship &s) {
	this->shipID = s.shipID;
	this->size = s.size;
	this->shipType = s.shipType;
	this->health = s.health;
}

void Ship::setHealth(int health) {
	this->health = health;
}

Ship::Ship() : shipID(-1), size(-1), health(-1) {}

Ship::Ship(int shipID, int size, ShipType shipType) : shipID(shipID),
	size(size), shipType(shipType), health(size) {
}

Ship::Ship(const Ship &s) {
	copyShip(s);
}

Ship& Ship::operator=(const Ship &s) {
	if (this != &s) {
		copyShip(s);
	}

	return *this;
}

int Ship::getId() const {
	return shipID;
}

int Ship::getSize() const {
	return size;
}

ShipType Ship::getShipType() const {
	return shipType;
}

bool Ship::isAlive() const {
	return health > NO_HEALTH;
}

int Ship::getHealth() const {
	return health;
}

void Ship::takeDamage() {
	if (isAlive()) {
		health--;
	}
}

bool operator== (Ship &lhs, Ship &rhs) {
	if (lhs.shipID != rhs.shipID)
		return false;
	if (lhs.size != rhs.size)
		return false;
	if (lhs.shipType != rhs.shipType)
		return false;
	if (lhs.health != rhs.health)
		return false;

	return true;
}

Carrier::Carrier(int shipId) : Ship(shipId, CARRIER_SIZE, CARRIER) {}

Cruiser::Cruiser(int shipId) : Ship(shipId, CRUISER_SIZE, CRUISER) {}

Destroyer::Destroyer(int shipId) : Ship(shipId, DESTROYER_SIZE, DESTROYER) {}

Submarine::Submarine(int shipId) : Ship(shipId, SUBMARINE_SIZE, SUBMARINE) {}
