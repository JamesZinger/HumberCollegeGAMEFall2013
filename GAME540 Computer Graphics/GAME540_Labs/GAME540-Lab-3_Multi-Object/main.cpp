// main.cpp : Defines the entry point for the console application.
//

#include <GL\freeglut.h>
#include <math.h>
#include <iostream>

float Sphere1Rot, Sphere2Rot, CameraRot;

void display()
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	glRotatef(CameraRot, 0,0, 1);
	glTranslatef(0,1,0);
	gluLookAt(	0,	0,	6,
				0,	0,	 0,
				0,	1,	0);

	glPushMatrix();
	
	glTranslatef(-2, 0, 2);
	glRotatef(Sphere1Rot,1,0,1);
	glutWireSphere(0.5, 10,10);

	glPopMatrix();

	glPushMatrix();
	
	glTranslatef(2, 0, 2);
	glRotatef(Sphere2Rot,1,0,1);
	glutWireSphere(0.5, 10,10);

	glPopMatrix();

	glFlush();

	Sphere1Rot += 0.5f;
	Sphere2Rot += 0.5f;
	CameraRot += 0.1f;

}

void reshape (int width, int height)
{
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 1, 100);
}

void keyboardHandler (unsigned char key, int mouseX, int mouseY)
{

}

void mouseHandler (int button, int state, int mouseX, int mouseY)
{

}

void motionHandler (int mouseX, int mouseY)
{

}

void idleHandler ()
{
	glutPostRedisplay();
}


int main (int argc, char** argsv)
{
	Sphere1Rot = 0;
	Sphere2Rot = 0;
	CameraRot = 0;
	glutInit(&argc, argsv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("TriangleRot");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardHandler);
	glutMouseFunc(mouseHandler);
	glutPassiveMotionFunc(motionHandler);
	glutIdleFunc(idleHandler);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutMainLoop();
}
