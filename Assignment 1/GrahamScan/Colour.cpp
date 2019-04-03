#include "Colour.h"
Colour::Colour(float R, float G, float B) {
	r = R;
	g = G;
	b = B;
}
Colour::Colour() {
	r = g = b = 1;
}

bool Colour::operator == (Colour c) {
	return (c.r == r && c.g == g && c.b == b);
}