#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <unistd.h>
#include <string.h>

#include "grahamscan.h"
#include "Line.h"
#include "Colour.h"

using namespace std;

vector<Point> points;
vector<Line> lines;

void setpoints(vector<Point> p) {
    points = p;
}

void setlines(vector<Line> l) {
    lines = l;
}

void test() {
    Point points[] = { Point(0, 3), Point(1, 1), Point(2, 2), Point(4, 4), 
       Point(0, 0), Point(1, 2), Point(3, 1), Point(3, 3)}; 
    int n = sizeof(points)/sizeof(points[0]); 
    getConvexHull(points, n); 
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

        case 't':
        test();

    }

    glutPostRedisplay();            //redraw scene
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
        glVertex2f(point.getX()/4.0f, point.getY()/4.0f); 
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

        glVertex2f(line.getp1().getX()/4.0f, line.getp1().getY()/4.0f); 
        glVertex2f(line.getp2().getX()/4.0f, line.getp2().getY()/4.0f); 
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
*   @param char** argv: the command line arguments
*/
void setup(int argc, char** argv) {

    // if(strcmp(argv[1], "-vc") == 0) getPointsFromUser();

    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);

    //Create the window
    glutCreateWindow("Kirkpatrick Seidel Demo");

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);

    glutMainLoop();
}