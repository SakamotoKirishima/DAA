#include "Point.h"
#include "Colour.h"

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
