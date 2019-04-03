#ifndef JARVIS_JARVIS_H
#define JARVIS_JARVIS_H

#include <vector>
using namespace std;
/**
*	Class to compute convex hull with Jarvis March algorithm
*/

class jarvis {
public:
	/**
	*	structure to store point
	*/
    struct point{
    	/** x coordinate*/
        double x;
        /** y coordinate */
        double y;
    };
    /** 
    *	Method to get orientation of 3 points
    *	\param p First point
    *	\param q Second point
    *	\param r Third point
    *	\return the orientation of the points
    */
    int orientation(point p,point q,point r);
    /** 
    *	Method to get index of leftmost point
    *	\param P An array of points
    *	\param n Number of points
    *	\return Index of leftmost point
    */

    int getleftmostpoint(point P[],int n);
    /**
    *	Method to get the convex hull
    *	\param P An array of points
    *	\param n Number of points
    *	\return A vector of the convex hull
    */
    vector<point> ConvexHull(point P[],int n);
};


#endif //JARVIS_JARVIS_H
