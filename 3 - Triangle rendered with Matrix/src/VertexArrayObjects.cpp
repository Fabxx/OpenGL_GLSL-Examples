#include <GL/glew.h>
#include <GL/gl.h>
#include "VertexArrayObjects.hh"

//Giving to openGL the triangle
// This will identify our vertex buffer
GLuint vertexbuffer;

void VertexArrayObjects()
{
	//Creating the VAO to store the vertices
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID); //drawing N vertices on the array of vertices and we store them.
	glBindVertexArray(VertexArrayID); //bind vertexes on buffer.
	

	//A vertex is composed of 3 screen coordinates: X, Y and Z. we need an array to sotre these coordinates.
	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f, //will be displayed at coords -1 -1, can't be changed because it's built in GPU.
		1.0f, 1.0f, 0.0f,
   		0.0f,  1.0f, 0.0f,
	}; //X, Y, Z, each 3 coords represent a vertex axis, modyfing these will edit the vertex coordinates, not the size of the triangle

	
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void VertexArrayCompute()
{
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}