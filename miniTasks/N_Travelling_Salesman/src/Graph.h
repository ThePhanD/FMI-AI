#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <limits.h>
#include <list>
using namespace std;

class Graph
{
private:
	int totalVertices;						
	int totalEdges;						
	int startVertex;					
	map<pair<int, int>, int> edges; 
	list<int>* adj;

	bool isSafe(int i, vector<int> path, int pos);
	bool hasCycle(vector<int> &path, int pos);

public:

	Graph(int totalVertices, int startVertex);
	~Graph();

	void generateRandomGraph();
	void addEdge(int a, int b, int weight);
	int existsEdge(int src, int dest);
	int getTotalVertices() const;
	int getStartVertex() const;
	bool isCyclic(vector<int> &path);

	void printGraph();
	void printInfo();

};

