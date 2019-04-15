#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <unistd.h>
#include <GL/freeglut.h>
// #include <chrono> 

#include"SegmentedLeastSquares.h"

#define plotSpace 0.80

using namespace std;

vector<Point> points;
vector<Line> lines;

bool mouseDown = false;
double cost = 0.1;

void drawScene();

//Returns pixel number with top left = 0,0 and bottom right = width,height
void handleMouseMotion(int x, int y) {
    if(x > 77 && x < 947 && y > 708 && y < 748 ) {
        cost = ((double)x - (double)77)/(double)870;
    }
    glutPostRedisplay();
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
        glVertex2f(point.getX() * plotSpace, point.getY() * plotSpace); 
    }
    glEnd();
    //Points plotted
    glDisable(GL_POINT_SMOOTH);

}

/**
*   Draws lines on the canvas
*
*   
*   The lines drawn have the following characteristics:
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

        glVertex2f(line.getp1().getX() * plotSpace, line.getp1().getY() * plotSpace); 
        glVertex2f(line.getp2().getX() * plotSpace, line.getp2().getY() * plotSpace); 
    }

    glEnd();
    //Lines drawn
    glDisable( GL_LINE_SMOOTH );

}
/**
*   Draws slider on the canvas
*
*   
*   The slider drawn have the following characteristics:
*       1. The range is float values from 0 to 1
*       2. The color denotes the location of the slider
*
*/
void drawSlider() {
    double costVal = (cost * 1.7) - 0.85;

    glColor3f(0.543,0.762,0.29);
    glBegin(GL_QUADS);
    glVertex2f(-0.85, -0.95);
    glVertex2f(costVal , -0.95);
    glVertex2f(costVal, -0.85);
    glVertex2f(-0.85, -0.85);
    glEnd();
}
/**
*   Draws sections on the canvas
*   Two sections are present: One for plotting the points and the other for the slider
*
*/
void drawSections() {

    //Plotting
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex2f(-plotSpace, -plotSpace);
    glVertex2f(plotSpace, -plotSpace);
    glVertex2f(plotSpace, plotSpace);
    glVertex2f(-plotSpace, plotSpace);
    glEnd();

    //Slider
    glColor3f(0.953,0.263,0.21);
    glBegin(GL_QUADS);
    glVertex2f(-0.85, -0.95);
    glVertex2f(0.85, -0.95);
    glVertex2f(0.85, -0.85);
    glVertex2f(-0.85, -0.85);

    glEnd();
}
/**
*   Display the value of the cost beside the slider
*
*/
void drawText() {
    glColor3f(0,0,0);
    glRasterPos2f(0.875, -0.91);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char *>(to_string(cost).c_str()) );
    glRasterPos2f(-0.965, -0.915);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("Cost: ") );
}

/**
*   Draws points and lines on the canvas
*
*   Dependent on drawPoints() and drawLines() for the actual drawing
*   Swaps buffers when drawing complete
*/
void drawScene() {

    //Temp (dummy) point to have 1 based indexing instead of 0
    vector<Point> temp;
    Colour tmp(1,1,1);
    Point p(-2,-2,tmp);
    temp.push_back(p);
    temp.insert(temp.end(), points.begin(), points.end());

    //Get lines to draw from the SegmentedLeastSquares Algorithm
    lines = getSegments(temp, cost);
    
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawSections();
    drawSlider();
    drawText();
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
*   main() function
*   Setups the openGL visualisation
*
*   \param int argc: number of arguments received as command Line arguments
*   \param char** argv: the command line arguments
*   \return integer
*/
int main(int argc, char** argv) {
    // using namespace std::chrono; 
    
    getPointsFromUser();
    // auto start = high_resolution_clock::now(); 
    // getSegments(points, cost);
    // auto stop = high_resolution_clock::now(); 
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << duration.count() << endl; 

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
    glutMotionFunc(handleMouseMotion);

    glutMainLoop();

    return 0;
}