#include <GL/glew.h>
#include <GL/gl.h>
#include "VertexArrayObjects.hh"

void VertexArrayObjects()
{
	//Creating the VAO to store the vertices
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID); 
	glBindVertexArray(VertexArrayID); 

	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f,
   		0.0f,  1.0f, 0.0f,

		1.5f, 0.3f, 1.0f, //2 triangle
	    1.0f, -0.5f, 0.3f,
		1.0f, 1.0f, 0.0f
	}; 

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
}