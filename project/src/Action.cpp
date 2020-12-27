#include "Action.h"

Attack::Attack(ControlPanel *controlPanel, BoardHub *boardHub, std::string position) {
	this->controlPanel = controlPanel;
	this->boardHub = boardHub;
	this->position = position;
}

Attack::~Attack() {
}

bool Attack::execute() {
	return controlPanel->attack(boardHub, position);
}

MoveShip::MoveShip(ControlPanel *controlPanel, BoardHub *boardHub, std::string shipPosition, std::string newStartPosition, std::string newEndPosition) {
	this->controlPanel = controlPanel;
	this->boardHub = boardHub;
	this->shipPosition = shipPosition;
	this->newStartPosition = newStartPosition;
	this->newEndPosition = newEndPosition;
}

MoveShip::~MoveShip() {
}

bool MoveShip::execute() {
	return controlPanel->moveShip(boardHub, shipPosition, newStartPosition, newEndPosition);
}

PlaceShip::PlaceShip(ControlPanel *controlPanel, BoardHub *boardHub, Ship *ship, std::string startPosition, std::string endPosition) {
	this->controlPanel = controlPanel;
	this->boardHub = boardHub;
	this->ship = ship;
	this->startPosition = startPosition;
	this->endPosition = endPosition;
}

PlaceShip::~PlaceShip() {
}

bool PlaceShip::execute() {
	return controlPanel->placeShip(boardHub, ship, startPosition, endPosition);
}