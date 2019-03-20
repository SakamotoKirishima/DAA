#include "Point.h"
#include "Colour.h"

#include <iostream>

using namespace std;

Point::Point(float X, float Y, Colour col) {
	x = X;
	y = Y;
	colour = col;
}
Point::Point() {
	x = 0;
	y = 0;
}

float Point::getX() {
	return x;
}
float Point::getY() {
	return y;
}

Colour Point::getColour() {
	return colour;
}

void Point::setColour(Colour col) {
	colour = col;
	// cout << colour.r << colour.g << colour.b << '\n';
}

bool Point::operator == (Point p)
{
   if(p.getX() == x && p.getY() == y)
     return true;
   else
     return false;
}
