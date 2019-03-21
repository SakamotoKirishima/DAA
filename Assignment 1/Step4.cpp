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

pair< vector<Line>, vector<Point> > findBridgeUtil(vector<Point> points, float median) {
	// if (points.size() == 2){
	// 	pair< vector<Line>, vector<Point> > result;
	// 	vector<Line> lines;
	// 	Line l(points.at(0), points.at(1), blue);
	// 	lines.push_back(l);
	// 	result.first = lines;
	// 	result.second = points;	
	// 	return result;
	// }
	vector<Point> candidates = points;
	vector<Line> randomLines;
	// srand (static_cast <unsigned> (time(NULL)));
	while(candidates.size() > 1){
		int random = rand() % candidates.size();
		Point p1 = candidates.at(random);
		candidates.erase(candidates.begin() + random);

		random = rand() % candidates.size();
		Point p2 = candidates.at(random);
		candidates.erase(candidates.begin() + random);
		
		Line l(p1, p2, blue);
		randomLines.push_back(l);
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
		pair< vector<Line>, vector<Point> > result;
		result.first = randomLines;
		result.second = candidates;
		return result;
	}

	sort(randomLines.begin(), randomLines.end(), compareSlopes());
	float medianSlope = 0.0f;
	if(randomLines.size() % 2 == 0) {
		cout << "Check2if" << randomLines.size() << '\t';
		median = ( getSlope(randomLines.at(randomLines.size()/2)) + getSlope(randomLines.at(randomLines.size()/2 - 1)) )/2.0f;
	}
	else{ 
		cout << "Check2else\t";
		medianSlope = getSlope(randomLines.at(randomLines.size()/2));
	}

	cout << "Check3\t";

	vector <Point> max;
	for(Point point : points) {
		if(max.size() == 0) max.push_back(point);
		else {
			float c1 = point.getY() - medianSlope*point.getX();
			float c2 = max.at(0).getY() - medianSlope*max.at(0).getX();
			if(c2 < c1) {
				cout << "l";
				max.clear();
				max.push_back(point);
			} else if(c2 == c1) {
				cout << "e";
				max.push_back(point);
			}
		}
		cout << "Count:" << max.size() << '\t';
	}

	cout << "Check4\t";

	sort(max.begin(), max.end(), compareX());

	if(max.size() == 0) {
		cout << "Error!\n";
	}
	
	if(max.at(0).getX() <= median && max.at(max.size() - 1).getX() > median) {
		cout << "one\t";
		candidates.clear();
		candidates.push_back(max.at(0));
		candidates.push_back(max.at(max.size() - 1));

		randomLines.clear();
		Line l(candidates.at(0), candidates.at(1), blue);
		randomLines.push_back(l);
		
	} else if(max.at(max.size() - 1).getX() <= median) {
		cout << "two\t";

		for(int i = 0; i < randomLines.size(); i++) {
			if(getSlope(randomLines.at(i)) < medianSlope) {
				candidates.push_back(randomLines.at(i).getp1());
				candidates.push_back(randomLines.at(i).getp2());
			} else candidates.push_back(randomLines.at(i).getp2());
		}

	} else if(max.at(0).getX() > median) {
		cout << "three\t";

		for(int i = 0; i < randomLines.size(); i++) {
			if(getSlope(randomLines.at(i)) <= medianSlope) candidates.push_back(randomLines.at(i).getp1());
			else {
				candidates.push_back(randomLines.at(i).getp1());
				candidates.push_back(randomLines.at(i).getp2());
			}
		}
	} else {
		cout << "error!";
	}

	
	pair< vector<Line>, vector<Point> > returnValue;
	returnValue.first = randomLines;
	returnValue.second = candidates;
	return returnValue;
}

pair<Point, Point> findBridge(vector<Point> points, float median) {
	while(points.size() > 2) {
		points = findBridgeUtil(points, median).second;
	}

	pair<Point, Point> bridge;
	bridge.first = points.at(0);
	bridge.second = points.at(1);
	return bridge;

}