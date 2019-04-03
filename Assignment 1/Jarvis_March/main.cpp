#include <vector>
#include <iostream>
#include "jarvis.h"
#include "visualisation.h"
using namespace std;

jarvis::point *P;
int n;

jarvis::point *getpoints() {
    return P;
}

int getSize() {
    return n;
}

int main(int argc, char **argv) {
    // enter number of points
    cin >> n;

    jarvis::point points[n];
    P = points;

    for(int i=0;i<n;i++){
        cin >> P[i].x >> P[i].y;
    }


    // jarvis obj;
    // vector<jarvis::point> hull = obj.ConvexHull(P,n);

    // if(hull.size()<3){
    //     cout << "ConvexHULL not possible" << endl;
    //     return 0;
    // }
    // for(vector<jarvis::point>::iterator it = hull.begin();it!=hull.end();it++){
    //     jarvis::point p = (*it);
    //     cout << "(" << p.x << "," << p.y << ")" << endl;
    // }

    setup(argc, argv);

    return 0;
}