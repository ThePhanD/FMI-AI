#include "NPuzzleApp.h"

void NPuzzleApp::insertBoard()
{
	std::cout << "Insert elements\n";
	int n;

	for (int i = 0; i < size * size; i++)
	{
		std::cin >> n;
		board.push_back(n);
	}

	std::cout << "\n\nCalculating!!!\n";
}

void NPuzzleApp::initSize()
{
	int n;
	std::cout << "Board elements size: ";
	std::cin >> n;
	std::cout << std::endl;

	n++;
	size = sqrt(n);
}

void NPuzzleApp::initZero()
{
	int n;
	std::cout << "Zero position: ";
	std::cin >> n;
	std::cout << std::endl;

	zeroPosition = n == -1 ? 8 : n;
}

Puzzle NPuzzleApp::initPuzzle() {
	PuzzleState startState(size, board, zeroPosition);
	PuzzleState goalState(size);

	return Puzzle(size, startState, goalState);
}

IDAStar NPuzzleApp::initAlg() {
	return IDAStar(size);
}

NPuzzleApp::NPuzzleApp() : size(3), zeroPosition(8) {}

void NPuzzleApp::init3Puzzle() {
	//size = 3;

	//zeroPosition = 0;
	//board = { 0, 1, 3, 4, 2, 5, 7, 8, 6 };	// 4

	zeroPosition = 6;
	board = { 1, 6, 2, 5, 7, 3, 0, 4, 8 };	// 10

	//zeroPosition = 4;
	//board = { 8, 1, 3, 4, 0, 2, 7, 6, 5 };	// 14

	//zeroPosition = 3;
	//board = { 4, 1, 2, 0, 8, 7, 6, 3, 5 };	// 17

	//zeroPosition = 1;
	//board = { 8, 0, 6, 5, 4, 7, 2, 3, 1 };	// 27

	//zeroPosition = 5;
	//board = { 6, 4, 7, 8, 5, 0, 3, 2, 1 };	// 31

	//zeroPosition = 8;
	//board = { 1, 2, 3, 4, 5, 6, 8, 7, 0 };	// Unsolvable
}

void NPuzzleApp::init4Puzzle()
{
	size = 4;

	//zeroPosition = 5;
	//board = { 13, 1, 2, 4, 5, 0, 3, 7, 9, 6, 10, 12, 15, 8, 11, 14 }; // Unsolvable

	//zeroPosition = 15;
	//board = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15 ,14, 0 }; // Unsolvable

	//zeroPosition = 6;
	//board = { 1, 2, 3, 4, 5, 6, 0, 8, 9, 10, 7, 11, 13, 14, 15, 12 }; // 3
	
	//zeroPosition = 3;
	//board = { 2, 3, 4, 0, 1, 5, 7, 8, 9, 6, 10, 12, 13, 14, 11, 15 }; // 9


	//zeroPosition = 0;
	//board = { 0, 1, 2, 3, 9, 7, 8, 4, 13, 5, 6, 11, 14, 15, 10, 12 }; // 18

	zeroPosition = 10;
	board = { 9, 1, 2, 3, 13, 7, 8, 4, 14, 5, 0, 11, 15, 10, 6, 12 }; // 24

	//zeroPosition = 10;
	//board = { 1, 9, 2, 3, 5, 12, 11, 10, 13, 6, 0, 8, 7, 14, 15, 4 }; // 38

	//zeroPosition = 10;
	//board = { 11, 8, 15, 12, 3, 2, 1, 9, 10, 4, 0, 6, 13, 14, 7, 5 };	// 54
}

void NPuzzleApp::init5Puzzle()
{
	size = 5;


	//zeroPosition = 6;
	//board =	{	1, 2, 3, 4, 5, 
	//			6, 0, 7, 9, 10,
	//			11, 12, 8, 13, 14, 
	//			16, 17, 18, 19, 15,
	//			21, 22, 23, 24, 20
	//}; // 6

	//zeroPosition = 24;
	//board = { 1, 2, 3, 4, 5,
	//			6, 7, 8, 9, 10,
	//			11, 12, 13, 14, 15,
	//			16, 17, 18, 19, 20,
	//			21, 22, 24, 23, 0
	//}; // Unsolvable

	zeroPosition = 0;
	board = {	0, 1, 2, 3, 4, 
				7, 8, 9, 10, 5,
				6, 11, 12, 13, 14,
				17, 18, 19, 20, 15,
				16, 21, 22, 23, 24,
	}; // 24

	//zeroPosition = 20;
	//board = {	1, 2, 3, 4, 5,
	//			6, 7, 8, 9, 10,
	//			12, 17, 13, 14, 15,
	//			16, 11, 18, 19, 20,
	//			0, 21, 22, 23, 24
	//}; // 10
}

void NPuzzleApp::init()
{
	std::cout << "NPuzzle Calculator!\n" << std::endl;

	initSize();
	initZero();
	insertBoard();

	//init3Puzzle();
	//init4Puzzle();
	//init5Puzzle();

	Puzzle puzzle = initPuzzle();
	IDAStar idaStar = initAlg();
	Solver solver(puzzle, idaStar);
	
	Solution *result = solver.solve();
	result->printResult();
}
