#include "Graph.h"

Graph::Graph(int totalVertices, int startVertex) : totalVertices(totalVertices), startVertex(startVertex), totalEdges(0) {
	adj = new list<int>[totalVertices];
}

Graph::~Graph() {
	delete[] adj;
}

bool Graph::isSafe(int dest, vector<int> path, int pos) {
	if (existsEdge(path[pos - 1], dest) == -1)
		return false;

	for (int i = 0; i < pos; ++i) {
		if (path[i] == dest)
			return false;
	}

	return true;
}

bool Graph::hasCycle(vector<int> &path, int pos) {

	if (pos == totalVertices) {
		if (existsEdge(path[pos - 1], path[startVertex]) != -1)
			return true;
		else 
			return false;
	}
	
	for (int i = 1; i < totalVertices; ++i) {
		if (isSafe(i, path, pos)) {
			path[pos] = i;

			if (hasCycle(path, pos + 1))
				return true;

			path[pos] = -1;
		}
	}

	return false;
}

bool Graph::isCyclic(vector<int> &path) {
	path[0] = startVertex;
	if (hasCycle(path, 1)) {
		return true;
	}

	return false;
}

void Graph::generateRandomGraph()
{
	vector<int> vertices;

	for (int i = 0; i < totalVertices; i++)
		vertices.push_back(i);

	int weight;
	for (int src = 0; src < totalVertices - 1; ++src){
		for (int dest = src + 1; dest < totalVertices; ++dest) {
			weight = rand() % totalVertices + 1;					// random weight in range [1,totalVectices]
			addEdge(vertices[src], vertices[dest], weight);
			addEdge(vertices[dest], vertices[src], weight);
		}
	}
}

void Graph::addEdge(int a, int b, int weight)
{
	edges[make_pair(a, b)] = weight;
	adj[a].push_back(b);
}

void Graph::printInfo()
{
	cout << "Graph info:" << endl;
	cout << "Number of vertices: " << totalVertices << endl;
	cout << "Number of edges: " << edges.size() << endl;
}

void Graph::printGraph()
{
	map<pair<int, int>, int>::iterator iter;
	for (iter = edges.begin(); iter != edges.end(); ++iter)
		cout << "[" << iter->first.first << ", " << iter->first.second << "]" << " = " << iter->second << endl;
}


int Graph::existsEdge(int src, int dest)
{
	map<pair<int, int>, int>::iterator iter = edges.find(make_pair(src, dest));

	if (iter != edges.end())
		return iter->second; // returns weight
	return -1;
}

int Graph::getTotalVertices() const {
	return totalVertices;
}

int Graph::getStartVertex() const {
	return startVertex;
}