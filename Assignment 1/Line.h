#ifndef _LINE_
#define _LINE_

#include "Point.h"
#include "Colour.h"

/**
*   Class to store a line
*	
*	Contains 2 extreme points
*	and the colour of the line
*/
class Line {
private:
	Point p1, p2;
	Colour colour;
public:

	/**
	*   Constructor to initialise with given Points and colour
	*
	*   @param Point P1: first Point of the line
	*   @param Point P2: second point of the line
	*	@param Colour col: RGB value for the point
	*/
	Line(Point P1, Point P2, Colour col);

	/**
	*   Function to obtain first point of the line
	*
	*	@return Point object for point 1 of the line
	*/
	Point getp1();

	/**
	*   Function to obtain second point of the line
	*
	*	@return Point object for point 2 of the line
	*/
	Point getp2();

	/**
	*   Function to obtain Colour of the line
	*
	*	@return Colour object of the line
	*/
	Colour getColour();
};

#endif