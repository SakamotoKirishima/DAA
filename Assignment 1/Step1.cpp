#include <cstdlib>
#include <ctime>
#include <vector>
#include <climits>
#include <iostream>

#include "Step1.h"
#include "Point.h"
#include "Colour.h"

using namespace std;

Colour colour(1.0, 1.0, 1.0);

bool checkUpperHull(vector<Point> points);

vector<Point> generatePoints(vector<Point> points) {

	for(int i = 0;i < 5;i++){
		float x = -1.0f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2);
		float y = -1.0f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2);
		Point p(x, y, colour);
		points.push_back(p);
	}
	if(checkUpperHull(points)) return points;
	else return generatePoints(points);

}

vector<Point> generatePoints() {
	srand (static_cast <unsigned> (time(NULL)));
	vector<Point> points;
	points = generatePoints(points);
	//Test code (print points)
	// for(Point point : points) {
	// 	cout << point.getX() << '\t' << point.getY() << '\n';
	// }
	return points;
}

bool checkUpperHull(vector<Point> points) {
	Point xMin(1.0, 0, colour);
	Point xMax(-1.0, 0, colour);

	for(Point point : points) {
		if(point.getX() >= xMax.getX() ) xMax = point;
		else if(point.getY() <= xMin.getX() ) xMin = point;
	}

	float slopeOfDivider = (xMax.getY() - xMin.getY() )/(xMax.getX() - xMin.getX() );
	int pointsInUpperHull = 0;

	for(Point point : points) {
		if((point.getY() - xMin.getY() )/(point.getX() - xMin.getX() ) > slopeOfDivider)
			pointsInUpperHull++;
	}

	return pointsInUpperHull > 5;

}