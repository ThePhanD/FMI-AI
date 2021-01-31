#include "GameApi.h"

void GameApi::setUpBoardHubPlayerOne() {
	BoardHubSetUp setup;
	playerOneHub = setup.initBoardHub();
}

void GameApi::setUpBoardHubPlayerTwo() {
	BoardHubSetUp setup;
	playerTwoHub = setup.initBoardHub();
}

void GameApi::setUpBoardHubAi(int playerNumber, std::vector<std::string> commands) {
	BoardHubSetUp setup;
	for (std::string command : commands)
		setup.execute(command);

	if (playerNumber == 1) {
		playerOneHub = setup.getBoardHub();
	}
	else {
		playerTwoHub = setup.getBoardHub();
	}
}

void GameApi::printMenu() {
	std::cout << std::endl;
	printf("| %-32s |\n", "MENU");
	printf("| %-32s |\n", "<attack position>");
	std::cout << std::endl;
}

bool GameApi::isGameOver() {
	if (playerOneHub->isGameOver()) {
		return true;
	}

	return playerTwoHub->isGameOver();
}

void GameApi::showPlayerOneGameResult() {
	printf("| %14s %4s |", "YOUR BOAR", "");
	playerOneHub->getBoardEngine()->printUncoverBoard();
	std::cout << std::endl;
	printf("| %14s %4s |", "ENEMY BOAR", "");
	playerTwoHub->getBoardEngine()->printHiddenBoard();
	std::cout << playerTwoLastTurn << std::endl;
}

void GameApi::showPlayerTwoGameResult() {
	printf("| %14s %4s |", "YOUR BOAR", "");
	playerTwoHub->getBoardEngine()->printUncoverBoard();
	std::cout << std::endl;
	printf("| %14s %4s |", "ENEMY BOAR", "");
	playerOneHub->getBoardEngine()->printHiddenBoard();
	std::cout << playerTwoLastTurn << std::endl;
}

void splitToTokens(std::vector<std::string> &tokens, std::string input) {
	std::istringstream iss(input);
	tokens = std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
}

std::string GameApi::updateLastTurn(int playerNumber, std::string lastTurn) {
	if (playerNumber == 1) {
		this->playerOneLastTurn = LAST_TURN + lastTurn;
	}
	else {
		this->playerTwoLastTurn = LAST_TURN + lastTurn;
	}
	return LAST_TURN + lastTurn;
}

std::string GameApi::executeAttackUtility(BoardHub *boardHub, int playerNumber, std::string turn) {
	std::vector<std::string> argv;
	splitToTokens(argv, turn);
	Attack attack(controlPanel, boardHub, argv[1]);

	if (attack.execute()) {
		return updateLastTurn(playerNumber, argv[1]);
	}

	return INVALID_COMMAND;
}

std::string GameApi::executeTurn(std::string turn, bool isPlayerOne) {
	if (controlPanel->isAttackAction(turn)) {
		if (isPlayerOne) {
			return executeAttackUtility(playerTwoHub, 1, turn);
		}

		return executeAttackUtility(playerOneHub, 2, turn);
	}
	else {
		return INVALID_COMMAND;
	}
}

void GameApi::updatePlayers(){	
	if (playerOneHub->isGameOver()) {			// Player one lost the game
		showPlayerOneGameResult();
		std::cout << "The opponet won the game!" << std::endl;
		std::cout << "You lost the game!" << std::endl;
	}
	else if (playerTwoHub->isGameOver()) {		// Plyaer two lost the game
		showPlayerOneGameResult();
		std::cout << "The opponet lost the game!" << std::endl;
		std::cout << "You won the game!" << std::endl;
	}
}

std::string GameApi::executePlayerOneTurn() {
	while (true) {
		std::cout << "Your turn: ";
		std::string turn;
		std::getline(std::cin, turn);

		std::string message = executeTurn(turn, true);

		if (isGameOver()) {
			updatePlayers();
			return "QUIT";
		}

		std::transform(message.begin(), message.end(), message.begin(), ::toupper);
		if (message.compare(INVALID_COMMAND)) {
			return message;
		}

		std::cout << INVALID_COMMAND << std::endl;
	}
}

std::string GameApi::executePlayerTwoTurn() {
	while (true) {
		std::cout << "Your turn: ";
		std::string turn;
		std::getline(std::cin, turn);
		std::string message = executeTurn(turn, false);
		if (isGameOver()) {
			updatePlayers();
			return "QUIT";
		}

		std::transform(message.begin(), message.end(), message.begin(), ::toupper);
		if (message.compare(INVALID_COMMAND)) {
			return message;
		}

		std::cout << INVALID_COMMAND << std::endl;
	}
}

void GameApi::startGame() {
	while (true) {
		printMenu();
		showPlayerOneGameResult();						// Show player One game result
		std::string message = executePlayerOneTurn();	// Player One turn
		if (isGameOver()) {
			break;
		}

		if (!message.compare("QUIT")) {					// When player One left the game by typing <quit>
			std::cout << "You surrender!" << std::endl;
			std::cout << "The opponent won the game!" << std::endl;
			break;
		}

		std::string inputLine = executePlayerTwoTurn(); // Player Two turn
		if (isGameOver()) {
			break;
		}

		if (!inputLine.compare("QUIT")) {				// When player Two left the game by typing <quit>
			std::cout << "You won the game!" << std::endl; 
			std::cout << "The opponent surrender!" << std::endl;
			break;
		}
	}
}

GameApi::GameApi() {
	controlPanel = new ControlPanel();
	playerOneLastTurn = LAST_TURN + "None";
	playerTwoLastTurn = LAST_TURN + "None";
}

GameApi::~GameApi() {
	delete controlPanel;
	delete playerOneHub;
	delete playerTwoHub;
}

void GameApi::printGameOptions() const {
	std::cout << "Welcome to Battleship FMI Style!" << std::endl;
	std::cout << "Choose one of the option below!" << std::endl;
	std::cout << "1) Plaver vs Player" << std::endl;
	std::cout << "2) Plaver vs AI-Normal" << std::endl;
	std::cout << "3) Plaver vs AI-Hard" << std::endl;
	std::cout << "4) Quit!" << std::endl;
	std::cout << "-> ";
}

void GameApi::run() {
	int option;

	while (true) {
		printGameOptions();
		std::cin >> option;
		std::cin.ignore();

		switch (option) {
		case 1: runWithTwoPlayer();
			return;
		case 2:
			return;
		case 3: runWithOneAiProbabilityDensityAlg();
			return;
		case 4: std::cout << "Support the game :D !" << std::endl;
			return;
		default:
			continue;
		}
	}
}

void GameApi::runWithTwoPlayer() {
	setUpBoardHubPlayerOne();
	setUpBoardHubPlayerTwo();

	startGame();
}

void createAiOneShipPlacement(std::vector<std::string> &commands) {
	commands.push_back("place carrier A9 E9");
	commands.push_back("place cruiser F2 F5");
	commands.push_back("place cruiser C6 F6");
	commands.push_back("place destroyer F10 H10");
	commands.push_back("place destroyer A2 A4");
	commands.push_back("place destroyer I5 I7");
	commands.push_back("place submarine G1 G2");
	commands.push_back("place submarine D3 E3");
	commands.push_back("place submarine I2 J2");
	commands.push_back("place submarine A5 A6");
}

void GameApi::runWithOneAiProbabilityDensityAlg() {
	setUpBoardHubPlayerOne();

	std::vector<std::string> commands;
	createAiOneShipPlacement(commands);
	setUpBoardHubAi(2, commands);
	probDensityAlg = new ProbabilityDensityAlg(playerOneHub);

	startGameWithOneAi();
}

std::string convecrtToString(std::pair<int, int> pos) {
	char c = (char)('A' + pos.first);
	std::string str = "attack ";
	str.push_back(c);
	str += std::to_string(pos.second + 1);
	return str;
}

std::string GameApi::executeAITurn(std::pair<int, int> pos) {
	
	std::string command = convecrtToString(pos);

	std::string message = executeTurn(command, false);
	if (isGameOver()) {
		updatePlayers();
		return "QUIT";
	}

	std::transform(message.begin(), message.end(), message.begin(), ::toupper);
	return message;
}

void GameApi::deleteHiddenBoard(char** hiddenBoard) {
	for (int i = 0; i < 10; i++) {
		delete[] hiddenBoard[i];
	}
	delete[] hiddenBoard;
}

void GameApi::startGameWithOneAi() {
	while (true) {
		printMenu();
		showPlayerOneGameResult();						// Show player One game result
		std::string message = executePlayerOneTurn();	// Player One turn
		if (isGameOver()) {
			break;
		}
		
		if (!message.compare("QUIT")) {					// When player One left the game by typing <quit>
			std::cout << "You surrender!" << std::endl;
			std::cout << "The opponent won the game!" << std::endl;
			break;
		}

		// AI turn
		std::pair<int, int> pos = probDensityAlg->getPosition(playerOneHub);
		std::string inputLine = executeAITurn(pos);
		char** board = playerOneHub->getBoardEngine()->getHiddenBoard();
		probDensityAlg->setHitFlag(board[pos.first][pos.second] == HIT_SHIP_FIELD);
		deleteHiddenBoard(board);

		if (isGameOver()) {
			break;
		}

		if (!inputLine.compare("QUIT")) { 
			std::cout << "You won the game!" << std::endl;
			std::cout << "The opponent surrender!" << std::endl;
			break;
		}
	}
}