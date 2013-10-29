#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include "GL\glew.h"

#include "GL\glfw.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "shader.hpp"
#include "objloader.hpp"
#include "texture.hpp"

using namespace glm;
using namespace std;

mat4 view;
mat4 proj;

void CheckGLErrors()
{
	int error;
	do
	{
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::printf("glError: %s\n", gluErrorString(error));

	}while (error != GL_NO_ERROR);
}

int main ( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		std::fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( 512, 384, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		std::fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile



	if (glewInit() != GLEW_OK) {
		std::fprintf(stderr, "Failed to initialize GLEW\n\n");
		return -1;
	}
	
	CheckGLErrors();
	std::printf("Starting Initialization's\n");

	glfwSetWindowTitle("GAME 540 Lab 7");
	
	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );
	//glfwSetMousePos(1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera matrix
	view       = glm::lookAt(
								glm::vec3(-10,0,0), // Camera is at (-10,0,0), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = proj * view * Model; // Remember, matrix multiplication is the other way around

	vector<vec3> sphereVerts;
	vector<vec4> sphereColor;
	vector<vec4> sphereColor2;
	for(int i = 0; i <= 40; i++)
	{
		double lat0 = M_PI * (-0.5 + (double) (i - 1) / 40);
		double z0  = sin(lat0);
		double zr0 =  cos(lat0);

		double lat1 = M_PI * (-0.5 + (double) i / 40);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		for(int j = 0; j <= 40; j++)
		{
			double lng = 2 * M_PI * (double) (j - 1) / 40;
			double x = cos(lng);
			double y = sin(lng);

			vec3 v = vec3(x * zr0, y * zr0, z0);

			sphereVerts.push_back(v);

			vec4 color = vec4(0.0f, 1.0f, 0.0f, 1.0f);

			sphereColor.push_back(color);

			vec4 color2 = vec4(1.0f, 0.0f, 0.0f, 0.5f);

			sphereColor2.push_back(color2);

			v = vec3(x * zr1, y * zr1, z1);

			sphereVerts.push_back(v);
			
			sphereColor.push_back(color);

			sphereColor2.push_back(color2);
		}
	}


	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sphereVerts.size() * sizeof(vec3), &sphereVerts[0], GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sphereColor.size() * sizeof(vec4), &sphereColor[0], GL_STATIC_DRAW);

	GLuint colorbuffer2;
	glGenBuffers(1, &colorbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer2);
	glBufferData(GL_ARRAY_BUFFER, sphereColor2.size() * sizeof(vec4), &sphereColor2[0], GL_STATIC_DRAW);
	CheckGLErrors();
	std::printf("Starting Loop\n");

	float theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		// Use our shader
		glUseProgram(programID);

		Model = mat4(1.0);

		glm::mat4 MVP = proj * view * Model; // Remember, matrix multiplication is the other way around

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLE_STRIP, 0, sphereVerts.size()); 

		glDisableVertexAttribArray(1);
		
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer2);
		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		
		Model = rotate(Model, theta, vec3(0,1,0));
		Model = translate(Model, vec3(0,0,2));
		Model = scale(Model, vec3(0.5,0.5,0.5));
		

		MVP = proj * view * Model; // Remember, matrix multiplication is the other way around

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0,sphereVerts.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		// Swap buffers
		glfwSwapBuffers();
		theta += 1.0f;
		CheckGLErrors();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}

