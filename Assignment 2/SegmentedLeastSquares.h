#ifndef _SEGMENTEDLEASTSQUARES_
#define _SEGMENTEDLEASTSQUARES_
#include<vector>
#include"Line.h"
#include"Point.h"
std::vector<Line> getSegments(std::vector<Point> points, double cost);
#endif