#include "BoardHub.h"

bool BoardHub::modifyShipPosition(const ShipPosition &shipPosition, const bool &removeShip) {
	Position startPosition = shipPosition.getStartPosition();
	Position endPosition = shipPosition.getEndPosition();
	Ship *ship = shipPosition.getShip();

	int startPositionRow = startPosition.getRow();
	int startPositionCol = startPosition.getCol();
	int endPositionRow = endPosition.getRow();
	int endPositionCol = endPosition.getCol();

	if (removeShip) { // Remove the ship from the map.
		return boardEngine->removeShip(startPositionRow, startPositionCol, endPositionRow, endPositionCol, ship);
	}
	else { // Place the ship on the map.
		return boardEngine->setShip(startPositionRow, startPositionCol, endPositionRow, endPositionCol, ship);
	}
}

bool BoardHub::changeShipToNewPosition(const ShipPosition &oldShipPosition, std::string &newStartPosition, std::string &newEndPosition) {
	Ship *ship = oldShipPosition.getShip();

	//Remove the ship old position.
	if (modifyShipPosition(oldShipPosition, true)) {
		changeShipAvailableNumber(ship, false); // Increate the count of this shipType
		if (!placeShip(ship, newStartPosition, newEndPosition)) {

			//If the ship can't be placed to the new position then it is placed to the old position.
			modifyShipPosition(oldShipPosition, false);
			changeShipAvailableNumber(ship, true);	// Reduce the count of this shipType
			return false;
		}
		return true;
	}

	return false;
}

void BoardHub::attackShip(const ShipPosition &shipPosition) {
	Ship *ship = shipPosition.getShip();
	ship->takeDamage(); // Ship health is reduced by 1.

	//If the ship is still alive then its added back.
	if (ship->isAlive()) {
		ships.push_back(shipPosition);
	}
	else {
		lineAttack(shipPosition);
	}
}

ShipPosition BoardHub::getShipPositionAt(Position &position) {
	for (int i = 0; i < ships.size(); ++i) {
		ShipPosition sp = ships[i];
		if (sp.isWithinShip(position)) {
			ships.erase(ships.begin() + i);
			return sp;
		}
	}

	return ShipPosition();
}

bool BoardHub::isShipAvailable(Ship *ship) {
	ShipType shipType = ship->getShipType();
	int shipNumber = getShipAvailableNumber(shipType);

	// Check for available shipType
	if (shipNumber == 0) {
		std::cerr << SHIP_UNAVAILABLE << std::endl;
		return false;
	}
	else if (shipNumber < 0) {
		std::cerr << SHIP_NOT_EXIST << std::endl;
		return false;
	}

	return true;
}

void BoardHub::changeShipAvailableNumber(Ship *ship, const bool &reduce) {
	ShipType shipType = ship->getShipType();
	int i = 1;
	if (reduce) {
		i = -1;
	}

	switch (shipType) {
	case CARRIER:
		carrierNumbers = carrierNumbers + i;
		break;
	case CRUISER:
		cruiserNumbers = cruiserNumbers + i;
		break;
	case DESTROYER:
		destroyerNumbers = destroyerNumbers + i;
		break;
	case SUBMARINE:
		submarineNumbers = submarineNumbers + i;
		break;
	}
}

void BoardHub::deleteAction() {
	delete boardEngine;
	ships.clear();
}

void BoardHub::copyAction(const BoardHub &a) {
	boardEngine = a.boardEngine;
	ships = a.ships;
	carrierNumbers = a.carrierNumbers;
	cruiserNumbers = a.cruiserNumbers;
	destroyerNumbers = a.destroyerNumbers;
	submarineNumbers = a.submarineNumbers;
}

BoardHub::BoardHub() : carrierNumbers(1), cruiserNumbers(2), destroyerNumbers(3), submarineNumbers(4) {
	boardEngine = new BoardEngine();
}

BoardHub::~BoardHub() {
	deleteAction();
}

BoardHub::BoardHub(const BoardHub &a) {
	copyAction(a);
}

BoardHub& BoardHub::operator=(const BoardHub &a) {
	if (this != &a) {
		deleteAction();
		copyAction(a);
	}

	return *this;
}

bool BoardHub::isContainsShip(ShipPosition &shipPosition) {
	for (ShipPosition &sp : ships) {
		if (sp == shipPosition)
			return true;
	}

	return false;
}

bool BoardHub::placeShip(Ship *ship, std::string &startPosition, std::string &endPosition) {
	
	ShipPosition shipPosition(ship, startPosition, endPosition);
	// Check if this shipType is available and it doesn't been place on the map
	if (isShipAvailable(ship) && !isContainsShip(shipPosition)) {

		//If the ship is successfully placed on the map then it is added to the game.
		if (modifyShipPosition(shipPosition, false)) { // false == place
			changeShipAvailableNumber(ship, true); // Reduce the available shipType
			ships.push_back(shipPosition);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		std::cerr << CHANGE_SHIP << std::endl;
		return false;
	}

	return false;
}

bool BoardHub::changeShipPosition(std::string &shipPosition, std::string &newStartPosition, std::string &newEndPosition) {
	
	Position newPosition(shipPosition);
	ShipPosition oldShipPosition = getShipPositionAt(newPosition);

	if (oldShipPosition.getShip()->getId() != -1) {

		//If the ship can't be changed to the new position then the old ship position is added back.
		if (!changeShipToNewPosition(oldShipPosition, newStartPosition, newEndPosition)) {
			ships.push_back(oldShipPosition);
			std::cerr << SHIP_UNCHANGEABLE << std::endl;
			std::cerr << CHANGE_SHIP << std::endl;
			return false;
		}

		return true;
	}
	else {
		std::cerr << SHIP_UNCHANGEABLE << std::endl;
		std::cerr << CHANGE_SHIP << std::endl;
		return false;
	}
}

void BoardHub::lineAttack(const ShipPosition &sp) {
	Position startPosition = sp.getStartPosition();
	Position endPosition = sp.getEndPosition();
	char numberMark = (char)('0' + sp.getShip()->getSize());

	if (startPosition.getRow() == endPosition.getRow()) {
		int start = std::min(startPosition.getCol(), endPosition.getCol());
		int end = std::max(startPosition.getCol(), endPosition.getCol());
		for (int i = start; i <= end; i++)
			boardEngine->placeAtPosition(startPosition.getRow(), i, numberMark);
	}
	else {
		int start = std::min(startPosition.getRow(), endPosition.getRow());
		int end = std::max(startPosition.getRow(), endPosition.getRow());
		for (int i = start; i <= end; i++)
			boardEngine->placeAtPosition(i, startPosition.getCol(), numberMark);
	}
}

bool BoardHub::attack(std::string &position) {
	
	Position newPosition(position);
	int row = newPosition.getRow();
	int col = newPosition.getCol();
	if (boardEngine->fireAtPosition(row, col)) {
		ShipPosition shipPosition = getShipPositionAt(newPosition); // Get a ship from the hit field
		if (shipPosition.getShip()->getId() != -1) {
			attackShip(shipPosition); // If there is a ship then the ship takes damage.
		}
		return true;
	}

	return false;
}

BoardEngine* BoardHub::getBoardEngine() const {
	return boardEngine;
}

bool BoardHub::isGameOver() const {
	return ships.empty();
}

int BoardHub::getShipAvailableNumber(const ShipType &shipType) const {
	if (shipType == CARRIER) {
		return this->carrierNumbers;
	}
	if (shipType == CRUISER)
		return this->cruiserNumbers;
	if (shipType == DESTROYER)
		return this->destroyerNumbers;
	if (shipType == SUBMARINE)
		return this->submarineNumbers;

	return -1;
}

std::vector<ShipPosition> BoardHub::getShips() const {
	return ships;
}