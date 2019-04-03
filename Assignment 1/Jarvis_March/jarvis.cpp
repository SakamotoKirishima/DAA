#include <iostream>
#include <unistd.h>

#include "jarvis.h"
#include "Colour.h"
#include "Line.h"
#include "visualisation.h"
using namespace std;

vector<jarvis::point> pointArraytoVector(jarvis::point points[], int size) {
    vector<jarvis::point> pointsVector;
    for(int i = 0;i < size; i++) {
        pointsVector.push_back(points[i]);
    }
    return pointsVector;
}

void draw(vector<jarvis::point> points, vector<Line> lines) {
    setpoints(points);
    setlines(lines);
    drawScene();
    sleep(1);
}

int jarvis::orientation(jarvis::point p, jarvis::point q, jarvis::point r){
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if(val==0) return 0;
    else if(val > 0) return 1;
    else return 2;
}
int jarvis::getleftmostpoint(jarvis::point *P, int n){
    jarvis::point result = P[0];
    int answer = 0;
    for(int i=1;i<n;i++){
        if(P[i].x < result.x) {
            result = P[i];
            answer = i;
        }
        else if(P[i].x==result.x && P[i].y>result.y){
            result = P[i];
            answer = i;
        }
    }
    return answer;
}
vector<jarvis::point> jarvis::ConvexHull(jarvis::point *P, int n){
    if(n<3){
        vector<jarvis::point> V;
        //cout << "Convex Hull Not possible" << endl;
        return V;
    }

    vector<jarvis::point> pointsVector;
    vector<Line> lines;

    for(int i = 0;i < n;i++) {
        pointsVector.push_back(P[i]);
    }

    draw(pointsVector, lines);

    vector<jarvis::point> hull;
    int l = getleftmostpoint(P,n);

    int p=l,q;

    Colour blue(0,0,1);

    while(1){
        hull.push_back(P[p]);

        lines.clear();

        q = (p+1)%n;
        for(int i=0;i<n;i++) {
            if(i > 0) {
                lines.erase(lines.begin() + lines.size() - 1);
                lines.erase(lines.begin() + lines.size() - 1);
            }
            Line l1(P[p],P[i], blue);
            Line l2(P[i], P[q], blue);
            lines.push_back(l1);
            lines.push_back(l2);
            draw(pointsVector, lines);
            if(orientation(P[p],P[i],P[q])==2)
                q=i;
        }

        lines.clear();

        for(unsigned int i = 0; i < hull.size() - 1; i++) {
            Line l1(hull[i], hull[i+1], blue);
            lines.push_back(l1);
        }

        draw(pointsVector, lines);

        p = q;
        if(p==l) break;
    }

    return hull;
}
