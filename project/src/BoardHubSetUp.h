#pragma once

#include <map>
#include <stdio.h>
#include "ShipFactory.h"
#include "Action.h"

const std::string INVALID_COMMAND = "Invalid command!";

class BoardHubSetUp
{
private:
	int carrierCount;
	int cruiserCount;
	int destroyerCount;
	int submarineCount;

	BoardHub *boardHub;
	ControlPanel *controlPanel;
	std::map<Ship*, bool> ships;

	void createShips(ShipType shipType, int maxShipType);
	void initShips();
	void printUpdateMap();
	void printMenu();
	void setShipsPosition();
	std::string getPlayerInput();
	void printAvailableShips();
	void executeCommand(std::string command);
	Ship* getShip(std::string shipType);
	ShipType getShipType(std::string shipType);
	bool isShipAvailable();
	void updateShipAvailableCount();

public:
	BoardHubSetUp();
	~BoardHubSetUp();

	BoardHub* initBoardHub();
	BoardHub* getBoardHub();
};

