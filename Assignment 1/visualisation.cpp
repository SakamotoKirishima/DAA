#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <unistd.h>

#include "Point.h"
#include "Line.h"
#include "Colour.h"

#include "Step1.h"
#include "Step2.h"
#include "Step3.h"
#include "Step4.h"

using namespace std;

vector<Point> points;
vector<Line> lines;

int step = 0;

void case0next() {
    Line l = getDivider(points);
    lines.push_back(l);
}

void case0prev() {
    points.clear();
    lines.clear();
}

void case1next() {

    Colour black(0.0, 0.0, 0.0);

    vector<Point> upperHull = getUpperHull(points);

    for(Point point : points){
        vector<Point>::iterator it;
        it = find(upperHull.begin(), upperHull.end(), point);

        if(it == upperHull.end()) {
            point.setColour(black);
            upperHull.push_back(point);
        }
    }

    points = upperHull;
    lines.clear();
}

void case1prev() {
    lines.clear();
}

void case2next() {

    Colour red(1.0, 0.0, 0.0);
    Colour blue(0.0, 0.0, 1.0);
    Colour green(0.0, 1.0, 0.0);

    vector<Point> upperHull = getUpperHull(points);
    lines.clear();

    float median = getMedian(upperHull);
    Point p1(median, -1.0, blue);
    Point p2(median, 1.0, blue);
    Line l(p1, p2, blue);
    lines.push_back(l);

    pair< vector<Point>, vector<Point> > leftRight = getSets(upperHull, median);
    vector<Point> right = leftRight.second;
    vector<Point> newPoints;

    for(Point point : points){
        vector<Point>::iterator it;
        it = find(right.begin(), right.end(), point);
        if(it != right.end()) {
            point.setColour(red);
        } else {
            it = find(upperHull.begin(), upperHull.end(), point);
            if(it != upperHull.end() ) point.setColour(green);
        }
        newPoints.push_back(point);
    }

    points = newPoints;
}

void case2prev() {

    vector<Point> allPoints;
    Colour white(1.0, 1.0, 1.0);

    for(Point point : points) {
        point.setColour(white);
        allPoints.push_back(point);
    }

    points = allPoints;
    case0next();
}

void case3next() {
    vector<Point> shortlisted = getUpperHull(points);
    vector<Line> randomLines;
    float median = getMedian(shortlisted);
    while(shortlisted.size() > 2) {
        randomLines.clear();
        randomLines.push_back(lines.at(0));
        pair< vector<Line>, vector<Point> > result = findBridgeUtil(shortlisted, median);
        shortlisted = result.second;

        randomLines.insert(randomLines.end(), result.first.begin(), result.first.end());

        // glutPostRedisplay();
    }

    Colour black(0.0, 0.0, 0.0);
    vector<Point> newPoints;
    for(int i = 0;i < points.size(); i++) {
        Point p = points.at(i);
        if( !(p == shortlisted.at(0)) && !(p == shortlisted.at(1)) ) {
            p.setColour(black);
        }
        newPoints.push_back(p);
    }

    points = newPoints;
    lines = randomLines;

}

void case3prev() {
    vector<Point> newPoints;
    Colour red(1.0, 0.0, 0.0);
    Colour green(0.0, 1.0, 0.0);
    for(Point point : points) {
        if(point.getColour() == red) point.setColour(green);
        newPoints.push_back(point);
    }

    lines.clear();
}

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
        if(step == 0) {
            points = generatePoints();
            lines.clear();
        }
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
        switch(step)
        {

            case 0:
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
        }
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
*   Function to draw lines on the canvas
*
*   
*   The lines drawm have the following characteristics:
*       1. They are smooth
*       2. Each point has a unique colour value attached to it
*
*   @param vector of Lines which are to be drawn
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
*   Function to draw points and lines on the canvas
*
*   Depends on drawPoints and drawLines for the actual drawing
*   Swaps buffers when drawing complete
*/
void drawScene() {
    // drawScene(points, lines);

    //Test code
    // Colour colour;
    // Point p1(0, 0, colour);
    // Point p2(1, 1, colour);
    // Point p3(200, 200, colour);
    // points.push_back(p1);
    // points.push_back(p2);
    // points.push_back(p3);

    // Line l1(p1, p2, colour);
    // lines.push_back(l1);
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

    lines.pop_back();
    lines.pop_back();

    glutSwapBuffers();
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