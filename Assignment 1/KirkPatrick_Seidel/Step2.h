#ifndef _STEP2_
#define _STEP2_

#include <vector>
#include "Line.h"
#include "Point.h"

using namespace std;

/**
*   Compare X coordinates of the point
*
*	Used for sorting points from left to right
*
*	@param Point p1: first point
*	@param Point p2: second point
*	@return true: p1.x < p2.x
*/
struct compareX {
	inline bool operator () (Point p1, Point p2) {
		return (p1.getX() < p2.getX());
	}
};

/**
*   Get slope of line formed by joining given 2 points
*
*	@param Point p1: first point
*	@param Point p2: second point
*	@return float: slope of the line
*/
float getSlope(Point p1, Point p2);

/**
*   Get slope of given line
*
*	@param Line l: line to find the slope of
*	@return float: slope of the line
*/
float getSlope(Line l);

/**
*   Get line that divides upper half and lower half
*
*	Used only in visualisation
*
*	@param vector<Point> points: set of points
*	@return Line: Line which divides the points to upper and lower halves
*/
Line getDivider(vector<Point> points);

/**
*   Get points in upper half
*
*	@param vector<Point> points: set of all points
*	@return vector<Point>: set of points in upper half
*/
vector<Point> getUpperHalf(vector<Point> points);

#endif