#ifndef _STEP4_
#define _STEP4_

#include <vector>
#include <utility>

#include "Point.h"

using namespace std;

vector<Point> findBridgeUtil(vector<Point> points, float median);
pair<Point, Point> findBridge(vector<Point> points);

#endif