#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include "Person.h"

const char COMMA = ',';
const char NEW_LINE = '\n';
const char END = '\0';

class Reader
{
private:
	void readData(std::ifstream &fin, int counter, Person people[]);
public:

	int readFile(const char* filename, Person people[]);
};

