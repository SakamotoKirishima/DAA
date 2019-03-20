#include <iostream>
#include <string.h>
#include <vector>

#include "visualisation.h"
#include "Point.h"
#include "Step1.h"
#include "Step2.h"

using namespace std;

//Where it all begins
int main(int argc, char** argv) {

	//Setup the visualisation environment if "-v" is passed
	if(argc == 2 && (strcmp(argv[1], "-v") == 0) ) {
		setup(argc, argv);
	}
	//Run without visualisation
	else {
		vector<Point> points = generatePoints();
		vector<Point> upperHull = getUpperHull(points);
	}
}