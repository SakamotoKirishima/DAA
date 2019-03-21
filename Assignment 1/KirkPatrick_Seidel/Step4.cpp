#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "Point.h"
#include "Step2.h"
#include "Step3.h"
#include "Step4.h"

using namespace std;

Colour blue(0.0, 0.0, 1.0);

struct compareSlopes {
	inline bool operator () (Line l1, Line l2) {
		return (getSlope(l1) < getSlope(l2));
	}
};

vector<Point> findBridgeUtil(vector<Point> points, float median) {

	vector<Point> candidates = points;
	vector<Line> randomLines;
	while(candidates.size() > 1){
		int random = rand() % candidates.size();
		Point p1 = candidates.at(random);
		candidates.erase(candidates.begin() + random);

		random = rand() % candidates.size();
		Point p2 = candidates.at(random);
		candidates.erase(candidates.begin() + random);
		
		if(p1.getX() <= p2.getX()){
			Line l(p1, p2, blue);
			randomLines.push_back(l);	
		} else {
			Line l(p2, p1, blue);
			randomLines.push_back(l);
		}
	}

	for(int i = 0;i < randomLines.size(); i++) {
		Line l = randomLines.at(i);
		if(l.getp1().getX() == l.getp2().getX()) {
			if(l.getp1().getY() > l.getp2().getY())
				candidates.push_back(l.getp1());
			else
				candidates.push_back(l.getp2());

			randomLines.erase(randomLines.begin() + i);
		}
	}

	if(randomLines.size() == 0) {
		return candidates;
	}

	sort(randomLines.begin(), randomLines.end(), compareSlopes());
	float medianSlope = 0.0f;
	if(randomLines.size() % 2 == 0) {
		medianSlope = ( getSlope(randomLines.at(randomLines.size()/2)) + getSlope(randomLines.at(randomLines.size()/2 - 1)) )/2.0f;
	}
	else{ 
		medianSlope = getSlope(randomLines.at(randomLines.size()/2));
	}

	vector <Point> max;
	for(Point point : points) {
		if(max.size() == 0) max.push_back(point);
		else {
			float c1 = point.getY() - medianSlope*point.getX();
			float c2 = max.at(0).getY() - medianSlope*max.at(0).getX();
			if(c2 < c1) {
				max.clear();
				max.push_back(point);
			} else if(c2 == c1) {
				max.push_back(point);
			}
		}
	}

	sort(max.begin(), max.end(), compareX());
	
	if(max.at(0).getX() <= median && max.at(max.size() - 1).getX() > median) {
		candidates.clear();
		candidates.push_back(max.at(0));
		candidates.push_back(max.at(max.size() - 1));
		
	} else if(max.at(max.size() - 1).getX() <= median) {
		for(int i = 0; i < randomLines.size(); i++) {
			if(getSlope(randomLines.at(i)) < medianSlope) {
				candidates.push_back(randomLines.at(i).getp1());
				candidates.push_back(randomLines.at(i).getp2());
			} else candidates.push_back(randomLines.at(i).getp2());
		}

	} else if(max.at(0).getX() > median) {
		for(int i = 0; i < randomLines.size(); i++) {
			if(getSlope(randomLines.at(i)) <= medianSlope) candidates.push_back(randomLines.at(i).getp1());
			else {
				candidates.push_back(randomLines.at(i).getp1());
				candidates.push_back(randomLines.at(i).getp2());
			}
		}
	} else {
		cout << "It shouldn't have gone here... Check code again!";
	}

	if(candidates.size() == 2) return candidates;
	else return findBridgeUtil(candidates, median);

}

pair<Point, Point> findBridge(vector<Point> points) {
	float median = getMedian(points);
	points = findBridgeUtil(points, median);

	pair<Point, Point> bridge;
	bridge.first = points.at(0);
	bridge.second = points.at(1);
	return bridge;

}