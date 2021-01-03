#include "ShipFactory.h"

int ShipFactory::id{ 0 };

Ship* ShipFactory::buildShip(ShipType &shipType) {
	Ship *ship;
	int idNumber = id;
	switch (shipType) {
		case ShipType::CARRIER: ship = new Carrier(idNumber);
			break;
		case ShipType::CRUISER: ship = new Cruiser(idNumber);
			break;
		case ShipType::DESTROYER: ship = new Destroyer(idNumber);
			break;
		case ShipType::SUBMARINE: ship = new Submarine(idNumber);
			break;
		default: return new Ship();
	}

	id++;
	return ship;
}

Ship* ShipFactory::buildShip(std::string &shipType) {
	Ship *ship;
	std::transform(shipType.begin(), shipType.end(), shipType.begin(), ::toupper);
	int idNumber = id;

	if (!shipType.compare(CARRIER_STR))
		ship = new Carrier(idNumber);
	else if (!shipType.compare(CRUISER_STR))
		ship = new Cruiser(idNumber);
	else if (!shipType.compare(DESTROYER_STR))
		ship = new Destroyer(idNumber);
	else if (!shipType.compare(SUBMARINE_STR))
		ship = new Submarine(idNumber);
	else
		return new Ship();

	id++;
	return ship;
}
