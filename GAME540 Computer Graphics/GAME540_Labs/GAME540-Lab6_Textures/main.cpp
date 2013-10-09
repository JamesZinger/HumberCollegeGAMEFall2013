// main.cpp : Defines the entry point for the console application.
//

#include <GL\freeglut.h>
#include <math.h>
#include <iostream>
#include "Texture.h"
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

Vector3 CubePosition;
Vector3 CubeRotation;
Vector3 CubeAxisRotation;
Vector3 CameraPosition;

Texture tex1;
Texture tex2;
Texture tex3;
Texture tex4;
Texture tex5;
Texture tex6;

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	 glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &tex1.texID);
   glGenTextures(1, &tex2.texID);
   glGenTextures(1, &tex3.texID);
   glGenTextures(1, &tex4.texID);
   glGenTextures(1, &tex5.texID);
   glGenTextures(1, &tex6.texID);
   glBindTexture(GL_TEXTURE_2D, tex1.texID);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);

   glTexImage2D(GL_TEXTURE_2D, 0, tex1.bpp / 8, tex1.width, tex1.height, 0, tex1.type, GL_UNSIGNED_BYTE, tex1.imageData);
   glTexImage2D(GL_TEXTURE_2D, 0, tex2.bpp / 8, tex2.width, tex2.height, 0, tex2.type, GL_UNSIGNED_BYTE, tex2.imageData);
   glTexImage2D(GL_TEXTURE_2D, 0, tex3.bpp / 8, tex3.width, tex2.height, 0, tex3.type, GL_UNSIGNED_BYTE, tex3.imageData);
   glTexImage2D(GL_TEXTURE_2D, 0, tex4.bpp / 8, tex4.width, tex2.height, 0, tex4.type, GL_UNSIGNED_BYTE, tex4.imageData);
   glTexImage2D(GL_TEXTURE_2D, 0, tex5.bpp / 8, tex5.width, tex2.height, 0, tex5.type, GL_UNSIGNED_BYTE, tex5.imageData);
   glTexImage2D(GL_TEXTURE_2D, 0, tex6.bpp / 8, tex6.width, tex2.height, 0, tex6.type, GL_UNSIGNED_BYTE, tex6.imageData);


}

void display()
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	


	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	gluLookAt(	CameraPosition.x,	CameraPosition.y,	CameraPosition.z,
				0,	0,	0,
				0,	1,	0);

	glPushMatrix();
	//Draw Cube

	glRotatef(CubeAxisRotation.x, 1,0,0);
	glRotatef(CubeAxisRotation.y, 0,1,0);
	glRotatef(CubeAxisRotation.z, 0,0,1);
	glTranslatef(CubePosition.x, CubePosition.y, CubePosition.z);
	glRotatef(CubeRotation.x, 1,0,0);
	glRotatef(CubeRotation.y, 0,1,0);
	glRotatef(CubeRotation.z, 0,0,1);

	glColor3f(0,0,1);
	glBindTexture(GL_TEXTURE_2D,tex1.texID);
	//z = 0.5f
	glBegin(GL_QUADS);
	glTexCoord4f(0,0,0,1);
	glVertex3f(0.5f,	0.5f,	0.5f);
	glTexCoord4f(1.0, 0.0, 0, 1);
	glVertex3f(0.5f,	-0.5f,	0.5f);
	glTexCoord4f(1.0, 1.0, 0, 1);
	glVertex3f(-0.5f,	-0.5f,	0.5f);
	glTexCoord4f(0.0, 1.0, 0, 1);
	glVertex3f(-0.5f,	0.5f,	0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex2.texID);
	//z = -0.5f
	glBegin(GL_QUADS);
	glTexCoord4f(0,0,0,1);
	glVertex3f(0.5f,	0.5f,	-0.5f);
	glTexCoord4f(1.0, 0.0, 0, 1);
	glVertex3f(0.5f,	-0.5f,	-0.5f);
	glTexCoord4f(1.0, 1.0, 0, 1);
	glVertex3f(-0.5f,	-0.5f,	-0.5f);
	glTexCoord4f(0.0, 1.0, 0, 1);
	glVertex3f(-0.5f,	0.5f,	-0.5f);
	glEnd();

	glColor3f(0,1,0);
	glBindTexture(GL_TEXTURE_2D,tex3.texID);
	//y = 0.5f
	glBegin(GL_QUADS);
	glTexCoord4f(0,0,0,1);
	glVertex3f(0.5f,	0.5f,	0.5f);
	glTexCoord4f(1.0, 0.0, 0, 1);
	glVertex3f(-0.5f,	0.5f,	0.5f);
	glTexCoord4f(1.0, 1.0, 0, 1);
	glVertex3f(-0.5f,	0.5f,	-0.5f);
	glTexCoord4f(0.0, 1.0, 0, 1);
	glVertex3f(0.5f,	0.5f,	-0.5f);
	glEnd();

	//y = -0.5f
	glBindTexture(GL_TEXTURE_2D,tex4.texID);
	glBegin(GL_QUADS);
	glTexCoord4f(0,0,0,1);
	glVertex3f(0.5f,	-0.5f,	0.5f);
	glTexCoord4f(1.0, 0.0, 0, 1);
	glVertex3f(0.5f,	-0.5f,	-0.5f);
	glTexCoord4f(1.0, 1.0, 0, 1);
	glVertex3f(-0.5f,	-0.5f,	-0.5f);
	glTexCoord4f(0.0, 1.0, 0, 1);
	glVertex3f(-0.5f,	-0.5f,	0.5f);
	glEnd();

	glColor3f(1,0,0);
	glBindTexture(GL_TEXTURE_2D,tex5.texID);
	//x = 0.5f
	glBegin(GL_QUADS);
	glTexCoord4f(0,0,0,1);
	glVertex3f(0.5f,	0.5f,	0.5f);
	glTexCoord4f(1.0, 0.0, 0, 1);
	glVertex3f(0.5f,	0.5f,	-0.5f);
	glTexCoord4f(1.0, 1.0, 0, 1);
	glVertex3f(0.5f,	-0.5f,	-0.5f);
	glTexCoord4f(0.0, 1.0, 0, 1);
	glVertex3f(0.5f,	-0.5f,	0.5f);
	glEnd();

	//x = -0.5f
	glBindTexture(GL_TEXTURE_2D,tex6.texID);
	glBegin(GL_QUADS);
	glTexCoord4f(0,0,0,1);
	glVertex3f(-0.5f,	0.5f,	0.5f);
	glTexCoord4f(1.0, 0.0, 0, 1);
	glVertex3f(-0.5f,	0.5f,	-0.5f);
	glTexCoord4f(1.0, 1.0, 0, 1);
	glVertex3f(-0.5f,	-0.5f,	-0.5f);
	glTexCoord4f(0.0, 1.0, 0, 1);
	glVertex3f(-0.5f,	-0.5f,	0.5f);
	glEnd();

	glPopMatrix();

	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex3f(0,-5,0);
	glVertex3f(0,5,0);
	glEnd();

	glColor3f(0,0,1);
	glBegin(GL_LINES);
	glVertex3f(0,0,-5);
	glVertex3f(0,0,5);
	glEnd();

	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3f(-5,0,0);
	glVertex3f(5,0,0);
	glEnd();

	CubeAxisRotation.y += 0.04f;
	CubeRotation.x += 0.05f;
	CubeRotation.y += 0.05f;
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
	LoadTGA(&tex1, "myTexture.tga");
	LoadTGA(&tex2, "rocks.tga");
	LoadTGA(&tex3, "rocks_2.tga");
	LoadTGA(&tex4, "rocks_3.tga");
	LoadTGA(&tex5, "rocks_4.tga");
	LoadTGA(&tex6, "snow_2.tga");
	tex1.texID = 1;
	tex2.texID = 2;
	tex3.texID = 3;
	tex4.texID = 4;
	tex5.texID = 5;
	tex6.texID = 6;
	CubePosition = Vector3(0,0,2);
	CubeAxisRotation = Vector3(0,45,0);
	CubeRotation = Vector3(0,0,0);
	CameraPosition = Vector3(2,3,2);
	glutInit(&argc, argsv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Texture Mapping");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardHandler);
	glutMouseFunc(mouseHandler);
	glutPassiveMotionFunc(motionHandler);
	glutIdleFunc(idleHandler);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glutMainLoop();
}
