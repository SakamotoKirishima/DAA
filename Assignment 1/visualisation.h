#ifndef _VISUALISATION_
#define _VISUALISATION_

#include <vector>
#include "Point.h"
#include "Line.h"

using namespace std;

/**
*   Function to setup the visualisation environment
*
*   Initialises openGL Window
*
*   @param argc passed from main
*   @param argv passed from main
*/
void setup(int argc, char** argv);


/**
*   Function to draw points and lines on the canvas
*
*   Depends on drawPoints and drawLines for the actual drawing
*   Swaps buffers when drawing complete
*
*   @param vector of Points
*   @param vector of Lines
*/
void drawScene(vector<Point> points, vector<Line> lines);

#endif