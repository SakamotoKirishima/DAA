#include "grahamscan.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class GUI{
public:
	int screenWidth;
	int screenHeight;
	
	GUI(int width, int height){
		screenWidth=width;
		screenHeight=height;
	}
	void go(){
		GLFWwindow *window;
		if (!glfwInit()) return;
	    window = glfwCreateWindow(screenWidth, screenHeight, "GrahamScan", NULL, NULL);
	    if (!window)
	    {
	        glfwTerminate();
	        return;
	    }
	    glfwMakeContextCurrent(window);	    
	    glViewport(0.0f, 0.0f, screenWidth, screenHeight); 
	    glMatrixMode(GL_PROJECTION); 
	    glLoadIdentity(); 
	    glOrtho(0, screenWidth, 0, screenHeight, 0, 1); 
	    glMatrixMode(GL_MODELVIEW); 
	    glLoadIdentity();
		GLfloat pointVertex[] = { screenWidth / 2, screenHeight / 2 };
	    GLfloat pointVertex2[] = { screenWidth * 0.75, screenHeight / 2 };
	    while (!glfwWindowShouldClose(window))
	    {
	        glClear(GL_COLOR_BUFFER_BIT);
	        glEnable(GL_POINT_SMOOTH);
	        glEnableClientState(GL_VERTEX_ARRAY);
	        glPointSize(3);
	        glVertexPointer(2, GL_FLOAT, 0, pointVertex);
	        glDrawArrays(GL_POINTS, 0, 1);
	        glDisableClientState(GL_VERTEX_ARRAY);
	        glDisable(GL_POINT_SMOOTH);
	        
	        glEnableClientState(GL_VERTEX_ARRAY); 
	        glVertexPointer(2, GL_FLOAT, 0, pointVertex2);
	        glPointSize(1); 
	        glDrawArrays(GL_POINTS, 0, 1); 
	        glDisableClientState(GL_VERTEX_ARRAY);
	        glfwSwapBuffers(window);
	        
	        // Poll for and process events
	        glfwPollEvents();
	    }
	    
	    glfwTerminate();
}
};
int main(int argc, char const *argv[])
{
	GUI o(300,300);
	o.go();
	return 0;
}