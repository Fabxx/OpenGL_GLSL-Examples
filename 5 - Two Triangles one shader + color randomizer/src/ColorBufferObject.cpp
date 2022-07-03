#include <GL/glew.h>
#include <GL/gl.h>
#include "ColorBufferObject.hh"
#include "ColorRandomizer.hh"
#include <iostream>

GLuint colorbuffer;


void ColorBufferObjects()
{
	static GLfloat g_color_buffer_data[18];

	gencolors(g_color_buffer_data);
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}

void ColorBufferCOmpute()
{
	 glEnableVertexAttribArray(1);
	 glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	 glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
}