#include "Reader.h"

int Reader::readFile(const char* filename, Point points[]) {
	std::ifstream fin(filename, std::ios::in);

	if (!fin.is_open()) {
		std::cerr << "The file " << filename << " can't be open!\n";
		return -1;
	}

	string line;
	int counter = 0;
	while (getline(fin, line)) {
		stringstream lineStream(line);
		double x, y;

		lineStream >> x;
		lineStream >> y;

		if (x >= 1000)
			x = x * 0.001;

		if (y >= 1000)
			y = y * 0.001;

		points[counter].x = x;
		points[counter++].y = y;
	}

	fin.close();

	return counter;
}