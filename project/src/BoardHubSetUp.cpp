#include "BoardHubSetUp.h"

void BoardHubSetUp::createShips(ShipType shipType, int maxShipType) {
	ShipFactory factory;
	for (int i = ZERO; i < maxShipType; ++i) {
		Ship *ship = factory.buildShip(shipType);
		ships.insert(std::make_pair(ship, false));
	}
}

void BoardHubSetUp::initShips() {
	createShips(CARRIER, carrierCount);
	createShips(CRUISER, cruiserCount);
	createShips(DESTROYER, destroyerCount);
	createShips(SUBMARINE, submarineCount);
}

void BoardHubSetUp::printUpdateMap() {
	boardHub->getBoardEngine()->getBoardPtr()->printUncoverMap();
}

void BoardHubSetUp::printMenu() {
	std::cout << std::endl;
	printf("| %-10s |\n", "<place ship startPosition endPosition>");
	printf("| %-10s |\n", "<move oldShipPosition newStartPosition newEndPosition>");
}

std::string BoardHubSetUp::getPlayerInput() {
	std::cout << "\n-> ";
	std::string str;
	std::getline(std::cin, str);
	return str;
}

void BoardHubSetUp::setShipsPosition() {
	while (isShipAvailable()) {
		printMenu();

		printAvailableShips();

		std::string command = getPlayerInput();

		executeCommand(command);

		printUpdateMap();
	}
}

void BoardHubSetUp::printAvailableShips() {
	std::cout << std::endl;
	updateShipAvailableCount();
	printf("| %-10s | %9s |\n", "ShipType", "Available");
	printf("| %-10s | %9d |\n", "Carrier", carrierCount);
	printf("| %-10s | %9d |\n", "Cruiser", cruiserCount);
	printf("| %-10s | %9d |\n", "Destroyer", destroyerCount);
	printf("| %-10s | %9d |\n", "Submarine", submarineCount);
}

void split(std::vector<std::string> &tokens, std::string input) {
	std::istringstream iss(input);
	tokens = std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
}

void BoardHubSetUp::executeCommand(std::string command) {
	std::vector<std::string> argv;
	split(argv, command);

	if (controlPanel->isPlaceShipAction(command)) {
		Ship *ship = getShip(argv[1]);				// Get a ship with this ship type.
		PlaceShip placeShip(controlPanel, this->boardHub, ship, argv[2], argv[3]);
		if (placeShip.execute()) {
			ships.find(ship)->second = true;		// If the ship was placed on the map then it is added to ships.
		}
	}
	else if (controlPanel->isMoveShipAction(command)) {
		MoveShip moveShip(controlPanel, boardHub, argv[1], argv[2], argv[3]);
		moveShip.execute();
	}
	else {
		std::cout << INVALID_COMMAND << std::endl;
	}
}

void BoardHubSetUp::execute(std::string command) {
	executeCommand(command);
}

Ship* BoardHubSetUp::getShip(std::string shipType) {
	ShipType expectedType = getShipType(shipType);

	for (std::pair<Ship*, bool> ship : ships) {
		ShipType actualType = ship.first->getShipType();

		bool isNotAvailable = ship.second;	// Continue if the ship isn't available.
		if (isNotAvailable) {
			continue;
		}

		if (actualType == expectedType) {	// Return the ship of expected type.
			return ship.first;
		}
	}

	return new Ship();
}

ShipType BoardHubSetUp::getShipType(std::string shipType) {
	std::transform(shipType.begin(), shipType.end(), shipType.begin(), ::tolower);
	if (!shipType.compare("carrier"))
		return CARRIER;
	else if (!shipType.compare("cruiser"))
		return CRUISER;
	else if (!shipType.compare("destroyer"))
		return DESTROYER;
	else if (!shipType.compare("submarine"))
		return SUBMARINE;
}

void BoardHubSetUp::updateShipAvailableCount() {
	this->carrierCount = boardHub->getShipAvailableNumber(CARRIER);
	this->cruiserCount = boardHub->getShipAvailableNumber(CRUISER);
	this->destroyerCount = boardHub->getShipAvailableNumber(DESTROYER);
	this->submarineCount = boardHub->getShipAvailableNumber(SUBMARINE);
}

bool BoardHubSetUp::isShipAvailable() {
	updateShipAvailableCount();
	return carrierCount > ZERO
		|| cruiserCount > ZERO
		|| destroyerCount > ZERO
		|| submarineCount > ZERO;
}

BoardHubSetUp::BoardHubSetUp() {
	this->boardHub = new BoardHub();
	this->controlPanel = new ControlPanel();
	updateShipAvailableCount();
	initShips();
}

BoardHubSetUp::~BoardHubSetUp() {
	delete controlPanel;
	ships.clear();
}

BoardHub* BoardHubSetUp::initBoardHub() {
	std::cout << "Place your ship on the board.\n";
	printUpdateMap();

	setShipsPosition();

	return boardHub;
}

BoardHub* BoardHubSetUp::getBoardHub() {
	return boardHub;
}


