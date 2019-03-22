#ifndef _STEP4_
#define _STEP4_

#include <vector>
#include <utility>

#include "Point.h"

using namespace std;

/**
*   Find bridge, given a set of points and a median value
*
*	Follows KirkPatrick Seidel algorithm
*	@see Page 6 http://graphics.stanford.edu/courses/cs268-16-fall/Notes/KirkSeidel.pdf
*
*  	@param vector<Point> points: Set of points
*	@param float median: Median value of the X-coordinates of the given points
*	@return vector<Point>: Two Points forming the bridge
*/
vector<Point> findBridge(vector<Point> points, float median);

#endif