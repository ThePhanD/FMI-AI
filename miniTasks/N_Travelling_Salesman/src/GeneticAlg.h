#pragma once
#include "Graph.h"
#include <set>

using graphPair = std::pair<std::vector<int>, int>;

// sort edges with weight
struct sortByWeight
{
	bool operator()(const graphPair& gp1, const graphPair& gp2)
	{
		return gp1.second < gp2.second;
	}
};

class GeneticAlg
{
private:
	Graph* graph;
	vector<graphPair> population;

	int populationSize;
	int currentPopulationSize;
	int generations;
	int mutationRate;

	void initPopulation();
	void insertByBinarySearch(vector<int> &child, int totalCost);
	void mutate(vector<int> child1, vector<int> child2);
	bool existsGene(const vector<int> &gene);
	int	getAvailablePosition(int startPosition, vector<int> &parent, vector<int> child, map<int, int> &genes, map<int, int> &genes1Pos);
	void mapCrossover(vector<int>& parent1, vector<int>& parent2);
	void reverseCrossover(vector<int> &parent1, vector<int> &parent2);
	void printSolution() const;
	void showGeneration(int generationNumber) const;

public:
	GeneticAlg(Graph* graph, int populationSize, int generations, int mutationRate);
	
	void run();
	int isValidSolution(vector<int> &solution);		
};


