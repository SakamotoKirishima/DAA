#include <vector>

#include "Point.h"
#include "Line.h"
#include "Step2.h"

using namespace std;

Colour green(0.0, 1.0, 0.0);

float getSlope(Point p1, Point p2) {
    return (p2.getY() - p1.getY())/(p2.getX() - p1.getX());
}
float getSlope(Line l) {
    return (l.getp2().getY() - l.getp1().getY())/(l.getp2().getX() - l.getp1().getX());
}

Line getDivider(vector<Point> points) {
	Colour colour(1, 1, 1);
	Point xMin(1.0f, 0.0f, colour);
	Point xMax(-1.0f, 0.0f, colour);

	for(Point point : points) {
		if(point.getX() > xMax.getX() ) xMax = point;
		else if(point.getX() < xMin.getX() ) xMin = point;
	}
	Line l(xMin, xMax, colour);
	return l;
}

vector<Point> getUpperHull(vector<Point> points) {
	Line l = getDivider(points);
	Point xMin = l.getp1();
	Point xMax = l.getp2();
	float slope = getSlope(l);

	vector<Point> newPoints;
	int count = 0;
	for(Point point : points) {
		float slope1 = getSlope(xMin, point);

		if(slope1 >= slope || point == xMin){
			point.setColour(green);
			newPoints.push_back(point);
		}
	}
	return newPoints;
}
