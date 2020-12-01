#include "GeneticAlg.h"

GeneticAlg::GeneticAlg(Graph* graph, int populationSize, int generations, int mutationRate) :
	populationSize(populationSize), generations(generations), mutationRate(mutationRate),  currentPopulationSize(0)
{
	this->graph = graph;
}

// checks if is a valid solution, then return total cost of path else return -1
int GeneticAlg::isValidSolution(vector<int> &solution) {
	int totalVertices = graph->getTotalVertices();
	set<int> solutions;

	for (int i = 0; i < totalVertices; i++)	// Insert all the genes
		solutions.insert(solution[i]);

	if (solutions.size() != totalVertices)	// Check if the solution is correct
		return -1;

	int totalCost = 0;
	for (int i = 0; i < totalVertices; i++) {
		if (i + 1 < totalVertices) {
			int cost = graph->existsEdge(solution[i], solution[i + 1]);
				
			if (cost == -1)	// checks if exists edge
				return -1;
			else
				totalCost += cost;
		}
		else {
			int cost = graph->existsEdge(solution[i], solution[0]);

			if (cost == -1)	// checks if exists edge
				return -1;
			else
				totalCost += cost;
			break;
		}
	}

	return totalCost;
} 

bool GeneticAlg::existsGene(const vector<int> &gene) {
	for (graphPair pair : population) {
		const vector<int> &oldGene = pair.first;
		if (equal(gene.begin(), gene.end(), oldGene.begin()))  // compares the generation if exists return true
			return true;
	}
	return false;
}

void GeneticAlg::initPopulation()
{
	vector<int> parent;
	int startVertex = graph->getStartVertex();
	int totalVertices = graph->getTotalVertices();

	for (int i = 0; i < totalVertices; ++i)
		parent.push_back(-1);

	if (!graph->isCyclic(parent)) {
		cout << "\nThe graph do not have hamiltonian cycle!\n";
		return;
	}

	int totalCost = isValidSolution(parent);
	if (totalCost != -1) {						// checks if the parent is valid
		population.push_back(make_pair(parent, totalCost));		
		currentPopulationSize++;						
	}

	int startGenerationSize = generations / 2;
	for (int i = 0; i < startGenerationSize; i++) {		// makes random permutations of generations
		random_shuffle(parent.begin() + 1, parent.begin() + (rand() % (totalVertices - 1) + 1)); // Permutation inside
		totalCost = isValidSolution(parent);

		if (totalCost != -1 && !existsGene(parent)) {	// checks if permutation is a valid solution and if does not exist
			population.push_back(make_pair(parent, totalCost));
			currentPopulationSize++;
		}

		if (currentPopulationSize == populationSize)	// checks size population
			break;
	}

	if (currentPopulationSize == 0)
		cout << "\nThe population can not be created!\n";
	else
		sort(population.begin(), population.end(), sortByWeight()); // sort population
}

void GeneticAlg::insertByBinarySearch(vector<int>& child, int totalCost)
{
	int left = 0;
	int right = currentPopulationSize - 1;
	 
	while (left <= right) {
		int mid = (left + right) / 2;

		if (totalCost == population[mid].second) {
			population.insert(population.begin() + mid, make_pair(child, totalCost));
			return;
		}
		else if (totalCost > population[mid].second)
			left = mid + 1;
		else
			right = mid - 1;
	}
	population.insert(population.begin() + left, make_pair(child, totalCost));
}

void GeneticAlg::mutate(vector<int> child1, vector<int> child2) {
	int totalVertices = graph->getTotalVertices();
	int mutation = rand() % 100 + 1;					// random number in [1,100]
	if (mutation <= mutationRate) {
		int indexGene1 = rand() % (totalVertices - 1) + 1;
		int indexGene2 = rand() % (totalVertices - 1) + 1;

		swap(child1[indexGene1], child1[indexGene2]);
		swap(child2[indexGene1], child2[indexGene2]);
	}

	int totalCostChild1 = isValidSolution(child1);
	int totalCostChild2 = isValidSolution(child2);

	if (totalCostChild1 != -1 && !existsGene(child1)) {	// Insert childs if they are valid and have new genes
		insertByBinarySearch(child1, totalCostChild1);
		currentPopulationSize++;
	}

	if (totalCostChild2 != -1 && !existsGene(child2)) {
		insertByBinarySearch(child2, totalCostChild2);
		currentPopulationSize++;
	}
}

void adjustPonts(int &point1, int &point2, int &totalVertices) {
	if (point1 == point2) {
		if (point1 - 1 > 1)
			point1--;
		else if (point2 + 1 < totalVertices)
			point2++;
		else {

			int randPoint = rand() % 10 + 1;	// random number in [1,10]
			if (randPoint <= 5)
				point1--;
			else
				point2++;
		}
	}
}

int GeneticAlg::getAvailablePosition(int position, vector<int> &fromParent, vector<int> child, map<int, int> &genes, map<int, int> &genesToPos) {
	int totalVertices = graph->getTotalVertices();
	for (int i = 0; i < totalVertices; ++i) {
		if (child[genesToPos[fromParent[position]]] == -1)
			return genesToPos[fromParent[position]];

		position = genesToPos[fromParent[position]];
	}
}

void GeneticAlg::mapCrossover(vector<int> &parent1, vector<int> &parent2)
{
	int totalVertices = graph->getTotalVertices();
	vector<int> child1, child2;
	map<int, int> genes1, genes2;
	map<int, int> genes1Pos, genes2Pos;

	for (int i = 0; i < totalVertices; i++) {	// Set parents genes visited to 0
		genes1[parent1[i]] = 0;
		genes2[parent2[i]] = 0;

		child1.push_back(-1);
		child2.push_back(-1);

		genes1Pos[i+1] = 0;
		genes2Pos[i+1] = 0;
	}

	for (int i = 0; i < totalVertices; i++) {	// Set parents genes position
		genes1Pos[parent1[i]] = i;
		genes2Pos[parent2[i]] = i;
	}

	int point1 = rand() % (totalVertices - 1) + 1;				// random number in [1,totalVertices]
	int point2 = rand() % (totalVertices - point1) + point1;	// random number in [point1,totalVertices - point1]
	adjustPonts(point1, point2, totalVertices);					// adjusts the points if they are equal

	// map crossover
	for (int i = point1; i <= point2; ++i) {	
		child1[i] = parent1[i];
		genes1[parent1[i]] = 1;
		
		child2[i] = parent2[i];
		genes2[parent2[i]] = 1;	
	}

	for (int i = point1; i < totalVertices; ++i) {
		if (genes1[parent2[i]] == 0) {		// if the gene is not used
			int pos = getAvailablePosition(i, parent2, child1, genes1, genes1Pos);
			child1[pos] = parent2[i];
			genes1[parent2[i]] = 1;
		}

		if (genes2[parent1[i]] == 0) {		// if the gene is not used
			int pos = getAvailablePosition(i, parent1, child2, genes2, genes2Pos);
			child2[pos] = parent1[i];
			genes2[parent1[i]] = 1;
		}
	}

	for (int i = 0; i < point1; ++i) {
		if (genes1[parent2[i]] == 0) {		// if the gene is not used
			int pos = getAvailablePosition(i, parent2, child1, genes1, genes1Pos);
			child1[pos] = parent2[i];
			genes1[parent2[i]] = 1;
		}

		if (genes2[parent1[i]] == 0) {		// if the gene is not used
			int pos = getAvailablePosition(i, parent1, child2, genes2, genes2Pos);
			child2[pos] = parent1[i];
			genes2[parent1[i]] = 1;
		}
	}


	mutate(child1, child2);
}

void GeneticAlg::reverseCrossover(vector<int>& parent1, vector<int>& parent2)
{
	int totalVertices = graph->getTotalVertices();
	vector<int> child1, child2;
	map<int, int> genes1, genes2;

	for (int i = 0; i < totalVertices; i++) {	// Set parents genes visited to 0
		genes1[parent1[i]] = 0;
		genes2[parent2[i]] = 0;
	}

	// generates random points
	int point1 = rand() % (totalVertices - 1) + 1;				// random number in [1,totalVertices]
	int point2 = rand() % (totalVertices - point1) + point1;	// random number in [point1,totalVertices - point1]

	adjustPonts(point1, point2, totalVertices);					// adjusts the points if they are equal

	// Generate childs
	for (int i = 0; i < point1; i++) {	
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
	
		genes1[parent1[i]] = 1;
		genes2[parent2[i]] = 1;
	}

	// Marks remaining genes visited
	for (int i = point2 + 1; i < totalVertices; i++) {
		genes1[parent1[i]] = 1;
		genes2[parent2[i]] = 1;
	}

	// map crossover
	for (int i = point2; i >= point1; i--) {
		if (genes1[parent2[i]] == 0) {	// if the gene is not used
			child1.push_back(parent2[i]);
			genes1[parent2[i]] = 1;
		}
		else {
			// if the gene already is used, chooses gene that is not used
			for (map<int, int>::iterator iter = genes1.begin(); iter != genes1.end(); ++iter) {
				if (iter->second == 0) {
					child1.push_back(iter->first);
					genes1[iter->first] = 1;
					break;
				}
			}
		}

		if (genes2[parent1[i]] == 0) {	 // if the gene is not used
			child2.push_back(parent1[i]);
			genes2[parent1[i]] = 1;
		}
		else {
			// if the gene already is used, chooses gene that is not used
			for (map<int, int>::iterator iter = genes2.begin(); iter != genes2.end(); ++iter) {
				if (iter->second == 0) {	// checks if is not used
					child2.push_back(iter->first);
					genes2[iter->first] = 1;
					break;
				}
			}
		}
	}

	// Insert remaining genes
	for (int i = point2 + 1; i < totalVertices; i++) {
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
	}

	mutate(child1, child2);
}

void GeneticAlg::run() {
	initPopulation();
		
	if (currentPopulationSize == 0)
		return;

	for (int i = 0; i < generations; ++i) {
		int crossParentSize = (rand() % currentPopulationSize + 1) / 2;
		for (int j = 0; j < crossParentSize; ++j) {
			int  oldPopulationSize = currentPopulationSize;

			if (currentPopulationSize >= 2) {	// Select two parents 
				if (currentPopulationSize == 2) {
					//reverseCrossover(population[0].first, population[1].first);
					mapCrossover(population[0].first, population[1].first);
				}
				else {
					int parent1, parent2;

					do {						// Select two random parents
						parent1 = rand() % currentPopulationSize;
						parent2 = rand() % currentPopulationSize;
					} while (parent1 == parent2);

					//reverseCrossover(population[parent1].first, population[parent2].first);
					mapCrossover(population[parent1].first, population[parent2].first);
				}

				int diff = currentPopulationSize - oldPopulationSize;

				if (diff == 2) {
					if (currentPopulationSize > populationSize) {	// Remove the two worst parents of the population		
						population.pop_back();
						population.pop_back();
						currentPopulationSize -= 2;
					}
				}
				else if (diff == 1) {
					if (currentPopulationSize > populationSize) {
						population.pop_back();						// Remove the worst parent of the population
						currentPopulationSize--;
					}
				}
			}
			else {
				//reverseCrossover(population[0].first, population[0].first);
				mapCrossover(population[0].first, population[0].first);

				if (currentPopulationSize > populationSize) {
					population.pop_back();
					currentPopulationSize--;
				}
			}
		}

		if (i == 10)
			showGeneration(i);
		else if (i == (generations / 4))
			showGeneration(i);
		else if (i == (generations / 2))
			showGeneration(i);
		else if (i == ( (3 * generations) / 4))
			showGeneration(i);
	}

	showGeneration(generations);

	printSolution();
}

void GeneticAlg::showGeneration(int generationNumber) const {
	int startVertex = graph->getStartVertex();
	int totalVertices = graph->getTotalVertices();
	cout << "\nGeneration: " << generationNumber << endl;

	const vector<int>& solution = population[0].first;
	for (int i = 0; i < totalVertices; i++)
		cout << solution[i] << " ";

	cout << startVertex << endl;
	cout << "Cost: " << population[0].second << endl;
	cout << "Population size: " << currentPopulationSize << endl;
}

void GeneticAlg::printSolution() const {
	int startVertex = graph->getStartVertex();
	int totalVertices = graph->getTotalVertices();
	cout << "\nBest solution:" << endl;

	const vector<int>& vec = population[0].first;
	for (int i = 0; i < totalVertices; i++)
		cout << vec[i] << " ";

	cout << startVertex << endl;
	cout << "Cost: " << population[0].second << endl;
}