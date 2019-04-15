#include<cmath>
#include<algorithm>
#include<float.h>
#include<vector>
#include<utility>
#include<iostream>
#include"SegmentedLeastSquares.h"
#include"Line.h"
#include"Point.h"

using namespace std;
/*	Checks if two double values are equal
	*	\param x : first number
	*	\param y : second number
	*	\return true or false
	*/
inline bool isEqual(double x, double y)
{
	
  const double epsilon = 0.0000001/* some small number such as 1e-6 */;
	bool returnValue = abs(x - y) <= epsilon ? true : false;
	return returnValue;
}

/*	Structure to compare x coordinates
*/
struct compareX {
	/*	Returns the smaller of the two points based on their x-coordinate
	*	\param p1: First point
	*	\param p2: Second point
	*	\return true or false
	*/
	inline bool operator () (Point p1, Point p2) {
		
		return (p1.getX() < p2.getX());
	}
};

std::vector<Line> getSegments(std::vector<Point> points, double cost) {
	int length = points.size();
	sort(points.begin() + 1, points.end(), compareX());
	

	double cumulativeX[length], cumulativeY[length], cumulativeXY[length], cumulativeXX[length];
	double slope[length][length] = {0}, intercept[length][length] = {0}, error[length][length] = {0};

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

			if (isEqual(numerator,0)) {
				slope[i][j] = 0;
			}
			else {
				double denominator = (interval * sumXX) - (sumX * sumX);
				slope[i][j] = isEqual(denominator,0) ? DBL_MAX : numerator/denominator;
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

	std::vector<Line> lines;
	Colour white(1,1,1);
	for(int i = length - 1, j = segments[length - 1]; i > 0; i = j - 1, j = segments[i]) {
		Line l(points.at(i), points.at(j), white);

		lines.push_back(l);
		if(i == 1) break;
	} 
	return lines;
}