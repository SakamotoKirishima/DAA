#include <vector>
#include <algorithm>

#include "Point.h"
#include "Step3.h"

using namespace std;

struct compareX {
	inline bool operator () (Point p1, Point p2) {
		return (p1.getX() < p2.getX());
	}
};

float getMedian(vector<Point> points) {
	sort(points.begin(), points.end(), compareX());
	return points.at(points.size()/2).getX();
}

pair< vector<Point>, vector<Point> > getSets(vector<Point> points) {
	Colour red(1.0, 0.0, 0.0);

	vector<Point> left, right;
	sort(points.begin(), points.end(), compareX());

	for(int i = 0; i < (points.size()/2); i++) {
		left.push_back(points.at(i));
	}
	for(int i = (points.size()/2) + 1; i < points.size(); i++) {
		Point point = points.at(i);
		point.setColour(red);
		right.push_back(point);
	}

	pair< vector<Point>, vector<Point> > returnValue;
	returnValue.first = left;
	returnValue.second = right;

	return returnValue;

}