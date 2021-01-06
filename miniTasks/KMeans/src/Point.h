#pragma once

using namespace std;

const double MAX_INFINITY = 1000000;
const double ZERO = 0.0;
const int DEFAULT_CLUSTER = -1;

struct Point {
	double x, y;     
	int cluster;     
	double minDist;

	Point() : x(ZERO), y(ZERO), cluster(DEFAULT_CLUSTER), minDist(MAX_INFINITY) {}
	Point(double x, double y) : x(x), y(y), cluster(DEFAULT_CLUSTER), minDist(MAX_INFINITY) {}

	double distance(Point p) {
		return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
	}
};
