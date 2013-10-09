
#include "Texture.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint texName;
static double ffar = 0;
Texture treeTexture;

void makeCheckImage(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

void init(void)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   //makeCheckImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &treeTexture.texID);
   glBindTexture(GL_TEXTURE_2D, treeTexture.texID);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);

   glTexImage2D(GL_TEXTURE_2D, 0, treeTexture.bpp / 8, treeTexture.width, treeTexture.height, 0, treeTexture.type, GL_UNSIGNED_BYTE, treeTexture.imageData);
}

void display(void)
{

  

   glLoadIdentity();	
   gluLookAt(0,0, ffar, 0,0,0, 0,1,0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   //glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
   glBegin(GL_QUADS);
   /*
   glTexCoord2f(0.5, 1.0); glVertex3f(-2.0, -1.0, 0.0);
   glTexCoord2f(1.0, 0.5); glVertex3f(-2.0, 1.0, 0.0);
   glTexCoord2f(0.5, 0.0); glVertex3f(0.0, 1.0, 0.0);
   glTexCoord2f(0.0, 0.5); glVertex3f(0.0, -1.0, 0.0);
   
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
   glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
   */


   glTexCoord4f(0.0, 0.0, 0, 1); glVertex3f(-2.0, -2.0, 0.0);
   glTexCoord4f(1.0, 0.0, 0, 1); glVertex3f(2.0, -2.0, 0.0);
   glTexCoord4f(1.0, 1.0, 0, 1); glVertex3f(1.5, 2.0, 0.0);
   glTexCoord4f(0.0, 1.0, 0, 1); glVertex3f(-1.5, 2.0, 0.0);

   glEnd();
   glFlush();
   //glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 300.0);
   glMatrixMode(GL_MODELVIEW);
  
  
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
	  case 'f':
		  ffar = ffar + 0.1;
		  glutPostRedisplay();
		  break;
	     default:
         break;
   }
}

/*int main(int argc, char** argv)
{
   LoadTGA(&treeTexture, "myTexture.tga");
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(250, 250);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}*/