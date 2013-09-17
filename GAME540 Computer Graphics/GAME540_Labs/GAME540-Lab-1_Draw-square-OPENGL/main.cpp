// CppTestProject.cpp : Defines the entry point for the console application.


#include <GL/freeglut.h>
#include <math.h>

void display()
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);	//I am loading the ModelView Matrix to be manipulated.
	
	glLoadIdentity();		//Comment in/out to see the effect of Loading Identity
	
	glRotatef(45, 0,0,1);
	glTranslatef(1,0,0);	
	
	//or you may replace with the following
	
	//gluLookAt(-1,0,0,-1,0,-1,1,1,0);
	
	glColor3f( 1.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
	glVertex2f(  -1.0,  -1.0); 
	glVertex2f(  1.0,  -1.0); 
	glVertex2f(  1.0,  1.0); 
	glVertex2f(  -1.0,  1.0); 
	glEnd();
	
	
	glFlush();
	
}


void reshape (int width, int height)
{
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2,2,-2,2,0,10);
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("Square"); // Set the title for the window
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glutMainLoop(); // Enter GLUT's main loop
}  
