#pragma once
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "Event.h"
#include "Node.h"

const char REC[] = "recurrence-events\0";
const char NO_REC[] = "no-recurrence-events\0";

const char predictors[ATTRIBUTES_SIZE][ATTRIBUTE_NAME_LENGTH] = { "age\0", "menopause\0", "tumor-size\0", 
			"inv-nodes\0", "node-caps\0", "deg-malig\0", "breast\0", "breast-quad\0", "irradiat\0" };

struct cmp_str
{
	bool operator()(char const *a, char const *b) const
	{
		return std::strcmp(a, b) < 0;
	}
};

class ID3
{
private:
	double entropyTarget;
	int k;
	Node *root;

	std::vector<int> attributesIndex;
	std::vector<int> setsOfEvents;
	std::vector<const char*> predictorsTypes[13];
	std::map<const char*, int, cmp_str> answerToInt;
	std::map<const char*, int, cmp_str> attributeIndex;

	void initPredictorsTypes();
	int numberOfEvent(const char *name, std::vector<Event> setsOfEvent);
	double entropyCalc(double a, double b);
	double entropyTwoElements(int recAnswers[], int noRecAnswers[], int answersSize, int attrLength);
	double gain(int recAnswers[], int noRecAnswers[], int answersSize, int attrLength);
	int getBestAtrrGain(std::vector<Event> learnEventSet, double &maxGain, std::vector<int> attributesIndex);
	void initEventSets(Node *node, int attrIdx, std::vector<Event> events);
	void buildTree(Node* &root, std::vector<Event> learnEventSet, std::vector<int> attributesIndex);
	char* getClass(Node* node, Event e, int idx);

public:
	ID3(int k);
	~ID3();

	void learn(std::vector<std::vector<Event>> setsOfEvents);
	int predict(std::vector<Event> events);
};

