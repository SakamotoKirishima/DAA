#ifndef _STEP3_
#define _STEP3_

#include <vector>
#include <utility>

#include "Point.h"

using namespace std;

/**
*   Get sets of points in the left and right side of the given line segment
*
*	@param vector<Point> points: set of all points
*	@param Line joiner: Bridge line
*	@return pair< vector<Point>, vector<Point> >: first contains points in left
*	and second, points in right
*/
pair< vector<Point>, vector<Point> > getSets(vector<Point> points, Line joiner);

/**
*   Get sets of points in the left and right side of the given median
*
*	@param vector<Point> points: set of all points
*	@param float median: The median value of all X coordinates of the point set
*	@return pair< vector<Point>, vector<Point> >: first contains points in left
*	and second, points in right
*/
pair< vector<Point>, vector<Point> > getSets(vector<Point> points, float median);

/**
*   Get median line of given set of points
*
*	@param vector<Point> points: set of all points
*	@return float: median X coordinate
*/
float getMedian(vector<Point> points);

#endif