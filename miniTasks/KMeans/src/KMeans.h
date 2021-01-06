#pragma once
#include <ctime> 
#include <vector>
#include <fstream>
#include <iostream>
#include "Point.h"
#include "BitmapImageh.h"

const double VERY_SMALL_NUMBER = 0.000001;

class KMeans
{
private:
	int K;
	int size;
	double shifting;
	int multiply;
	vector<Point> points;
	vector<Point> centroids;

	void initPoints(Point points[]);
	void initCentroids();
	void assingPointsToCluster();
	void assingNewCentroids(int &isFinish);
	void writeToFile(const char* toFilename);

public:
	KMeans(int K, Point points[], int size, double shifting, int multiply);
	void run(const char* toFilename);
};

