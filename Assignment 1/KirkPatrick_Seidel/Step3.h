#ifndef _STEP3_
#define _STEP3_

#include <vector>
#include <utility>

#include "Point.h"

using namespace std;

pair< vector<Point>, vector<Point> > getSets(vector<Point> points);
pair< vector<Point>, vector<Point> > getSets(vector<Point> points, Line joiner);
pair< vector<Point>, vector<Point> > getSets(vector<Point> points, float median);
float getMedian(vector<Point> points);

#endif