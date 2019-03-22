
#include <iostream>
#include <algorithm>
#include<math.h>
#include <stdlib.h>
#include <vector>
#include "grahamscan.h"

Point::Point(){
    x=0;
    y=0;
}
Point::Point(int x1, int y1){
    x= x1;
    y=y1;
}
double Point:: getDistance(Point p1, Point p2){
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}
int Point::areTheyColinear(Point p1, Point p2, Point p3){
    int val= (p2.y-p1.y)*(p3.x-p2.x)-(p2.x-p1.x)*(p3.y-p2.y);
    if (!val) return 1;
    return (val>0)?-1:0;
}
void Point:: printPoint(){
    std::cout << x << ", " << y << '\n';
}

GlobalClass::GlobalClass()
{
}
Point GlobalClass:: getPoint()
{
    return smallestPoint;
}
void GlobalClass:: setPoint(int x, int y)
{
    smallestPoint.x=x;
    smallestPoint.y=y;
}
GlobalClass * GlobalClass:: instance()
{
    if (!s_instance)
      s_instance = new GlobalClass;
    return s_instance;
}
GlobalClass *GlobalClass::s_instance = 0;

void getConvexHull(Point points[], int len){
    setSmallestPoint(points,len);
    int index= sortPoints(points, len);
    if (index==-1) return;
    // for (int i = 0; i < len; ++i)
    //  {
    //     // points[i].printPoint();

    //     // std::cout << "___________________________________\n"<< i << '\n';
    //     // GlobalClass::instance()->getPoint().printPoint();
    //     // points[i].printPoint();
    //     // points[i+1].printPoint();
    //     // std::cout << Point::areTheyColinear(GlobalClass::instance()->getPoint(),points[i],points[i+1])<< '\n';
    //     // std::cout << "___________________________________\n";
    //      if(i<len-1 && (Point::areTheyColinear(GlobalClass::instance()->getPoint(),points[i],points[i+1])==1)) continue;
    //      points[index++]=points[i];
    //  } 
    // std::cout << GlobalClass::instance()->getPoint().x << ", " << GlobalClass::instance()->getPoint().y << '\n' ;
    
     // for (int i = 0; i < index; ++i)
     // {
     //     points[i].printPoint();
     // }
     // return;
     
     // return;
    std::vector<Point> convexHull = mainConvexHullFunc(points,index);
     for (auto i = convexHull.rbegin(); i != convexHull.rend(); ++i){
        (*i).printPoint();
     } 
        

}
std::vector<Point> mainConvexHullFunc(Point points[], int index){
    std::vector<Point> convexHull;
     convexHull.push_back(points[0]);
     convexHull.push_back(points[1]);
     convexHull.push_back(points[2]);
     auto tillhere= convexHull.end();
     for (int i = 3; i < index; ++i)
     {
        // points[i].printPoint();
        // std::cout << Point::areTheyColinear(convexHull[convexHull.size()-2],convexHull[convexHull.size()-1],points[i]) << '\n';
        while(Point::areTheyColinear(convexHull[convexHull.size()-2],convexHull[convexHull.size()-1],points[i])){
            convexHull.erase(convexHull.end()-1);
        }
         // if(Point::areTheyColinear(convexHull[convexHull.size()-2],convexHull[convexHull.size()-1],points[i])==0){
         //    tillhere--;
         //    continue;
         // }
         // convexHull.erase(tillhere,convexHull.end());
         // tillhere= convexHull.end();
         convexHull.push_back(points[i]);
     }
     return convexHull;
}
int sortPoints(Point points[], int len){
    qsort(&points[1], len-1, sizeof(Point), compare);
    int index=1;
    // for (int i = 0; i < len; ++i)
    //  {
    //     points[i].printPoint();
    // }
    // return;
    for (int i = 1; i < len; ++i)
     {
        // points[i].printPoint();

        // std::cout << "___________________________________\n"<< i << '\n';
        // GlobalClass::instance()->getPoint().printPoint();
        // points[i].printPoint();
        // points[i+1].printPoint();
        // std::cout << Point::areTheyColinear(GlobalClass::instance()->getPoint(),points[i],points[i+1])<< '\n';
        // std::cout << "___________________________________\n";
         if(i<len-1 && (Point::areTheyColinear(GlobalClass::instance()->getPoint(),points[i],points[i+1])==1)) continue;
         points[index++]=points[i];
         
     } 
     if(index<3) index=-1;
     return index;
}
void setSmallestPoint(Point points[], int n){
    Point minPoint = points[0];
    int index=0;
    for (int i = 1; i < n; ++i)
    {
        if((minPoint.y>points[i].y)||((minPoint.y==points[i].y) && (minPoint.x>points[i].x))){
            minPoint=points[i];
            index=i;
        }
    }
    GlobalClass::instance()->setPoint(minPoint.x,minPoint.y);
    std::swap(points[0],points[index]);

}
int compare(const void *point1, const void *point2){
        const Point *p1 = static_cast<const Point *>(point1);
        const Point *p2 = static_cast<const Point *>(point2);
        if(Point::areTheyColinear(GlobalClass::instance()->getPoint(),*p1,*p2)==1){
            return (Point::getDistance(GlobalClass::instance()->getPoint(),*p1)<=Point::getDistance(GlobalClass::instance()->getPoint(),*p2))?-1:1;
        }
        return (!Point::areTheyColinear(GlobalClass::instance()->getPoint(),*p1,*p2))?-1:1;
    }
int main(int argc, char const *argv[])
{
    Point points[] = { Point(0, 3), Point(1, 1), Point(2, 2), Point(4, 4), 
                       Point(0, 0), Point(1, 2), Point(3, 1), Point(3, 3)}; 
    int n = sizeof(points)/sizeof(points[0]); 
    getConvexHull(points, n); 
    // Point p(1,2);
    // Point p1(1,0);
    // std::swap(p,p1);
    // // std::cout << Point::getDistance(p,p1) << '\n';
    // std::cout << compare(&p,&p1) << '\n';
    // // std::cout << GlobalClass::instance()->getPoint().x << '\n';
    return 0;
}