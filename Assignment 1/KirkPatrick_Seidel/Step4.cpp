#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

#include "Point.h"
#include "Colour.h"
#include "Step2.h"
#include "Step3.h"
#include "Step4.h"

using namespace std;

/**
*   Compare given floats (with precision error acceptance)
*
*  	@param float x: first float value
*	@param float y: second float value
*	@return bool: true if float values are equal till 6th decimal place
*/
inline bool isEqual(float x, float y)
{
  const float epsilon = 0.000001/* some small number such as 1e-5 */;
	return abs(x - y) <= epsilon;
}

/**
*   Check if slope of line 1 is less than slope of line 2
*
*	Used for sorting lines based on their slope
*  	@param Line l1: first line
*	@param Line l2: second line
*	@return bool: true if slope of l1 is less than slope of l2
*/
struct compareSlopes {
	inline bool operator () (Line l1, Line l2) {
		return (getSlope(l1) < getSlope(l2));
	}
};

/**
*   Get median value of slopes of the given lines
*
*  	@param vector<Line> lines: Set of lines
*	@return float: Median slope of given lines
*/
float getMedianSlope(vector<Line> randomLines) {
	sort(randomLines.begin(), randomLines.end(), compareSlopes());
	if(randomLines.size() % 2 == 0) 
		return ( getSlope(randomLines.at(randomLines.size()/2)) 
			+ getSlope(randomLines.at(randomLines.size()/2 - 1)) )/2.0f;
	else
		return getSlope(randomLines.at(randomLines.size()/2));
}

/**
*   Get points with max constant value
*
*	returns set of points with max value of y-Mx
*	where is M is given as medianSlope
*
*  	@param vector<Point> points: Set of points
*	@return vector<Point>: Points with maximum constant value
*/
vector<Point> getPointsWithMaxC(vector<Point> points, float medianSlope) {
	vector <Point> max;
	for(Point point : points) {
		float c1 = 0, c2 = 0;
		if(max.size() == 0) max.push_back(point);
		else {
			c1 = point.getY() - medianSlope*point.getX();
			c2 = max.at(0).getY() - medianSlope*max.at(0).getX();
			if(isEqual(c1, c2)) {
				max.push_back(point);
			} else if(c2 < c1) {
				max.clear();
				max.push_back(point);
			}
		}
	}
	return max;
}

vector<Point> findBridge(vector<Point> points, float median) {
	Colour blue(0,0,1);

	//Stores the candidates for the bridge
	vector<Point> candidates = points;
	//Store the randomly generated lines
	vector<Line> randomLines;

	//Generate random lines (if last point remains, it is a candidate)
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

	//If a vertical line is encountered, insert higher end in candidates
	//Remove the vertical line (avoids getting a nan when calculating slope)
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

	float medianSlope = getMedianSlope(randomLines);

	//Find point(s) with max y-Mx where M is median slope
	vector<Point> max = getPointsWithMaxC(points, medianSlope);

	//Sort max based on X coordinate of the points
	sort(max.begin(), max.end(), compareX());
	
	//Add points to candidates as per the algorithm
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
	}

	if(candidates.size() == 2)
		return candidates;
	else
		return findBridge(candidates, median);

}