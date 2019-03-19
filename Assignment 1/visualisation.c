#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //Escape key
        exit(0);

        //Translation with char keys (arrow keys in separate function below)
        case 'i':
        break;

    }

    glutPostRedisplay();            //redraw scene
}

//Called when special keys are pressed
void specialInput(int key, int x, int y) {
    switch(key)
    {
        case GLUT_KEY_UP:
        break;
    }

    glutPostRedisplay();

}


void drawPoint() {

    //Color set here
    glColor3f(1,1,1);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable( GL_POINT_SMOOTH );

    glPointSize(10);

    glBegin(GL_POINTS);
    glVertex2f(0.9, 0.9); 
    glVertex2f(0.7, 0.7); 

    glEnd();

    glDisable(GL_POINT_SMOOTH);

}

void drawLine() {

    //Color set here
    glColor3f(1,1,1);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable( GL_LINE_SMOOTH );

    glBegin(GL_LINES);
    glVertex2f(0.9, 0.9); 
    glVertex2f(0.7, 0.7); 

    glEnd();

    glDisable( GL_LINE_SMOOTH );

}

//Draws the 3D scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawPoint(); 
    drawLine();

    glutSwapBuffers();
}

void test(int argc, char** argv) {
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