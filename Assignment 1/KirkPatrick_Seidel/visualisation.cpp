#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <unistd.h>
#include <string.h>

#include "Step1.h"
#include "Step2.h"
#include "Step3.h"
#include "Step4.h"

using namespace std;

vector<Point> points;
vector<Line> lines;

int step = 0;

void drawScene();

/**
*   (Internal) Find line between upper and lower halfs
*/
void case0next() {
    Line l = getDivider(points);
    lines.push_back(l);
}

/**
*   (Internal) Go (back) to blank state
*
*   Clears all points and lines from the display
*/
void case0prev() {
    points.clear();
    lines.clear();
}

/**
*   (Internal) Display the points in the upper half
*
*   Colours the points in the lower half same as background colour
*   (This is done to enable reversability in the visualisation)
*/
void case1next() {
    Colour black(0,0,0);
    vector<Point> upperHalf = getUpperHalf(points);

    //For each point, if point not in upper half, paint it black
    for(Point point : points){
        vector<Point>::iterator it;
        it = find(upperHalf.begin(), upperHalf.end(), point);

        if(it == upperHalf.end()) {
            point.setColour(black);
            upperHalf.push_back(point);
        }
    }

    points = upperHalf;
    lines.clear();
}

/**
*   Go back to previous step (display only points)
*
*   Only clears the lines to be drawn
*/
void case1prev() {
    lines.clear();
}

/**
*   (Internal) Display division of upper half in two sets
*
*   The two sets are those that are seperated by the line x = median,
*   where median is the median of all the point's X-coordinates.
*   Left Half is displayed in green, right in red
*/
void case2next() {

    Colour red(1,0,0);
    Colour green(0,1,0);
    Colour blue(0,0,1);

    vector<Point> upperHalf = getUpperHalf(points);
    lines.clear();

    float median = getMedian(upperHalf);    

    //Draw median line
    Point p1(median, -1.0, blue);
    Point p2(median, 1.0, blue);
    Line l(p1, p2, blue);
    lines.push_back(l);

    //Get the 2 sets (for colouring accordingly)
    pair< vector<Point>, vector<Point> > leftRight = getSets(upperHalf, median);
    vector<Point> newPoints;

    for(Point point : points){
        vector<Point>::iterator it;
        it = find(leftRight.second.begin(), leftRight.second.end(), point);
        if(it != leftRight.second.end()) {
            point.setColour(red);
        } else {
            it = find(leftRight.first.begin(), leftRight.first.end(), point);
            if(it != leftRight.first.end() ) point.setColour(green);
        }
        newPoints.push_back(point);
    }

    points = newPoints;
}

/**
*   (Internal) Revert to displaying all the points and the divider line.
*
*   Colours all the points white (hence rendering them visible)
*   Then internally call case0next() to draw the divider line.
*/
void case2prev() {

    Colour white(1.0, 1.0, 1.0);

    vector<Point> allPoints;

    for(Point point : points) {
        point.setColour(white);
        allPoints.push_back(point);
    }

    points = allPoints;
    case0next();
}

/**
*   (Internal) Demonstrate the first bridge point
*/
void case3next() {

    Colour red(1,0,0);
    Colour green(0,1,0);
    Colour blue(0,0,1);

    //Same as previous case (done again to refetch the values)
    vector<Point> shortlisted = getUpperHalf(points);
    float median = getMedian(shortlisted);

    pair< vector<Point>, vector<Point> > leftRight = getSets(shortlisted, median);
    vector<Point> right = leftRight.second;
    vector<Point> newPoints;
    for(Point point : points){
        vector<Point>::iterator it;
        it = find(right.begin(), right.end(), point);
        if(it != right.end()) {
            point.setColour(red);
        } else {
            it = find(shortlisted.begin(), shortlisted.end(), point);
            if(it != shortlisted.end() ) point.setColour(green);
        }
        newPoints.push_back(point);
    }
    points = newPoints;

    //Find the bridge and display it
    vector<Point> result = findBridge(shortlisted, median);

    Line l(result.at(0), result.at(1), blue);
    lines.push_back(l);
}

/**
*   (Internal) Revert to displaying the upper half
*
*   Colours all the red points green and clears all lines to be displayed
*/
void case3prev() {
    Colour red(1,0,0);
    Colour green(0,1,0);

    vector<Point> newPoints;
    for(Point point : points) {
        if(point.getColour() == red) point.setColour(green);
        newPoints.push_back(point);
    }

    lines.clear();
}

/**
*   (Internal, Utility) Find the upper convex hull
*
*   This function is recursively called for the left and right
*   sets generated according to the Kirkpatrick Seidel algorithm.
*   Execution of this function disallows returning back to previous steps
*   This function has a sleep timer inside for 1s to display all steps
*
*   @see Page 6 of http://graphics.stanford.edu/courses/cs268-16-fall/Notes/KirkSeidel.pdf
*/
void case4nextUtil(vector<Point> setOfPoints) {
    Colour white(1.0, 1.0, 1.0);

    //if it has 1 or 0 points, no lines can be formed
    if(setOfPoints.size() < 2) {
        return;
    }

    //if it has only 2 points, that is a bridge line (the only possible line)
    if(setOfPoints.size() == 2) {
        Line l(setOfPoints.at(0), setOfPoints.at(1), white);
        lines.push_back(l);
        return;
    }

    //Find bridge lines recursively
    float median = getMedian(setOfPoints);

    vector<Point> candidates = findBridge(setOfPoints, median);

    Colour blue(0,0,1);
    Line l(candidates.at(0), candidates.at(1), blue);

    //Add the bridge, display it and sleep for one second (let user perceive)
    lines.push_back(l);
    drawScene();
    sleep(1);

    //Recurse for left and right half
    pair< vector<Point>, vector<Point> > leftRight = getSets(setOfPoints, l);
    case4nextUtil(leftRight.first);
    case4nextUtil(leftRight.second);
}

/**
*   (Internal) Initiate finding the upper convex hull
*
*   This function calls the corresponding utility function
*/
void case4next() {
    case4nextUtil(getUpperHalf(points));
}

/**
*   Handler for normal key presses in Visualisation
*
*   OpenGL send the key's ASCII code and the mouse position
*   This functions only takes into account the key pressed and handles it accordingly
*/
void handleKeypress(unsigned char key, int x, int y) {

    switch (key) {
        case 27: //Escape key
        exit(0);

        //Translation with char keys (arrow keys in separate function below)
        case 'r':
        if(points.size() == 0) {
            points = generatePoints();
            lines.clear();
        }
        break;

    }

    glutPostRedisplay();            //redraw scene
}

/**
*   Handler for special key presses in Visualisation
*
*   OpenGL send the key's custom code and the mouse position
*   @see https://www.opengl.org/resources/libraries/glut/spec3/node54.html
*   This functions only takes into account the key pressed and handles it accordingly
*/
void specialInput(int key, int x, int y) {

    switch(key)
    {
        case GLUT_KEY_RIGHT:
        switch(step)
        {

            case 0:
            if(points.size() == 0) break;
            case0next();
            step++;
            break;

            case 1:
            case1next();
            step++;
            break;

            case 2:
            case2next();
            step++;
            break;

            case 3:
            case3next();
            step++;
            break;

            case 4:
            case4next();
            step++;
            break;

        }
        break;
        case GLUT_KEY_LEFT:
        switch(step)
        {
            case 0:
            case0prev();
            break;

            case 1:
            case1prev();
            step--;
            break;

            case 2:
            case2prev();
            step--;
            break;

            case 3:
            case3prev();
            step--;
            break;

            case 4:
            case2next();
            step--;
            break;

            case5:
            break;
        }
        break;
    }

    glutPostRedisplay();

}

/**
*   Draw points on the canvas
*
*   
*   The points plotted have the following characteristics:
*       1. They are circular (and not square pixels)
*       2. Point size is 10
*       3. Each point has a unique colour value attached to it
*
*/
void drawPoints() {

    //Make the points circular
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable( GL_POINT_SMOOTH );

    //Set point size
    glPointSize(10);

    //Begin plotting the point
    glBegin(GL_POINTS);

    for (Point point : points){
        //Colour of given point
        Colour colour = point.getColour();
        glColor3f(colour.r, colour.g, colour.b);
        glVertex2f(point.getX(), point.getY()); 
    }
    glEnd();
    //Points plotted
    glDisable(GL_POINT_SMOOTH);

}

/**
*   Draws lines on the canvas
*
*   
*   The lines drawm have the following characteristics:
*       1. They are smooth
*       2. Each point has a unique colour value attached to it
*
*/

void drawLines() {

    //Make smoother lines
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable( GL_LINE_SMOOTH );

    //Begin drawing lines
    glBegin(GL_LINES);

    for(Line line : lines) {

        //Set line colour
        Colour colour = line.getColour();
        glColor3f(colour.r, colour.g, colour.b);

        glVertex2f(line.getp1().getX(), line.getp1().getY()); 
        glVertex2f(line.getp2().getX(), line.getp2().getY()); 
    }

    glEnd();
    //Lines drawn
    glDisable( GL_LINE_SMOOTH );

}

/**
*   Draws points and lines on the canvas
*
*   Depends on drawPoints() and drawLines() for the actual drawing
*   Swaps buffers when drawing complete
*/
void drawScene() {
    // drawScene(points, lines);

    //Draw axis
    Colour axis(1, 0, 1);
    Point p1(1, 0, axis);
    Point p2(-1, 0, axis);
    Point p3(0, 1, axis);
    Point p4(0, -1, axis);
    Line l1(p1, p2, axis);
    Line l2(p3, p4, axis);
    lines.push_back(l1);
    lines.push_back(l2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawPoints(); 
    drawLines();

    //Remove the axis lines (avoid being processed anywhere else)
    lines.pop_back();
    lines.pop_back();

    glutSwapBuffers();
}

/**
*   Get point set from user in case of choice "-vc"
*
*   Obtain all points from stdin with coordinates
*   in the range of -1.0 to 1.0
*   If a point data out of this range is submitted, it stops accepting
*   new points and continues further execution
*
*/
void getPointsFromUser() {
    Colour white(1.0, 1.0, 1.0);

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

/**
*   Setups the openGL visualisation
*
*   @param int argc: number of arguments received as command Line arguments
*   #param char** argv: the command line arguments
*/
void setup(int argc, char** argv) {

    if(strcmp(argv[1], "-vc") == 0) getPointsFromUser();
    
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);

    //Create the window
    glutCreateWindow("Kirkpatrick Seidel Demo");

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialInput);

    glutMainLoop();
}