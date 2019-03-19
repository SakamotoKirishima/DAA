#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>

#include "Point.h"
#include "Line.h"
#include "Colour.h"

using namespace std;

/**
*   Function to handle normal key presses in Visualisation
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
        //TODO: Insert random points
        break;

    }

    glutPostRedisplay();            //redraw scene
}

/**
*   Function to handle special key presses in Visualisation
*
*   OpenGL send the key's custom code and the mouse position
*   @see https://www.opengl.org/resources/libraries/glut/spec3/node54.html
*   This functions only takes into account the key pressed and handles it accordingly
*/
void specialInput(int key, int x, int y) {
    switch(key)
    {
        case GLUT_KEY_RIGHT:
        //TODO: Go to Next visualisation step
        break;
        case GLUT_KEY_LEFT:
        //TODO: Go to Previous Visualisation Step
        break;
    }

    glutPostRedisplay();

}

/**
*   Function to draw points on the canvas
*
*   
*   The points plotted have the following characteristics:
*       1. They are circular
*       2. Point size is 10
*       3. Each point has a unique colour value attached to it
*
*   @param vector of Points which are to be drawn
*/
void drawPoints(vector<Point> points) {

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
*   Function to draw lines on the canvas
*
*   
*   The lines drawm have the following characteristics:
*       1. They are smooth
*       2. Each point has a unique colour value attached to it
*
*   @param vector of Lines which are to be drawn
*/

void drawLines(vector<Line> lines) {

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

void drawScene(vector<Point> points, vector<Line> lines) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawPoints(points); 
    drawLines(lines);

    glutSwapBuffers();
}

/**
*   Function to generate a blank canvas
*/

void drawScene() {
    // drawScene(NULL, NULL);

    //Test code below
    Colour colour;
    Point p1(0.9, 0.9, colour);
    Point p2(0.7, 0.7, colour);
    Point p3(0.3, 0.3, colour);
    vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    Line l1(p1, p2, colour);
    vector<Line> lines;
    lines.push_back(l1);

    drawScene(points, lines);
}



void setup(int argc, char** argv) {
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);

    //Create the window
    glutCreateWindow("Rotating 3D Cuboid");

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialInput);

    glutMainLoop();
}