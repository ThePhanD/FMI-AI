#include "ShipFactory.h"

int ShipFactory::id{ 0 };

Ship* ShipFactory::buildShip(ShipType &shipType) {
	Ship *ship;
	switch (shipType) {
		case ShipType::CARRIER: ship = new Carrier(id); 
			break;
		case ShipType::CRUISER: ship = new Cruiser(id);
			break;
		case ShipType::DESTROYER: ship = new Destroyer(id);
			break;
		case ShipType::SUBMARINE: ship = new Submarine(id);
			break;
		default: return new Ship();
	}

	id++;
	return ship;
}

Ship* ShipFactory::buildShip(std::string &shipType) {
	Ship *ship;
	std::transform(shipType.begin(), shipType.end(), shipType.begin(), ::toupper);

	if (!shipType.compare(CARRIER_STR))
		ship = new Carrier(id);
	else if (!shipType.compare(CRUISER_STR))
		ship = new Cruiser(id);
	else if (!shipType.compare(DESTROYER_STR))
		ship = new Destroyer(id);
	else if (!shipType.compare(SUBMARINE_STR))
		ship = new Submarine(id);
	else
		return new Ship();

	id++;
	return ship;
}
