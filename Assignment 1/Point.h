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
	*   Function to obtain point's X coordinate
	*
	*	@return X-coordinate of the point
	*/
	float getX();

	/**
	*   Function to obtain point's Y coordinate
	*
	*	@return Y-coordinate of the point
	*/
	float getY();

	/**
	*   Function to obtain point's colour
	*
	*	@return Colour object of the point
	*/
	Colour getColour();
	void setColour(Colour col);

	bool operator == (Point p);
};

#endif