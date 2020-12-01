#pragma once
#include "Graph.h"

Graph* getGraph1(int startVertex = 0) {
	Graph * graph1 = new Graph(5, startVertex);
	
	graph1->addEdge(0, 1, 1);
	graph1->addEdge(1, 0, 1);
	graph1->addEdge(0, 2, 3);
	graph1->addEdge(2, 0, 3);
	graph1->addEdge(0, 3, 4);
	graph1->addEdge(3, 0, 4);
	graph1->addEdge(0, 4, 5);
	graph1->addEdge(4, 0, 5);

	graph1->addEdge(1, 2, 1);
	graph1->addEdge(2, 1, 1);
	graph1->addEdge(1, 3, 4);
	graph1->addEdge(3, 1, 4);
	graph1->addEdge(1, 4, 8);
	graph1->addEdge(4, 1, 8);

	graph1->addEdge(2, 3, 5);
	graph1->addEdge(3, 2, 5);
	graph1->addEdge(2, 4, 1);
	graph1->addEdge(4, 2, 1);

	graph1->addEdge(3, 4, 2);
	graph1->addEdge(4, 3, 2);

	return graph1;
}

Graph* getGraph2(int startVertex = 0) {
	Graph * graph2 = new Graph(4, startVertex);
	
	graph2->addEdge(0, 1, 2);
	graph2->addEdge(1, 0, 2);
	graph2->addEdge(0, 2, 6);
	graph2->addEdge(2, 0, 6);
	graph2->addEdge(0, 3, 3);
	graph2->addEdge(3, 0, 3);

	graph2->addEdge(1, 3, 7);
	graph2->addEdge(3, 1, 7);
	graph2->addEdge(1, 2, 4);
	graph2->addEdge(2, 1, 4);

	graph2->addEdge(2, 3, 2);
	graph2->addEdge(3, 2, 2);

	return graph2;
}

Graph* getGraph3(int startVertex = 0) {
	Graph * graph3 = new Graph(4, startVertex);

	graph3->addEdge(0, 1, 10);
	graph3->addEdge(1, 0, 10);
	graph3->addEdge(0, 2, 15);
	graph3->addEdge(2, 0, 15);
	graph3->addEdge(0, 3, 20);
	graph3->addEdge(3, 0, 20);

	graph3->addEdge(1, 2, 35);
	graph3->addEdge(2, 1, 35);
	graph3->addEdge(1, 3, 25);
	graph3->addEdge(3, 1, 25);

	graph3->addEdge(2, 3, 30);
	graph3->addEdge(3, 2, 30);

	return graph3;
}

Graph* getGraph4(int startVertex = 0) {
	Graph * graph4 = new Graph(13, startVertex);

	graph4->addEdge(0, 1, 5);
	graph4->addEdge(0, 4, 16);
	graph4->addEdge(0, 5, 45);

	graph4->addEdge(1, 0, 5);
	graph4->addEdge(1, 2, 12);
	graph4->addEdge(1, 3, 43);

	graph4->addEdge(2, 1, 12);
	graph4->addEdge(2, 11, 8);
	graph4->addEdge(2, 5, 38);
	graph4->addEdge(2, 4, 22);
	graph4->addEdge(2, 3, 12);

	graph4->addEdge(3, 1, 44);
	graph4->addEdge(3, 2, 12);
	graph4->addEdge(3, 5, 69);
	graph4->addEdge(3, 4, 66);

	graph4->addEdge(4, 0, 16);
	graph4->addEdge(4, 3, 66);
	graph4->addEdge(4, 9, 8);
	graph4->addEdge(4, 2, 22);

	graph4->addEdge(5, 0, 45);
	graph4->addEdge(5, 3, 69);
	graph4->addEdge(5, 1, 43);
	graph4->addEdge(5, 2, 38);
	graph4->addEdge(5, 11, 18);

	graph4->addEdge(6, 7, 16);
	graph4->addEdge(6, 12, 64);
	graph4->addEdge(6, 9, 41);
	graph4->addEdge(6, 11, 58);

	graph4->addEdge(7, 6, 16);
	graph4->addEdge(7, 12, 37);
	graph4->addEdge(7, 8, 23);

	graph4->addEdge(8, 7, 23);
	graph4->addEdge(8, 12, 48);
	graph4->addEdge(8, 11, 35);
	graph4->addEdge(8, 10, 10);

	graph4->addEdge(9, 4, 8);
	graph4->addEdge(9, 6, 41);
	graph4->addEdge(9, 12, 45);
	graph4->addEdge(9, 10, 9);

	graph4->addEdge(10, 9, 9);
	graph4->addEdge(10, 8, 10);

	graph4->addEdge(11, 2, 8);
	graph4->addEdge(11, 5, 18);
	graph4->addEdge(11, 8, 35);
	graph4->addEdge(11, 12, 68);
	graph4->addEdge(11, 6, 58);

	graph4->addEdge(12, 6, 64);
	graph4->addEdge(12, 11, 68);
	graph4->addEdge(12, 9, 45);
	graph4->addEdge(12, 8, 48);
	graph4->addEdge(12, 7, 37);

	/*cout << graph->existsEdge(0, 4) << endl;
	cout << graph->existsEdge(4, 9) << endl;
	cout << graph->existsEdge(9, 10) << endl;
	cout << graph->existsEdge(10, 8) << endl;
	cout << graph->existsEdge(8, 7) << endl;
	cout << graph->existsEdge(7, 6) << endl;
	cout << graph->existsEdge(6, 12) << endl;
	cout << graph->existsEdge(12, 11) << endl;
	cout << graph->existsEdge(11, 2) << endl;
	cout << graph->existsEdge(2, 5) << endl;
	cout << graph->existsEdge(5, 3) << endl;
	cout << graph->existsEdge(3, 1) << endl;
	cout << graph->existsEdge(1, 0) << endl;*/

	return graph4;
}

Graph* getRandomGraph() {
	int n;
	cout << "N: ";
	cin >> n;
	Graph* randomGraph = new Graph(n, 0);
	randomGraph->generateRandomGraph();

	return randomGraph;
}

