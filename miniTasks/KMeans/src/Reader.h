#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include "Point.h"

const char COMMA = ',';
const char NEW_LINE = '\n';
const char END = '\0';

class Reader
{	
public:
	int readFile(const char* filename, Point points[]);
};

