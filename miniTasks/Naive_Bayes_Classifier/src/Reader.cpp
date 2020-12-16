#include "Reader.h"

void Reader::readData(std::ifstream &fin, int counter, Person people[]) {
	char c;
	int idx = 0;
	while (fin.get(c)) {
		if (c == NEW_LINE) {
			break;
		}
		else if (c != COMMA) {
			people[counter].attributes[idx++] = c;
		}
	}
}

int Reader::readFile(const char* filename, Person people[]) {
	std::ifstream fin(filename, std::ios::in);

	if (!fin.is_open()) {
		std::cerr << "The file " << filename << " can't be open!\n";
		return -1;
	}

	char c;
	int counter = 0;
	int idx = 0;
	while (fin.get(c)) {
		if (c == COMMA) {
			people[counter].name[idx] = END;
			readData(fin, counter, people);
			idx = 0;
			counter++;
		}
		else {
			people[counter].name[idx++] = c;
		}
	}

	fin.close();

	return counter;
}