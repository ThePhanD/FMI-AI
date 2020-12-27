#pragma once
#include <string>
#include <algorithm>
#include "Ship.h"

const std::string SUBMARINE_STR = "SUBMARINE";
const std::string DESTROYER_STR = "DESTROYER";
const std::string CRUISER_STR = "CRUISER";
const std::string CARRIER_STR = "CARRIER";

class ShipFactory
{
public:
	static int id;
	Ship* buildShip(ShipType &shipType);
	Ship* buildShip(std::string &shipType);
};

