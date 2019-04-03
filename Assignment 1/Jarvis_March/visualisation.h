#ifndef __VISUALISATION__
#define __VISUALISATION__
#include <vector>
#include "jarvis.h"
#include "Line.h"

using namespace std;
/**
*	Set the points to be drawn
*	\param p Vector of points
*/
void setpoints(vector<jarvis::point> p);
/**
*	Set the lines to be drawn
*	\param l Vector of lines
*/
void setlines(vector<Line> l);
/**
*	Draw Function
*/
void drawScene();
/**
*	Setup the window
**/
void setup(int argc, char** argv);
#endif