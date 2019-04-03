#ifndef _COLOUR_
#define _COLOUR_

/**
	*   Class to store colour value
	*/
class Colour {
	
public:
	/** Red value */
	float r; 
	/** Green value */
	float g; 
	/** Blue value*/
	float b; 
	
	/**
	*   Constructor to initialise with given RGB values
	*
	*   \param R A float value of red (between 0 and 1)
	*   \param G A float value of green (between 0 and 1)
	*	\param B A float value of blue (between 0 and 1)
	*/
	Colour(float R, float G, float B);
	
/**
	*   Default constructor to initialise with white
	*/
	
	Colour();
	/**
	*	Equality operator
	**/

	bool operator == (Colour c); 
	
};

#endif