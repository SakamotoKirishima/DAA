#include <vector>
#include <algorithm>
#include <iostream>

#include "Point.h"
#include "Step2.h"
#include "Step3.h"

using namespace std;

float getMedian(vector<Point> points) {
	sort(points.begin(), points.end(), compareX());
	float median;
	if(points.size() % 2 == 0) {
		median = (points.at(points.size()/2).getX() + points.at(points.size()/2 - 1).getX())/2;
	} else median = points.at(points.size()/2).getX();

	return median;
}

pair< vector<Point>, vector<Point> > getSets(vector<Point> points) {
	return getSets(points, getMedian(points));
}

pair< vector<Point>, vector<Point> > getSets(vector<Point> points, Line joiner) {
	Colour red(1.0, 0.0, 0.0);

	vector<Point> left, right;
	left.push_back(joiner.getp1());
	right.push_back(joiner.getp2());

	for(int i = 0; i < points.size(); i++) {
		if(points.at(i).getX() < joiner.getp1().getX()) left.push_back(points.at(i));
		else if(points.at(i).getX() > joiner.getp2().getX()) right.push_back(points.at(i));
	}

	pair< vector<Point>, vector<Point> > returnValue;
	returnValue.first = left;
	returnValue.second = right;

	return returnValue;

}

pair< vector<Point>, vector<Point> > getSets(vector<Point> points, float median) {
	Colour red(1.0, 0.0, 0.0);

	vector<Point> left, right;

	for(int i = 0; i < points.size(); i++) {
		if(points.at(i).getX() <= median) left.push_back(points.at(i));
		else right.push_back(points.at(i));
	}

	pair< vector<Point>, vector<Point> > returnValue;
	returnValue.first = left;
	returnValue.second = right;

	return returnValue;

}