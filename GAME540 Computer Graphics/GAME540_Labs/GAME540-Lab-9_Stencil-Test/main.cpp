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
GLuint sphereProgramID;
GLuint sphereMatrixID;
GLuint sphereVertBuffer;
GLuint sphereColorBuffer;
int sphereVertsSize;
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
void DrawSphere(mat4 MVP, GLuint programID, GLuint MVPID, GLuint vertsBuffer, GLuint colorBuffer, int size)
{

	glUseProgram(programID);

	glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertsBuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLE_STRIP, 0, size); 

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
}

void resize (int width, int height)
{
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc (GL_NEVER, 0x1, 0x1);
	glStencilOp (GL_REPLACE, GL_REPLACE, GL_REPLACE);

	mat4 Model = mat4(1.0f);
	Model = translate(Model, vec3(-5,0,0));
	mat4 MVP = proj * view * Model;
		
	DrawSphere(MVP, sphereProgramID, sphereMatrixID, sphereVertBuffer, sphereColorBuffer, sphereVertsSize);

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

	
	vector<vec3> sphereVerts;
	vector<vec4> sphereColor;
	
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

			vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);

			sphereColor.push_back(color);

			v = vec3(x * zr1, y * zr1, z1);

			sphereVerts.push_back(v);
			
			sphereColor.push_back(color);
		}
	}

	sphereVertsSize = sphereVerts.size();

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_NEVER, 1, 0x1);
	//glStencilOp( GL_REPLACE, GL_KEEP, GL_KEEP );

	
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	sphereProgramID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

	// Get a handle for our "MVP" uniform
	sphereMatrixID = glGetUniformLocation(sphereProgramID, "MVP");

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

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


	GLuint Texture = loadBMP_custom("Class Model0.bmp");

	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	vector<vec3> tarusVerts;
	vector<vec3> tarusNorms;
	vector<vec2> tarusUVs;
	loadOBJ("ClassDiagram.obj", tarusVerts, tarusUVs, tarusNorms);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, tarusVerts.size() * sizeof(vec3), &tarusVerts[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, tarusUVs.size() * sizeof(vec2), &tarusUVs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, tarusNorms.size() * sizeof(glm::vec3), &tarusNorms[0], GL_STATIC_DRAW);

	glGenBuffers(1, &sphereVertBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, sphereVertBuffer);
	glBufferData(GL_ARRAY_BUFFER, sphereVerts.size() * sizeof(vec3), &sphereVerts[0], GL_STATIC_DRAW);

	glGenBuffers(1, &sphereColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, sphereColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sphereColor.size() * sizeof(vec4), &sphereColor[0], GL_STATIC_DRAW);


	CheckGLErrors();
	std::printf("Starting Loop\n");

	glClearStencil(0x0);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	glfwSetWindowSizeCallback(resize);

	do{
		
		

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			


		glStencilFunc(GL_EQUAL, 0x1, 0x1);
		glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);


		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		Model = mat4(1.0);
		Model = rotate(Model,90.0f,vec3(0,0,1));
		Model = scale(Model, vec3(4,1,4));
		//Model = translate(Model, vec3(0,0,0));
		MVP = proj * view * Model; // Remember, matrix multiplication is the other way around

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &view[0][0]);

		glm::vec3 lightPos = glm::vec3(-10,0,0);

		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, tarusVerts.size()); 
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);	
		
		// Swap buffers
		glfwSwapBuffers();
		CheckGLErrors();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}

