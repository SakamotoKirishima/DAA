#include <cstdlib>
#include <ctime>
#include <vector>
#include <climits>
#include <iostream>

#include "Step1.h"
#include "Point.h"
#include "Colour.h"

using namespace std;

/**
*   Checks if Upper half has 5 points
*
*	@return bool: true if upper half has 5 points
*/
bool checkUpperHalf(vector<Point> points);

/**
*   Random point generator
*
*	Generates random points in the coordinate range of -1 to 1
*	Also checks if there are more than 5 points in the upper half (for demo)
*	else adds more points
*
*	@return vector<Point>: Generated random points
*/
vector<Point> generatePoints(vector<Point> points) {
	Colour white(1.0, 1.0, 1.0);

	for(int i = 0;i < 5;i++){
		float x = -1.0f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2);
		float y = -1.0f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2);
		Point p(x, y, white);
		points.push_back(p);
	}

	//check if upper hull has 5 points
	if(checkUpperHalf(points)) return points;
	else return generatePoints(points);

}

vector<Point> generatePoints() {
	srand (static_cast <unsigned> (time(NULL)));
	vector<Point> points;
	points = generatePoints(points);
	cout << "Generated points (Step 1):\n";
	for(Point point : points) {
		cout << point.getX() << "\t" << point.getY() << '\n';
	}
	cout << '\n';	
	return points;
}

bool checkUpperHalf(vector<Point> points) {
	Colour white(1.0, 1.0, 1.0);
	
	Point xMin(1.0f, 0.0f, white);
	Point xMax(-1.0f, 0.0f, white);

	for(Point point : points) {
		if(point.getX() >= xMax.getX() ) xMax = point;
		else if(point.getX() <= xMin.getX() ) xMin = point;
	}

	float slopeOfDivider = (xMax.getY() - xMin.getY() )/(xMax.getX() - xMin.getX() );
	int pointsInUpperHalf = 0;

	for(Point point : points) {
		if((point.getY() - xMin.getY() )/(point.getX() - xMin.getX() ) > slopeOfDivider)
			pointsInUpperHalf++;
	}

	return pointsInUpperHalf > 5;

}