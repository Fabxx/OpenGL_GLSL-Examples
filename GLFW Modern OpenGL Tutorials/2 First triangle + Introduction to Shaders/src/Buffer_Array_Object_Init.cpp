#include "Buffer_Array_Object_Init.hh"

void CreateVertexBuffer()
{
	//A vertex is composed of 3 screen coordinates: X, Y and Z. we need an array to store these coordinates.
	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f, //bottom left
		1.0f, -1.0f, 0.0f, //bottom right
   		0.0f,  1.0f, 0.0f //top
	};

  

/**loads the attributes of our vertexes into the VBO.
  In Detail:
  **We first generate one buffer that can store data into VBO
  ** We bind this target to openGL via GL_ARRAY_BUFFER: indicates that the vertex values have to be packed as an array.
  ** Note: once this buffer is binded, it gives a pointer to openGL where to write the data, but if you bind another buffer
  ** soon after the first bind function with another VBO, the last binded VBO will be the one where you write the data.
  **See chapter 2.1 for Vertex Buffer and Array object handling.
  ** Writing data into this buffer following these arguments:
  **-Size of the buffer in bytes
  **-Pointer to the buffer
  **-GL_STATIC_DRAW: populate the buffer once, and use it multiple times
  **/
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  
/**
   **We Generated a buffer on VBO which contans a block of data representing our vertices, but GL doesn't know what this data is yet
   **So, we first bind the VBO with the data to be sended, then we generate an object that tells to GL, that this is an Array of
   **vertices with the attributes and coordinates, the VAO (Vertex Array Object). It works as an interpreter of the data stored in the buffer.
   **Then when we bind the vertex array, we're going to render it. We can bind the VAO when we want, not necessarily after the generation.
   */
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
//Handles the attributes for the current binded vertex buffer (in this case, coordinates, at index 0, colors can be at index 1 etc)
//each vertex attribarray and pointer, gives an indexing to the attributes to be used in the shader, via a layout number.
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

   //!DO NOT BIND THE BUFFERS AGAIN ELSEWHERE, BIND THEM ONLY WHERE YOU INITIALIZE THEM.
  
  /** In Detail:

** 0 is the index given before
** 3 is the size of the vector (3 for 3D, 2 for 2D etc)
** GL_FLOAT Indicates that we have float values in the buffer, and must be interpreted like so.
** GL_FALSE Tells GL to NOT normalize the data to 0 to 1 or -1
** 0 Is the Stride, number of bytes to the next occurrence of this attribute
** 0 Pointer, treated as integer, offset from the beginning of the buffer to the occurred instance of the attribute

EXAMPLE STRIDE
**OFFSET 0 (position of vertices): [][][]  
**OFFSET 12 (texture coordinates) [][][]
**OFFSET 20 (color) [][]  

**each block is 4 bytes, the coordinates start at byte 12, color at byte 20. the stride will be at 32 bytes total
**and the distance number from the offset to the stride will be 32 in the last pointer, this one will increase at runtime,
**when we have an occurrency of the vertex attributes.
**We put stride to 0 since in our case, we start with the attribs from the beginning of the buffer.
**/ 

/*
Draw points, pass data from the buffer to the pipeline via shading units and goes to the reasterizer.
*The rasterizer checks that the vertex position is in a visible part of the screen, and it maps it to the correspondent pixels
In Detail:
*GL_TRIANGLES: Tells to GL how to interprete the primitive type, in this case a single triangle, which is made by three vertices
			*(here we have a triangle with XYZ vertices)

*Index of the vertex to draw, tells from which vertex we have to start to draw
*Number of vertices to draw (in this case 3) */
}
