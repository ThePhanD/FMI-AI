#include "Processing.h"

int Processing::answerToInt(char answer) {
	if (answer == YES)
		return 1;
	if (answer == NO)
		return -1;

	return 0;
}

void Processing::initPriorities(Person people[]) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < ATTRIBUTES_SIZE; ++j) {
			if (!strcmp(people[i].name, REPUBLICAN)) {
				republicanAttributePriorities[j] += answerToInt(people[i].attributes[j]);
			}
			else {
				democratAttributePriorities[j] += answerToInt(people[i].attributes[j]);
			}
		}
	}
}

Processing::Processing(Person people[], int size) {
	for (int i = 0; i < ATTRIBUTES_SIZE; ++i) {
		republicanAttributePriorities[i] = 0;
		democratAttributePriorities[i] = 0;
	}
	this->size = size;
	initPriorities(people);
}

char Processing::answerForAttribute(int attribute, int attributePriorities[]) {
	if (attributePriorities[attribute] > 0)
		return YES;
	if (attributePriorities[attribute] < 0)
		return NO;

	srand((unsigned)time(0));
	int number = rand() % 10;
	return number < 5 ? YES : NO;
}

void Processing::process(Person people[]) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < ATTRIBUTES_SIZE; ++j) {
			if (!answerToInt(people[i].attributes[j])) {
				if (!strcmp(people[i].name, REPUBLICAN)) {
					people[i].attributes[j] = answerForAttribute(j, republicanAttributePriorities);
				}
				else {
					people[i].attributes[j] = answerForAttribute(j, democratAttributePriorities);
				}
			}
		}
	}
}