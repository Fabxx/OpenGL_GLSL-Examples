#include "0VBO_init.hh"

void CreateVertexBuffer(VertexBuffer *data)
{
	//A vertex is composed of 3 screen coordinates: X, Y and Z. we need an array to sotre these coordinates.
	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f, //will be displayed at coords -1 -1, can't be changed because it's built in GPU.
		1.0f, -1.0f, 0.0f,
   	0.0f,  1.0f, 0.0f
	}; //X, Y, Z, each 3 coords represent a vertex, modyfing these will edit the vertex coordinates, not the size of the triangle

  //Generate a buffer on VBO, and attach it to the GPU, then write the coordinates from vertex to the buffer attached.
  glGenBuffers(1, &data->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, data->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}