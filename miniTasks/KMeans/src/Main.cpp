#include <iostream>
#include <fstream>
#include "Reader.h"
#include "KMeans.h"

const char* NORMAL_FILENAME = "../resources/normal.txt";
const char* UNBALANCE_FILENAME = "../resources/unbalance.txt";
const char* TO_NORMAL_FILENAME = "../results/normalResult.bmp";
const char* TO_UNBALANCE_FILENAME = "../results/unbalanceResult.bmp";

void initNormalTest() {
	Point points[128];
	Reader reader;
	int size = reader.readFile(NORMAL_FILENAME, points);

	int k = 4;
	double shifting = -5.0;
	int multiply = 400;
	KMeans alg(k, points, size, shifting, multiply);
	alg.run(TO_NORMAL_FILENAME);
}

void initUnbalanceTest() {
	Point points[6500];
	Reader reader;
	int size = reader.readFile(UNBALANCE_FILENAME, points);

	int k = 8;
	double shifting = -375;
	int multiply = 2;
	KMeans alg(k, points, size, shifting, multiply);
	alg.run(TO_UNBALANCE_FILENAME);
}

int main()
{
	initNormalTest();
	initUnbalanceTest();

	return 0;
}

