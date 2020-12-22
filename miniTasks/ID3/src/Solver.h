#pragma once
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <map>
#include "Reader.h"
#include "ID3.h"

const int MAX_SIZE = 512;

class Solver
{
private:
	Event events[MAX_SIZE];
	Reader reader;
	ID3 *id3;

	int size;
	int numberOfTests;
	std::vector<std::vector<Event>> setsOfEvents;

	void initSets();
	void insertEvents(int start, int end);

public:
	Solver(const char *filename, int numberOfTests, int k);
	~Solver();
	void solve();
};

