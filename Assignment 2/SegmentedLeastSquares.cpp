#include<cstdlib>
#include<algorithm>
#include<float.h>
#include<vector>
#include<utility>
#include<iostream>
#include"SegmentedLeastSquares.h"
#include"Line.h"
#include"Point.h"

using namespace std;

struct compareX {
	inline bool operator () (Point p1, Point p2) {
		return (p1.getX() < p2.getX());
	}
};

std::vector<Line> getSegments(std::vector<Point> points, double cost) {
	int length = points.size();
	sort(points.begin() + 1, points.end(), compareX());
	

	double cumulativeX[length], cumulativeY[length], cumulativeXY[length], cumulativeXX[length];
	double slope[length][length], intercept[length][length], error[length][length];

	cumulativeX[0] = cumulativeY[0] = cumulativeXY[0] = cumulativeXX[0] = 0.0;
	for(int j = 1; j < length; j++) {
		cumulativeX[j] = cumulativeX[j-1] + points.at(j).getX();
		cumulativeY[j] = cumulativeY[j-1] + points.at(j).getY();
		cumulativeXY[j] = cumulativeXY[j-1] + ( points.at(j).getX() * points.at(j).getY() );
		cumulativeXX[j] = cumulativeXX[j-1] + ( points.at(j).getX() * points.at(j).getX() );

		for(int i = 1; i <= j; i++) {
			int interval = j - i + 1;
			double sumX = cumulativeX[j] - cumulativeX[i-1];
			double sumY = cumulativeY[j] - cumulativeY[i-1];
			double sumXY = cumulativeXY[j] - cumulativeXY[i-1];
			double sumXX = cumulativeXX[j] - cumulativeXX[i-1];

			double numerator = (interval * sumXY) - (sumX * sumY);
			if (numerator == 0) slope[i][j] = 0.0;
			else {
				double denominator = (interval * sumXX) - (sumXX * sumXX);
				slope[i][j] = (denominator == 0) ? DBL_MAX : numerator/denominator;
			}
			intercept[i][j] = (sumY - slope[i][j] * sumX) / (double) interval;

			error[i][j] = 0.0;
			for(int k = i; k <= j; k++) {
				double temp = points.at(k).getY() - (slope[i][j] * points.at(k).getX() ) - intercept[i][j];
				error[i][j] += (temp * temp);
			}
		}
	}


	double opt[length];
	int segments[length];
	opt[0] = segments[0] = 0;
	for(int j = 1; j < length; j++) {
		double min = DBL_MAX;
		int k = 0;
		for(int i = 1; i <= j; i++) {
			double temp = error[i][j] + opt[i-1];
			if (temp < min) {
				min = temp;
				k = i;
			}
		}
		opt[j] = min + cost;
		segments[j] = k;
	}

	for(int i = 0;i < length;i++) {
		cout << points.at(i).getX() << ", " << points.at(i).getY() << '\n';
	}

	cout << "\n";

	std::vector<Line> lines;
	Colour white(1,1,1);
	for(int i = length - 1; i > 0; i = segments[i] - 1) {
		Line l(points.at(i), points.at(segments[i] - 1), white);
		cout << points.at(i).getX() << ", " << points.at(i).getY() 
		<< '\t' 
		<< points.at(segments[i] - 1).getX() << ", " << points.at(segments[i] - 1).getY() 
		<< "\n";

		lines.push_back(l);
		if(i == 1) break;
		// i = segments[i];
	} 
	return lines;
}