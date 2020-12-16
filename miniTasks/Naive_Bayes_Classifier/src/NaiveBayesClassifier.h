#pragma once
#include <algorithm>
#include <ctime>
#include <vector>
#include <map>
#include <iostream>
#include "Person.h"

const int NUMBER_OF_SETS = 10;
const int NUMBER_OF_ATTRIBUTES = 16;
const double VERY_SMALL_NUMBER = 0.000000001;
const char REPUBLICAN[] = "republican\0";
const char DEMOCRAT[] = "democrat\0";

class NaiveBayesClassifier
{
private:
	Person *people;
	int size;
	std::vector<int> setsOfPeople;

	void init();
	int numberOfPeople(const char *name, int left, int right);
	void learn(int left, int right, int republicanCounter, int democraftCounter, std::vector<std::vector<double>> &republicans, std::vector<std::vector<double>> &democrats);
	int predict(int left, int right, double republicanProbability, double democratProbability, std::vector<std::vector <double> > republicans, std::vector<std::vector<double>> democrats);
	int answerToInt(char answer);

public:
	NaiveBayesClassifier(Person *people, int size);
	~NaiveBayesClassifier();

	void solve(int numberOfTests);
};


