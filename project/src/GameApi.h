#pragma once

#include "BoardHubSetUp.h"

const std::string LAST_TURN = "Opponent last turn: ";

class GameApi
{
private:
	ControlPanel *controlPanel;
	BoardHub *playerOneHub;
	BoardHub *playerTwoHub;
	std::string playerOneLastTurn;
	std::string playerTwoLastTurn;

	void setUpBoardHubPlayerOne();
	void setUpBoardHubPlayerTwo();
	void printMenu();
	bool isGameOver();
	void showPlayerOneGameResult();
	void showPlayerTwoGameResult();
	void updatePlayers();
	std::string executeAttackUtility(BoardHub *boardHub, int playerNumber, std::string turn);
	std::string updateLastTurn(int playerNumber, std::string lastTurn);
	std::string executeTurn(std::string turn, bool isPlayerOne);
	std::string executePlayerOneTurn();
	std::string executePlayerTwoTurn();
	void startGame();

public:
	GameApi();
	~GameApi();
	
	void run();
};

