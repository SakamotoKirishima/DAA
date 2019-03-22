#include <vector>
#include <algorithm>

#include "Point.h"
#include "Line.h"
#include "Step2.h"

using namespace std;

float getSlope(Point p1, Point p2) {
    return (p2.getY() - p1.getY())/(p2.getX() - p1.getX());
}
float getSlope(Line l) {
    return (l.getp2().getY() - l.getp1().getY())/(l.getp2().getX() - l.getp1().getX());
}

Line getDivider(vector<Point> points) {
	Colour white(1.0, 1.0, 1.0);
	
	sort(points.begin(), points.end(), compareX());
	
	Line l(points.at(0), points.at(points.size() - 1), white);
	return l;
}

vector<Point> getUpperHalf(vector<Point> points) {
	Colour green(0,1,0);

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
