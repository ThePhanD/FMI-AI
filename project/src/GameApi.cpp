#include "GameApi.h"

void GameApi::setUpBoardHubPlayerOne() {
	BoardHubSetUp setup;
	playerOneHub = setup.initBoardHub();
}

void GameApi::setUpBoardHubPlayerTwo() {
	BoardHubSetUp setup;
	playerTwoHub = setup.initBoardHub();
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
			return executeAttackUtility(playerTwoHub, 2, turn);
		}

		return executeAttackUtility(playerOneHub, 1, turn);
	}
	else {
		return INVALID_COMMAND;
	}
}

void GameApi::updatePlayers() {
	if (playerOneHub->isGameOver()) { // Player one lost the game
		showPlayerOneGameResult();
		std::cout << "The opponet won the game!" << std::endl;
		std::cout << "You lost the game!" << std::endl;
	}
	else if (playerTwoHub->isGameOver()) { // Plyaer two lost the game
		showPlayerOneGameResult();
		std::cout << "The opponet the game!" << std::endl;
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
		showPlayerOneGameResult(); // Show player One game result
		std::string message = executePlayerOneTurn(); // Player One turn
		if (isGameOver()) {
			break;
		}

		if (!message.compare("QUIT")) { // When player One left the game by typing <quit>
			std::cout << "You surrender!" << std::endl; // Receive player Two last request
			std::cout << "The opponent won the game!" << std::endl;
			break;
		}

		std::string inputLine = executePlayerTwoTurn(); // Player Two turn
		if (isGameOver()) {
			break;
		}

		if (!inputLine.compare("QUIT")) { // When player Two left the game by typing <quit>
			std::cout << "You won the game!" << std::endl; // Receive player One last request
			std::cout << "The opponent surrender!" << std::endl;
			break;
		}
	}
}

GameApi::GameApi() {
	controlPanel = new ControlPanel();
	playerOneLastTurn = "None";
	playerTwoLastTurn = "None";
}

GameApi::~GameApi() {
	delete controlPanel;
	delete playerOneHub;
	delete playerTwoHub;
}

void GameApi::run() {
	setUpBoardHubPlayerOne();
	setUpBoardHubPlayerTwo();

	startGame();
}