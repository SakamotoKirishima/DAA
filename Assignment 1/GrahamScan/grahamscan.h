#ifndef GRAHAMSCAN_H
#define GRAHAMSCAN_H

#include "Colour.h"
#include <vector>

using namespace std;
/**
    *Class to store the coordinates and colors of a point
    **/
class Point{
    
    
public:
    /** x coordinate*/
    float x; 
    /** y coordinate*/
    float y; 
    /** Color of point*/
    Colour colour; 
     /**
    *   Constructor to initialise point at (0,0)
    */
    Point(); 
   /**
    *   Constructor to initialise point with default colour white
    *   \param x1 x coordinate
    *   \param y1 y coordinate
    */
    Point(float x1, float y1);
    /**
    *   Constructor to initialise point with given color
    *   \param x1 x coordinate
    *   \param y1 y coordinate
    *   \param c object of class Colour
    */
    
    Point(float x1, float y1, Colour c);
    /**
    *   \return Color of point
    */
    Colour getColour();
    /**
    *   \return x coordinate
    */
    float getX();
    /**
    *   \return y coordinate
    */
    float getY(); 
    /**
    *   Method to get the distance between 2 points
    *   \param p1 First point
    *   \param p2 Second point
    *   \return Distance between p1 and p2
    */
    static double getDistance(Point p1, Point p2);
    /**
    * Method to check if 3 points are colinear or arranged in a clockwise or anti-clockwise direction
    *   \param p1 First point
    *   \param p2 Second point
    *   \param p3 Third point
    *   \return Their respective orientation
    **/
    static int areTheyColinear(Point p1, Point p2, Point p3);
    /**
    *   Method to print the x and y coordinates of the point on the std out
    */
    void printPoint();
    
    };
class GlobalClass
/**
*   Class to store the smallest point in the given list of points
**/
{
private:
    /**Smallest Point*/
    Point smallestPoint; 
    /**Singleton instance of Global Class*/
    static GlobalClass *s_instance;
    /**
    *   Private Constructor
    **/ 
    GlobalClass(); 
    
public:
    /**
    *   \return The smallest point
    */
    Point getPoint();
    /**
    *   Method to set the smallest point's values in the instance
    *   \param x x coordinate
    *   \param y y coordinate
    */
    void setPoint(float x, float y);
    /**
    *   Method to get the singleton instance of the class
    */
    static GlobalClass *instance();
    
};
/**
*   Function to get the convex hull of a given set of points
*   \param points An array of points to get the convex hull
*   \param len number of points in the array
*/
void getConvexHull(Point points[], int len);
/**
*   Function to sort the points in ascending order
*   \param points An array of points to get the convex hull
*   \param len number of points in the array
*/
int sortPoints(Point points[], int len);
/**
*   Function to set the smallest point
*   \param points An array of points to get the convex hull
*   \param n number of points in the array
*/
void setSmallestPoint(Point points[], int n);
/**
*   Function to compare 2 points to see which is smaller
*   \param point1 First point
*   \param point2 Second point
*/
int compare(const void *point1, const void *point2);
/**
*   Function which returns the set of points that are in the hull in clockwise order
*   \param points An array of points to get the convex hull
*   \param index number of points in the array
*   \return A vector of points in the hull
*/
std::vector<Point> mainConvexHullFunc(Point points[],int index);

#endif    
