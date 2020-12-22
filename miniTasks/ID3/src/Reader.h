#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include "Event.h"

const char COMMA = ',';
const char NEW_LINE = '\n';
const char END = '\0';

class Reader
{
private:
	void readData(std::ifstream &fin, int counter, Event events[]);
public:

	int readFile(const char* filename, Event events[]);
};

