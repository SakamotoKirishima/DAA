#include "Line.h"
#include "grahamscan.h"
#include "Colour.h"

Line::Line(Point P1, Point P2, Colour col) {
	p1 = P1;
	p2 = P2;
	colour = col;
}

Point Line::getp1() {
	return p1;
}
Point Line::getp2() {
	return p2;
}
Colour Line::getColour() {
	return colour;
}