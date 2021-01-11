#pragma once
#include "ControlPanel.h"

class Action
{
public:
	virtual bool execute() = 0;
};

class Attack : public Action 
{
private:
	ControlPanel *controlPanel;
	BoardHub *boardHub;
	std::string position;

public:
	Attack(ControlPanel *controlPanel, BoardHub *boardHub, std::string position);
	~Attack();

	bool execute();
};

class MoveShip : public Action
{
private:
	ControlPanel *controlPanel;
	BoardHub *boardHub;
	std::string shipPosition;
	std::string newStartPosition;
	std::string newEndPosition;

public:
	MoveShip(ControlPanel *controlPanel, BoardHub *boardHub, std::string shipPosition, std::string newStartPosition, std::string newEndPosition);
	~MoveShip();

	bool execute();
};

class PlaceShip : public Action
{
private:
	ControlPanel *controlPanel;
	BoardHub *boardHub;
	Ship *ship;
	std::string startPosition;
	std::string endPosition;

public:
	PlaceShip(ControlPanel *controlPanel, BoardHub *boardHub, Ship *ship, std::string startPosition, std::string endPosition);
	~PlaceShip();

	bool execute();
};