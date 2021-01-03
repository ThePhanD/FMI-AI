#include <iostream>
#include "GameApi.h"

using namespace std;

int main()
{	
	/*
	// Place every ship on a board
	BoardHubSetUp hub;
	hub.initBoardHub();
	*/

	GameApi api;
	api.runWithOneAiProbabilityDensityAlg();


	return 0;
}


