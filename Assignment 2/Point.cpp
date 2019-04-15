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
}

bool Point::operator == (Point p)
{
	//No need for fancy float comparator as value is never manipulated
	if(p.getX() == x && p.getY() == y)
		return true;
	else
		return false;
}