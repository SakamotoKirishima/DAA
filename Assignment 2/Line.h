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
	*   Return first point of the line
	*
	*	@return Point:Point 1 of the line
	*/
	Point getp1();

	/**
	*   Return second point of the line
	*
	*	@return Point: Point 2 of the line
	*/
	Point getp2();

	/**
	*   Return colour of the line
	*
	*	@return Colour: colour of the line
	*/
	Colour getColour();
};

#endif