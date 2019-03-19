/*
*
* To compile:
*   g++ Transform3DCuboid.cpp -lglut -lGL -lGLU
*
*/
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

//Initializes 3D rendering
void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    //glShadeModel(GL_SMOOTH); //Enable smooth shading
}

//Called when the window is resized
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


void drawCube(float dimensions[], float center[], float colour[]) {

    //Color set here
    glColor3f(colour[0], colour[1], colour[2]);
    glBegin(GL_QUADS);

    glEnd();

}

//Draws the 3D scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawCube(dimensions, center, colour); 
    glutSwapBuffers();
}

void test(int argc, char** argv) {
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);

    //Create the window
    glutCreateWindow("Kirkpatrick Seidel Visualisation");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialInput);
    glutReshapeFunc(handleResize);

    glutMainLoop();
}