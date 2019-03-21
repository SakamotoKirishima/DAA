#ifndef _STEP2_
#define _STEP2_

#include <vector>
#include "Line.h"
#include "Point.h"

using namespace std;

struct compareX {
	inline bool operator () (Point p1, Point p2) {
		return (p1.getX() < p2.getX());
	}
};

float getSlope(Point p1, Point p2);
float getSlope(Line l);
Line getDivider(vector<Point> points);
vector<Point> getUpperHull(vector<Point> points);

#endif