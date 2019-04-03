#ifndef __GRAPHICS__
#define __GRAPHICS__

#include <vector>

#include "grahamscan.h"
#include "Line.h"

using namespace std;

void setpoints(vector<Point> p);
/**
* Function to set the set of points to be drawn
*	\param p vector of points
*/
void setlines(vector<Line> l);
/**
*	Function to set the lines to be drawn
* \param l vector of lines 
*/
void setup(int argc, char** argv);
/**
* Function to initialize the window
* \param argc number of arguments
* \param arguments
*/
void drawScene();
/**
*	Draw function
*/
#endif