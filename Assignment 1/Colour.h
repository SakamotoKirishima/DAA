#ifndef _COLOUR_
#define _COLOUR_

/**
*   Class to store colour value
*/
class Colour {
public:
	float r, g, b;
	/**
	*   Constructor to initialise with given RGB values
	*
	*   @param float R: value of Red (between 0 and 1)
	*   @param float G: value of Green (between 0 and 1)
	*	@param float B: value of Blue (between 0 and 1)
	*/
	Colour(float R, float G, float B);

	/**
	*   Default constructor to initialise with white
	*/
	Colour();

	bool operator == (Colour c);
};

#endif