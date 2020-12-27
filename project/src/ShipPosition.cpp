#include "ShipPosition.h"

void ShipPosition::copyShipPosition(const ShipPosition &sp) {
	this->ship = sp.ship;
	this->startPosition = sp.startPosition;
	this->endPosition = sp.endPosition;
}

bool ShipPosition::isWithinShipFields(int &startPositionField, int &endPositionField, int &field) {
	if (startPositionField <= field && field <= endPositionField) {
		return true;
	}

	return endPositionField <= field && field <= startPositionField;
}

ShipPosition::ShipPosition() : ship(), startPosition(), endPosition() {

}

ShipPosition::ShipPosition(Ship *ship, std::string &startPosition, std::string &endPosition) : ship(ship), startPosition(startPosition), endPosition(endPosition) {
}

ShipPosition::ShipPosition(const ShipPosition &sp) {
	copyShipPosition(sp);
}

ShipPosition& ShipPosition::operator=(const ShipPosition &sp) {
	if (this != &sp) {
		copyShipPosition(sp);
	}

	return *this;
}

Ship* ShipPosition::getShip() const {
	return ship;
}

Position ShipPosition::getStartPosition() const {
	return startPosition;
}

Position ShipPosition::getEndPosition() const {
	return endPosition;
}

bool ShipPosition::isWithinShip(Position &position) {
	int startPositionRow = startPosition.getRow();
	int startPositionCol = startPosition.getCol();
	int endPositionRow = endPosition.getRow();
	int endPositionCol = endPosition.getCol();
	int row = position.getRow();
	int col = position.getCol();

	if (startPositionRow == endPositionRow) {
		if (startPositionRow == row) {
			return isWithinShipFields(startPositionCol, endPositionCol, col);
		}
	}
	else if (startPositionCol == endPositionCol) {
		if (startPositionCol == col) {
			return isWithinShipFields(startPositionRow, endPositionRow, row);
		}
	}

	return false;
}

bool operator== (ShipPosition &lhs, ShipPosition &rhs) {
	if (!(lhs.ship == rhs.ship))
		return false;
	if (!(lhs.startPosition == rhs.startPosition))
		return false;
	if (!(lhs.endPosition == rhs.endPosition))
		return false;

	return true;
}