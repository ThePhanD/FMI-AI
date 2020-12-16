#pragma once
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include "Person.h"
#include "NaiveBayesClassifier.h"

const char YES = 'y';
const char NO = 'n';

class Processing
{
private:
	int size;
	int republicanAttributePriorities[ATTRIBUTES_SIZE];
	int democratAttributePriorities[ATTRIBUTES_SIZE];

	int answerToInt(char answer);
	void initPriorities(Person people[]);
	char answerForAttribute(int attribute, int attributePriorities[]);

public:
	Processing(Person people[], int size);
	void process(Person people[]);
};

