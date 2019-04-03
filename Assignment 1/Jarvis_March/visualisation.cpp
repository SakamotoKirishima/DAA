#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <unistd.h>
#include <string.h>

#include "jarvis.h"
#include "Line.h"
#include "Colour.h"
#include "main.h"

using namespace std;

vector<jarvis::point> points;
vector<Line> lines;

void setpoints(vector<jarvis::point> p) {
    points = p;
}

void setlines(vector<Line> l) {
    lines = l;
}

int step = 0;

void drawScene();


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
        jarvis obj;
        int n = getSize();
        cout << n;
        vector<jarvis::point> hull = obj.ConvexHull(getpoints(),getSize());

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

    for (jarvis::point pnt : points){
        //Colour of given point
        glColor3f(1, 1, 1);
        glVertex2f(pnt.x/4.0f, pnt.y/4.0f); 
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

        glVertex2f(line.getp1().x/4.0f, line.getp1().y/4.0f); 
        glVertex2f(line.getp2().x/4.0f, line.getp2().y/4.0f); 
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
    jarvis::point p1;
    p1.x = 1; p1.y = 0;
    jarvis::point p2;
    p2.x = -1; p2.y = 0;
    jarvis::point p3;
    p3.x = 0; p3.y = 1;
    jarvis::point p4;
    p4.x = 0; p4.y = -1;
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
*   Setups the openGL visualisation
*
*   @param int argc: number of arguments received as command Line arguments
*   @param char** argv: the command line arguments
*/
void setup(int argc, char** argv) {

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