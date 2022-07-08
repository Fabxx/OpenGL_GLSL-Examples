#include "Buffer_Array_Object_Init.hh"

/**
 ** The index buffer it's used to remove duplicated vertices that are not active, but still loaded by the GPU.
 ** We initialize the IBO, and we do indexing on the vertices to discard the unused duplicated
 ** And keep only the current active vertices. Considering the total byte size of the draw with UV mapping, vertices,
 ** etc, multiplied by the numer of vertices, we save a lot of Memory.
 **NOTE: With the introduciton of VBOs in GL, this is done automatically, it's just to show how it works.
 * */

void CreateIndexBuffer()
{
  static const GLuint g_index_buffer_data[] =
  {
    /** 
      **0 is the origin for each vertex, 
      **2 and 1 indicate the first vertex, note how we follow the numerical order as we go,
      **3 is linked with 2, 4 linked with 3 etc.
    */
    0, 2, 1, 
    0, 3, 2,
    0, 4, 3,
    
    0, 5, 4,
    0, 6, 5,
    0, 7, 6,
    
    0, 8, 7,
    0, 9, 8,
    0, 10, 9
  };
  //*GL_ELEMENT_ARRAY_BUFFER indicates to openGL that this is a index buffer.
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_index_buffer_data), g_index_buffer_data, GL_STATIC_DRAW);
}
void CreateVertexBuffer()
{
	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
   	0.0f,  1.0f, 0.0f,
     
      -1.0f, -1.0f, 0.0f,
		  1.0f, 1.0f, 0.0f,
   		0.0f,  1.0f, 0.0f,

      1.0f, -1.0f, 0.0f,
		  1.0f, 1.0f, 0.0f,
   		0.0f,  1.0f, 0.0f,
	}; 

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  glCreateVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
