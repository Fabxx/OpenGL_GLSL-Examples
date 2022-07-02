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

void VertexUVMapping()
{
// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
	static const GLfloat g_uv_buffer_data[] = 
	{
		0.000059f, 1.0f-0.000004f,
		0.000103f, 1.0f-0.336048f,
		0.335973f, 1.0f-0.335903f,
		1.000023f, 1.0f-0.000013f
	};

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size of vector (UV is 2D vector)
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

}