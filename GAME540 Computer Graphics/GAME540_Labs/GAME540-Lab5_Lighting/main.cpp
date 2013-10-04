// main.cpp : Defines the entry point for the console application.
//

#include <GL\freeglut.h>
#include <math.h>
#include <iostream>

void display()
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	gluLookAt(	4,	2,	6,
				0,	0,	0,
				0,	1,	0);


	//glBegin(GL_QUADS);
	//glNormal3f(0,1,0);
	//glVertex3f(0,0,0);
	//glNormal3f(0,1,0);
	//glVertex3f(4,0,0);
	//glNormal3f(0,1,0);
	//glVertex3f(4,0,3);
	//glNormal3f(0,1,0);
	//glVertex3f(0,0,3);
	//glEnd();

	float xdis = 4.0f/100.0f;
	float zdis = 3.0f/100.0f;

	for (int i = 0; i < 100; i++)
	{
	
		for (int j = 0; j < 100; j++)
		{
			glBegin(GL_QUADS);
			glNormal3f(0,1,0);
			glVertex3f(xdis * i,0,zdis*j);
			glNormal3f(0,1,0);
			glVertex3f(xdis * i + xdis,0,zdis*j);
			glNormal3f(0,1,0);
			glVertex3f(xdis * i + xdis,0,zdis * j + zdis);
			glNormal3f(0,1,0);
			glVertex3f(xdis*i,0,zdis*j + zdis);
			glEnd();
		}
	}

	float ydis = 4.0f/100.0f;
	float zdis2 = 3.0f/100.0f;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			glBegin(GL_QUADS);
			glNormal3f(1,0,0);
			glVertex3f(0,ydis * i, zdis2*j);
			glNormal3f(1,0,0);
			glVertex3f(0,ydis * i + ydis,zdis2*j);
			glNormal3f(1,0,0);
			glVertex3f(0,ydis * i + ydis,zdis2 * j + zdis2);
			glNormal3f(1,0,0);
			glVertex3f(0,ydis*i,zdis2*j + zdis2);
			glEnd();
		}
	}

	//glBegin(GL_QUADS);
	//glNormal3f(1,0,0);
	//glVertex3f(0,0,0);
	//glNormal3f(1,0,0);
	//glVertex3f(0,0,3);
	//glNormal3f(1,0,0);
	//glVertex3f(0,4,3);
	//glNormal3f(1,0,0);
	//glVertex3f(0,4,0);
	//glEnd();
	GLfloat diffuseColor[] = {0, 1, 0, 1};
	GLfloat lightPosition[] = {1, 2, 1.5,1};
	GLfloat spotDirection[] = {0,-1, 0};
	GLfloat ambientColor[] = {1,1,1,1};
	GLfloat specular[] = {1,1,1,1};

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);

	lightPosition[0] = 1.8;
	diffuseColor[0] = 1;

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseColor);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientColor);

	diffuseColor[0] = 0;
	diffuseColor[1] = 0;
	diffuseColor[2] = 1;
	lightPosition[0] = 2.6;
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseColor);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientColor);

	diffuseColor[0] = 1;
	diffuseColor[1] = 0;
	diffuseColor[2] = 1;
	lightPosition[0] = 0;
	lightPosition[1] = 3;
	lightPosition[2] = 1;
	glLightfv(GL_LIGHT3, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseColor);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 10);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientColor);

	diffuseColor[0] = 1;
	diffuseColor[1] = 0;
	diffuseColor[2] = 0;
	lightPosition[0] = 0;
	lightPosition[1] = 3;
	lightPosition[2] = 2;
	glLightfv(GL_LIGHT4, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuseColor);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 10);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT4, GL_AMBIENT, ambientColor);


	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);

	glEnable(GL_DEPTH_TEST);

	glFlush();


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
