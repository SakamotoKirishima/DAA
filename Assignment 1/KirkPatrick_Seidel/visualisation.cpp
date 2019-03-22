#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <unistd.h>
#include <string.h>

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
    float median = getMedian(shortlisted);
    Colour red(1, 0, 0);
    Colour green(0, 1, 0);
    Colour blue(0, 0, 1);

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

    vector<Point> result = findBridgeUtil(shortlisted, median);



    // lines.clear();
    Line l(result.at(0), result.at(1), blue);
    lines.push_back(l);
    // points = shortlisted;
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

vector<Line> case4nextUtil(vector<Point> setOfPoints) {

    if(setOfPoints.size() < 2) {
        vector<Line> lines;
        return lines;
    }
    if(setOfPoints.size() == 2) {
        Colour white(1, 1, 1);
        vector<Line> result;
        Line l(setOfPoints.at(0), setOfPoints.at(1), white);
        result.push_back(l);
        return result;
    }
    float median = getMedian(setOfPoints);

    vector<Point> candidates = findBridgeUtil(setOfPoints, median);

    Colour blue(0, 0, 1);
    Line l(candidates.at(0), candidates.at(1), blue);
    vector<Line> randomLines;
    randomLines.push_back(l);

    pair< vector<Point>, vector<Point> > leftRight = getSets(setOfPoints, l);

    vector<Line> leftLines = case4nextUtil(leftRight.first);
    vector<Line> rightLines = case4nextUtil(leftRight.second);
    randomLines.insert(randomLines.end(), leftLines.begin(), leftLines.end());
    randomLines.insert(randomLines.end(), rightLines.begin(), rightLines.end());
    // cout << randomLines.size();
    return randomLines;

    // lines.insert()
}

void case4next() {
    // cout << "Case 4 started";
    lines = case4nextUtil(getUpperHull(points));
    // cout << "Case 4 finished";
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
        if(points.size() == 0) {
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

void getPointsFromUser() {
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