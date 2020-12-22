#include "Solver.h"

Solver::Solver(const char *filename, int numberOfTests, int k) : numberOfTests(numberOfTests) {
	size = reader.readFile(filename, events);
	id3 = new ID3(k);
	initSets();
}

Solver::~Solver() {
	delete id3;
}

void Solver::insertEvents(int start, int end) {
	std::vector<Event> set;
	for (int i = start; i <= end; ++i) {
		set.push_back(events[i]);
	}

	setsOfEvents.push_back(set);
}

void Solver::initSets() {
	srand((unsigned)time(0));
	std::random_shuffle(events, events + size);

	int partSize = size / numberOfTests;
	int rest = size % numberOfTests;

	std::vector<int> eventSizes = std::vector<int>(numberOfTests, partSize);
	int idx = 0;
	while (rest > 0) {
		eventSizes[idx]++;
		idx++;
		rest--;
	}

	int sumSizes = 0;
	for (int i = 0; i < numberOfTests; ++i) {
		int start = sumSizes;
		int end = sumSizes + eventSizes[i] - 1;
		insertEvents(start, end);
		sumSizes += eventSizes[i];
	}
}

void Solver::solve() {
	double sumAccuracy = 0.0;
	for (int i = 0; i < numberOfTests; ++i) {
		std::vector<Event> testSet = setsOfEvents[0];
		setsOfEvents.erase(setsOfEvents.begin() + 0);
		id3->learn(setsOfEvents);
		int match = id3->predict(testSet);

		double accuracy = ((double)match / testSet.size()) * 100.0;
		sumAccuracy += accuracy;
		std::cout << "Accuracy is " << accuracy << "% for test set number " << i + 1 << std::endl;
		setsOfEvents.push_back(testSet);
	}

	std::cout << "Average accuracy is " << sumAccuracy / numberOfTests << std::endl;
}