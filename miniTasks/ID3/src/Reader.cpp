#include "Reader.h"

void Reader::readData(std::ifstream &fin, int counter, Event events[]) {
	char c;
	int attrIdx = 0, idx = 0;
	while (fin.get(c)) {
		if (c == NEW_LINE) {
			events[counter].attributes[attrIdx][idx] = END;
			break;
		}
		else if (c == COMMA) {
			events[counter].attributes[attrIdx][idx] = END;
			attrIdx++;
			idx = 0;
		}
		else {
			events[counter].attributes[attrIdx][idx++] = c;
		}
	}
}

int Reader::readFile(const char* filename, Event events[]) {
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
			events[counter].name[idx] = END;
			readData(fin, counter, events);
			idx = 0;
			counter++;
		}
		else {
			events[counter].name[idx++] = c;
		}
	}

	fin.close();

	return counter;
}