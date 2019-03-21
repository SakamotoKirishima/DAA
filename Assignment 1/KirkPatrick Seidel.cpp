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

vector<Point> findBridges(vector<Point> points) {

	if(points.size() < 2) {
		vector<Point> p;
		return p;
	}
	if(points.size() == 2) {
		return points;
	}

	vector<Point> answer;
	pair<Point, Point> recv = findBridge(points);
	answer.push_back(recv.first);
	answer.push_back(recv.second);

	Colour blue(0,0,1);
	Line l(recv.first, recv.second, blue);

	pair< vector<Point>, vector<Point> > leftRight = getSets(points, l);
	vector<Point> left = findBridges(leftRight.first);
	vector<Point> right = findBridges(leftRight.second);

	answer.insert(answer.end(), left.begin(), left.end());
	answer.insert(answer.end(), right.begin(), right.end());

	return answer;
}

//Where it all begins
int main(int argc, char** argv) {
	//Run without visualisation
	if( argc == 1 || (argc == 2 && (strcmp(argv[1], "-c") == 0)) ) {
		vector<Point> points;
		//Generate Random Points
		if(argc == 1) {
			points = generatePoints();
			cout << "Generated points:\n";
			for(Point point : points) {
				cout << point.getX() << "\t" << point.getY() << '\n';
			}
			cout << '\n';	
		} else {
			Colour white(1, 1, 1);
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
		vector<Point> upperHull = getUpperHull(points);

		//Run recursive calls to find the upper hull
		vector<Point> pointsInUpperHull = findBridges(upperHull);
		sort(pointsInUpperHull.begin(), pointsInUpperHull.end());
		pointsInUpperHull.erase( unique( pointsInUpperHull.begin(), pointsInUpperHull.end() ), pointsInUpperHull.end() );
		cout << "Selected in Upper Hull:\n";
		for(Point point : pointsInUpperHull) {
			cout << point.getX() << "," << point.getY() << '\n';
		}
	}
	//Setup the visualisation environment if "-v" is passed
	else if(argc == 2) {
		if((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "-vc") == 0)) setup(argc, argv);
	}
}