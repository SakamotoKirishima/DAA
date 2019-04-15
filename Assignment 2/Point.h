#ifndef _POINT_
#define _POINT_

#include "Colour.h"

/**
*   Class to store point coordinates
*	
*	The coordinates are considered with center as origin 
*	and the top right corner of window as (1,1)
*/
class Point {
private:
	float x,y;
	Colour colour;
public:

	/**
	*   Constructor to initialise with given coordinates and colour
	*
	*   @param float X: value of X-coordinate (between 0 and 1)
	*   @param float Y: value of Y-coordinate (between 0 and 1)
	*	@param Colour col: RGB value for the point
	*/
	Point(float X, float Y, Colour col);

	/**
	*   Default constructor to initialise a whitepoint at origin
	*/
	Point();

	/**
	*   Return point's X coordinate
	*
	*	@return float: X-coordinate of the point
	*/
	float getX();

	/**
	*   Return point's Y coordinate
	*
	*	@return float: Y-coordinate of the point
	*/
	float getY();

	/**
	*   Return point's colour
	*
	*	@return Colour: Colour of the point
	*/
	Colour getColour();

	/**
	*   Set the point's colour
	*/	
	void setColour(Colour col);

	/**
	*   Operator overload to check equality of points
	*
	*	@return bool: true if x and y coordinates are the same
	*/
	bool operator == (Point p);
};

#endif