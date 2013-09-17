
#include <GL\freeglut.h>
#include <math.h>
#include <iostream>

struct Vector2
{
	int x;
	int y;
};

#define __ROTATION_STEP_AMOUNT__ 20
#define __ROTATION_REPEAT_AMOUNT__ 0.1

GLfloat theta;
bool rotating;
Vector2* initalLoc;
Vector2* prevMousePos;
bool fixedMode;

void display()
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	gluLookAt(	0,	0,	-1,
				0,	0,	 0,
				0,	1,	0);

	glRotatef(theta,0,0,1);

	glColor3f( 0.0, 0.0, 1.0 );
	glBegin(GL_TRIANGLES);
	glVertex2f(  -1.0,  -1.0); 
	glVertex2f(  1.0,  -1.0); 
	glVertex2f( 0,  1); 
	
	glEnd();

	if (rotating)
	{
		theta += __ROTATION_REPEAT_AMOUNT__;
	}
	
	glFlush();
}

void reshape (int width, int height)
{
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2,2,-2,2,0,10);
}

void keyboardHandler (unsigned char key, int mouseX, int mouseY)
{
	if (key == 's' || key == 'S')
	{
		rotating = !rotating;
		return;
	}

	if (key == 'b' || key == 'B')
	{
		theta -= __ROTATION_STEP_AMOUNT__;
		return;
	}

	if (key == 'f' || key == 'F')
	{
		theta += __ROTATION_STEP_AMOUNT__;
		return;
	}

	if (key == 'r')
	{
		fixedMode = !fixedMode;
	}
	
}

void mouseHandler (int button, int state, int mouseX, int mouseY)
{
	if( GLUT_RIGHT_BUTTON ==  button && state == GLUT_UP)
	{
		delete initalLoc;
		delete prevMousePos;
		exit(0);
	}
	/*
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			initalLoc->x = mouseX;
			initalLoc->y = mouseY;
			return;
		}

		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			if(initalLoc == NULL)
				return;

			if(mouseX - initalLoc->x > 0)
				theta -= __ROTATION_STEP_AMOUNT__;
			else if (mouseX - initalLoc->x < 0)
				theta += __ROTATION_STEP_AMOUNT__;
			return;
		}
		*/
	
}

void motionHandler (int mouseX, int mouseY)
{
	if (prevMousePos == NULL)
	{
		return;
	}
	if (mouseX > prevMousePos->x)
	{
		theta -= __ROTATION_REPEAT_AMOUNT__;
	}
	else if (mouseX < prevMousePos->x)
	{
		theta += __ROTATION_REPEAT_AMOUNT__;
	}

	prevMousePos->x = mouseX;
	prevMousePos->y = mouseY;
	return;
	
}

void idleHandler ()
{
	glutPostRedisplay();
}

int main (int argc, char** argsv)
{
	theta = 0;
	rotating = FALSE;
	initalLoc = new Vector2();
	prevMousePos = new Vector2();
	fixedMode = FALSE;
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

#undef __ROTATION_STEP_AMOUNT__
#undef __ROTATION_REPEAT_AMOUNT__