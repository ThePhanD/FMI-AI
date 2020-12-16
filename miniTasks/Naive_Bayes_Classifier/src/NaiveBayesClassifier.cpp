#include "NaiveBayesClassifier.h"

int NaiveBayesClassifier::numberOfPeople(const char *name, int left, int right) {
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (i < left || i > right) {
			if (!strcmp(people[i].name, name))
				counter++;
		}
	}
	return counter;
}

void NaiveBayesClassifier::init() {
	srand((unsigned)time(0));
	std::random_shuffle(people, people + size);

	int partSize = size / NUMBER_OF_SETS;
	int rest = size % NUMBER_OF_SETS;

	setsOfPeople = std::vector<int>(NUMBER_OF_SETS, partSize);
	int idx = 0;
	while (rest > 0) {
		setsOfPeople[idx]++;
		idx++;
		rest--;
	}
}

NaiveBayesClassifier::NaiveBayesClassifier(Person *people, int size) : size(size) {
	this->people = new Person[size];
	for (int i = 0; i < size; ++i) {
		this->people[i] = people[i];
	}

	init();
}

NaiveBayesClassifier::~NaiveBayesClassifier() {
	delete[] people;
}

int NaiveBayesClassifier::answerToInt(char answer) {
	return answer == 'y' ? 1 : 0;
}
double checkValue(int number, int size) {
	if (number == 0)
		return VERY_SMALL_NUMBER;

	return (double)number / size;
}

void NaiveBayesClassifier::learn(int left, int right, int republicanCounter, int democraftCounter, std::vector<std::vector<double>> &republicans, std::vector<std::vector<double>> &democrats) {
	for (int i = 0; i < NUMBER_OF_ATTRIBUTES; i++) {
		int countRepublicansAnswers[2] = { 0 };
		int countDemocratsAnswers[2] = { 0 };
		
		for (int j = 0; j < size; j++) {
			if (j < left || j > right) {
				if (!strcmp(people[j].name, REPUBLICAN)) {
					countRepublicansAnswers[answerToInt(people[j].attributes[i])]++;
				}
				else {
					countDemocratsAnswers[answerToInt(people[j].attributes[i])]++;
				}
			}
		}

		std::vector<double> attributeAnswers;
		attributeAnswers.push_back(checkValue(countRepublicansAnswers[0], republicanCounter));
		attributeAnswers.push_back(checkValue(countRepublicansAnswers[1], republicanCounter));
		republicans.push_back(attributeAnswers);
		attributeAnswers.clear();
		attributeAnswers.push_back(checkValue(countDemocratsAnswers[0], democraftCounter));
		attributeAnswers.push_back(checkValue(countDemocratsAnswers[1], democraftCounter));
		democrats.push_back(attributeAnswers);
	}
}

int NaiveBayesClassifier::predict(int left, int right, double republicanProbability, double democratProbability, std::vector<std::vector<double>> republicans, std::vector<std::vector<double>> democrats) {
	int match = 0;
	for (int i = left; i <= right; i++) {
		double currentRepublicanProbability = 1.0, currentDemocratProbability = 1.0;
		for (int j = 0; j < NUMBER_OF_ATTRIBUTES; j++) {
			currentRepublicanProbability *= republicans[j][answerToInt(people[i].attributes[j])];
			currentDemocratProbability *= democrats[j][answerToInt(people[i].attributes[j])];
		}

		currentRepublicanProbability *= republicanProbability;
		currentDemocratProbability *= democratProbability;

		if (currentRepublicanProbability - currentDemocratProbability < VERY_SMALL_NUMBER) {
			if (!strcmp(people[i].name, DEMOCRAT))
				match++;
		}
		else {
			if (!strcmp(people[i].name, REPUBLICAN))
				match++;
		}
	}

	return match;
}

void NaiveBayesClassifier::solve(int numberOfTests) {
	int sumSizes = 0;
	double sumAccuracy = 0.0;

	for (int i = 0; i < numberOfTests; ++i) {
		// test set includes elements in the interval [left, right] in people[]
		int left = sumSizes;
		int right = sumSizes + setsOfPeople[i] - 1;

		int republicanCounter = numberOfPeople(REPUBLICAN, left, right);
		int democraftCounter = numberOfPeople(DEMOCRAT, left, right);
		int sizeOfPoeple = republicanCounter + democraftCounter;
		double republicanProbability = (double)republicanCounter / sizeOfPoeple;	
		double democratProbability = (double)democraftCounter / sizeOfPoeple;

		std::vector<std::vector<double>> republicans; // P(X | Class = republican)
		std::vector<std::vector<double>> democrats;   // P(X | Class = democrat)
		learn(left, right, republicanCounter, democraftCounter, republicans, democrats);

		int match = predict(left, right, republicanProbability, democratProbability, republicans, democrats);
		double accuracy = ((double)match / setsOfPeople[i]) * 100.0;
		sumAccuracy += accuracy;
		std::cout << "Accuracy is " << accuracy << "% for test set number " << i + 1 << std::endl;

		sumSizes += setsOfPeople[i];
	}

	std::cout << "Average accuracy is " << sumAccuracy / NUMBER_OF_SETS << std::endl;
}