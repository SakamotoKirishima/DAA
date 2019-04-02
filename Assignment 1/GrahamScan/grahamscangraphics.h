#ifndef __GRAPHICS__
#define __GRAPHICS__

#include <vector>

#include "grahamscan.h"
#include "Line.h"

using namespace std;

void setpoints(vector<Point> p);
void setlines(vector<Line> l);

void setup(int argc, char** argv);
void drawScene();
#endif