
#include <iostream>
#include "Solver.h"

const char *FILENAME = "../resource/breast-cancer.data";

int main()
{
	Solver solver(FILENAME, 10, 5);
	solver.solve();

	return 0;
}
