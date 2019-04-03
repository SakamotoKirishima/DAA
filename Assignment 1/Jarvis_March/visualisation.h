#ifndef __VISUALISATION__
#define __VISUALISATION__
#include <vector>
#include "jarvis.h"
#include "Line.h"

using namespace std;

void setpoints(vector<jarvis::point> p);
void setlines(vector<Line> l);
void drawScene();
void setup(int argc, char** argv);
#endif