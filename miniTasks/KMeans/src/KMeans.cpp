#include "KMeans.h"

void KMeans::initPoints(Point points[]) {
	for (int i = 0; i < size; ++i)
		this->points.push_back(points[i]);
}

void  KMeans::initCentroids() {
	srand((unsigned)time(0));  
	for (int i = 0; i < K; ++i) {
		centroids.push_back(points.at(rand() % size));
	}
}

void KMeans::assingPointsToCluster() {
	for (vector<Point>::iterator c = begin(centroids); c != end(centroids); ++c) {
		int clusterId = c - begin(centroids);

		for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
			Point p = *it;
			double dist = c->distance(p);
			if (dist < p.minDist) {
				p.minDist = dist;
				p.cluster = clusterId;
			}

			*it = p;
		}
	}
}

KMeans::KMeans(int K, Point points[], int size, double shifting, int multiply) : K(K), size(size), shifting(shifting), multiply(multiply) {
	initPoints(points);
	initCentroids();
}

void KMeans::assingNewCentroids(int &isFinish) {
	vector<int> nPoints;
	vector<double> sumX, sumY;

	for (int i = 0; i < K; ++i) {
		nPoints.push_back(0);
		sumX.push_back(0.0);
		sumY.push_back(0.0);
	}

	// Iterate over points to append data to centroids
	for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
		int clusterId = it->cluster;
		nPoints[clusterId] += 1;
		sumX[clusterId] += it->x;
		sumY[clusterId] += it->y;

		it->minDist = MAX_INFINITY;  // reset distance
	}

	// Compute the new centroids
	for (vector<Point>::iterator c = begin(centroids); c != end(centroids); ++c) {
		int clusterId = c - begin(centroids);
		double newX = sumX[clusterId] / nPoints[clusterId];
		double newY = sumY[clusterId] / nPoints[clusterId];

		Point newCentroid(newX, newY);
		if (c->distance(newCentroid) < VERY_SMALL_NUMBER) {
			isFinish++;
		}
		else {
			c->x = newX;
			c->y = newY;
		}

	}
}

void KMeans::run(const char* toFilename) {
	
	int isFinish = 0;
	int iteration = 0;
	int maxIteration = 100;
	while (isFinish == (K - 1) || iteration < maxIteration) {
		assingPointsToCluster();
		assingNewCentroids(isFinish);
		iteration++;
	}

	writeToFile(toFilename);
}

void KMeans::writeToFile(const char* toFilename) {
	const int canvas_width = 1400;
	const int canvas_height = 1200;
	const double radius = (std::min(canvas_width, canvas_height) / 2.0) - 5.0;
	const double spread = radius / std::sqrt(size);
	const double p_radius = std::floor(spread / 7.0);

	cartesian_canvas canvas(canvas_width, canvas_height);

	for (Point point : points) {

		const double x = (point.x + shifting) * multiply;
		const double y = (point.y + shifting) * multiply;
		double clusterId = (double)point.cluster + 1;

	
		canvas.pen_color(hsv_colormap[static_cast<std::size_t>(1000.0 * (clusterId / centroids.size()))]);
		canvas.fill_circle(x, y, p_radius);
	}

	canvas.image().save_image(toFilename);

}