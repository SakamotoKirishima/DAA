#ifndef JARVIS_JARVIS_H
#define JARVIS_JARVIS_H

#include <vector>
using namespace std;

class jarvis {
public:
    struct point{
        double x;
        double y;
    };
    int orientation(point p,point q,point r);
    int getleftmostpoint(point P[],int n);
    vector<point> ConvexHull(point P[],int n);
};


#endif //JARVIS_JARVIS_H
