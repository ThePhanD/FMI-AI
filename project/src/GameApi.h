#pragma once

#include "BoardHubSetUp.h"
#include "ProbabilityDensityAlg.h"
#include "HuntAndParityAlg.h"

class GameApi
{
private:
	ControlPanel* controlPanel;
	BoardHub* playerOneHub;
	BoardHub* playerTwoHub;
	std::string playerOneLastTurn;
	std::string playerTwoLastTurn;

	ProbabilityDensityAlg* probDensityAlg;
	HuntAndParityAlg* huntAndParityAlg;

	void deleteHiddenBoard(char** hiddenBoard);
	void setUpBoardHubPlayerOne();
	void setUpBoardHubPlayerTwo();
	void setUpBoardHubAi(int playerNumber, std::vector<std::string> commands);
	void printMenu();
	void printGameOptions() const;
	bool isGameOver();
	void showPlayerOneGameResult();
	void showPlayerTwoGameResult();
	void updatePlayers();
	std::string executeAttackUtility(BoardHub* boardHub, int playerNumber, std::string turn);
	std::string updateLastTurn(int playerNumber, std::string lastTurn);
	std::string executeTurn(std::string turn, bool isPlayerOne);
	std::string executePlayerOneTurn();
	std::string executePlayerTwoTurn();
	std::string executeAITurn(std::pair<int, int> pos);
	void startGame();
	void startGameWithOneAi(int option);

	void runWithTwoPlayer();
	void runWithOneAiProbabilityDensityAlg();
	void runWithHuntAndParityAlg();

public:
	GameApi();
	~GameApi();

	void run();
};
