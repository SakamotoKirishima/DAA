#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <unistd.h>
#include <string.h>

#include"SegmentedLeastSquares.h"

using namespace std;

vector<Point> points;
vector<Line> lines;
double cost = 0.1;

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
        break;

        case GLUT_KEY_LEFT:
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

    vector<Point> temp;
    Colour tmp(1,1,1);
    Point p(-2,-2,tmp);
    temp.push_back(p);
    temp.insert(temp.end(), points.begin(), points.end());

    lines = getSegments(temp, cost);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawPoints(); 
    drawLines();

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
    cout << "Enter cost:\n";
    cin >> cost;
    bool flag = true;
    cout << "Enter your points below: (-1 <= x,y <= 1.... else finish reading)\n";
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
int main(int argc, char** argv) {

    getPointsFromUser();
    
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);

    //Create the window
    glutCreateWindow("Segmented Least Squares");

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialInput);

    glutMainLoop();

    return 0;
}