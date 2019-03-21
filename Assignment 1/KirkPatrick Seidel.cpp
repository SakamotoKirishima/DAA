#include <iostream>
#include <string.h>
#include <vector>
#include <utility>

#include "visualisation.h"
#include "Point.h"
#include "Step1.h"
#include "Step2.h"
#include "Step3.h"
#include "Step4.h"

using namespace std;

//Where it all begins
int main(int argc, char** argv) {

	//Setup the visualisation environment if "-v" is passed
	if(argc == 2 && (strcmp(argv[1], "-v") == 0) ) {
		setup(argc, argv);
	}
	//Run without visualisation
	else {
		vector<Point> points;
		points = generatePoints();			//Step 1
		vector<Point> upperHull = getUpperHull(points);		//Step 2
		pair< vector<Point>, vector<Point> > leftRight = getSets(upperHull);
		vector<Point> left = leftRight.first;
		vector<Point> right = leftRight.second;
		pair<Point,Point> bridge = findBridge(upperHull);

		cout << bridge.first.getX() << "," << bridge.first.getY() << '\t' 
		<< bridge.second.getX() << "," << bridge.second.getY() << '\n';
	}
}