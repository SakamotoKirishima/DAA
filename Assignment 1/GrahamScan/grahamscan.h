#ifndef GRAHAMSCAN_H
#define GRAHAMSCAN_H
class Point{
public:
    int x;
    int y;
    Point();
    Point(int x1, int y1);
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
    void setPoint(int x, int y);
    static GlobalClass *instance();
};
void getConvexHull(Point points[], int len);
int sortPoints(Point points[], int len);
void setSmallestPoint(Point points[], int n);
int compare(const void *point1, const void *point2);
std::vector<Point> mainConvexHullFunc(Point points[],int index);
#endif    
