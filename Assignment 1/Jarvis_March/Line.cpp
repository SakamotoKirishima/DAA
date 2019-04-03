#include "Line.h"
#include "jarvis.h"
#include "Colour.h"

Line::Line(jarvis::point P1, jarvis::point P2, Colour col) {
	p1 = P1;
	p2 = P2;
	colour = col;
}

jarvis::point Line::getp1() {
	return p1;
}
jarvis::point Line::getp2() {
	return p2;
}
Colour Line::getColour() {
	return colour;
}