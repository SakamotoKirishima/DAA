#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

#include "visualisation.h"
#include "Point.h"
#include "Colour.h"
#include "Step1.h"
#include "Step2.h"
#include "Step3.h"
#include "Step4.h"

using namespace std;

/**
*   Find Upper Convex Hull (using the KirkPatrick Seidel Algorithm)
*
*	Recursively finds all bridges for all the generated halves 
*
*	@see http://graphics.stanford.edu/courses/cs268-16-fall/Notes/KirkSeidel.pdf
*
*  	@param vector<Point> points: Points in the upper half
*	@return vector<Point>: Set of points in the Upper Convex Hull
*/
vector<Point> findUpperConvexHull(vector<Point> points) {

	if(points.size() < 2) {
		vector<Point> p;
		return p;
	}
	if(points.size() == 2) {
		return points;
	}

	vector<Point> answer;
	vector<Point> recv = findBridge(points, getMedian(points));
	answer.insert(answer.end(), recv.begin(), recv.end());

	Colour blue(0,0,1);
	Line l(recv.at(0), recv.at(1), blue);

	pair< vector<Point>, vector<Point> > leftRight = getSets(points, l);
	vector<Point> left = findUpperConvexHull(leftRight.first);
	vector<Point> right = findUpperConvexHull(leftRight.second);

	answer.insert(answer.end(), left.begin(), left.end());
	answer.insert(answer.end(), right.begin(), right.end());

	return answer;
}

//Where it all begins
int main(int argc, char** argv) {
	Colour white(1.0, 1.0, 1.0);
	
	//Run without visualisation
	if( argc == 1 || (argc == 2 && (strcmp(argv[1], "-c") == 0)) ) {
		vector<Point> points;
		//Generate Random Points
		if(argc == 1) {
			points = generatePoints();
		} else {
			bool flag = true;
			cout << "Enter your points below:\n";
			while(flag) {
				float pointX, pointY;
				cin >> pointX;
				cin >> pointY;

				Point p(pointX, pointY, white);
				points.push_back(p);

				if(pointX > 1 || pointY > 1) flag = false;
			}
			points.pop_back();
		}

		//Obtain the set of points in the upper half
		vector<Point> upperHalf = getUpperHalf(points);

		//Run recursive calls to find the upper hull
		vector<Point> upperHull = findUpperConvexHull(upperHalf);
		sort(upperHull.begin(), upperHull.end(), compareX());
		//remove duplicates
		upperHull.erase( unique( upperHull.begin(), upperHull.end() ), upperHull.end() );

		//Print them out
		cout << "Selected in Upper Hull:\n";
		for(Point point : upperHull) {
			cout << point.getX() << "," << point.getY() << '\n';
		}
	}
	//Setup the visualisation environment if "-v" is passed
	else if(argc == 2) {
		if((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "-vc") == 0))
			setup(argc, argv);
	}
}