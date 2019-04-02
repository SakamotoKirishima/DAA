#ifndef GRAHAMSCAN_H
#define GRAHAMSCAN_H

#include "Colour.h"
#include <vector>

using namespace std;

class Point{
public:
    float x;
    float y;
    Colour colour;
    Point();
    Point(float x1, float y1);
    Point(float x1, float y1, Colour c);
    Colour getColour();
    float getX();
    float getY(); 
    static double getDistance(Point p1, Point p2);
    static int areTheyColinear(Point p1, Point p2, Point p3);
    void printPoint();
    };
class GlobalClass
{
private:
    Point smallestPoint;
    static GlobalClass *s_instance;
    GlobalClass();
public:
    Point getPoint();
    void setPoint(float x, float y);
    static GlobalClass *instance();
};
void getConvexHull(Point points[], int len);
int sortPoints(Point points[], int len);
void setSmallestPoint(Point points[], int n);
int compare(const void *point1, const void *point2);
std::vector<Point> mainConvexHullFunc(Point points[],int index);
#endif    
