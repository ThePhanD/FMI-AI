#pragma once
#include "Ship.h"
#include <algorithm>

class ShipFactory
{
public:
	static int id;
	Ship* buildShip(ShipType &shipType);
	Ship* buildShip(std::string &shipType);
};

