#include "Buffer_Array_Object_Init.hh"

void VertexCoordinates()
{
  //Two set of vertices for each buffer.
	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 
   		0.0f,  1.0f, 0.0f 
	};

  static const GLfloat g_vertex_buffer_data_2[] =
  {
    -1.0f, 1.0f, 0.0f,
		1.0f, -0.5f, 0.0f, 
   	0.0f,  1.0f, 0.0f 
  };

  /** 
   **When we bind a buffer, we're giving a pointer to GL of where we have to write the data, soon
   **after glBindBuffer, we do glBufferData, which is going to write on the LAST BINDED buffer.
   **If i bind VBO[0] first and then VBO[1] before glBufferData, i'm not writing into VBO[0]
   **anymore, but into VBO[1]. So bind one buffer per time, and write the data into them.
   **The gen buffer has to be done at the beginning with the number of buffers to use.
   */ 

  glGenBuffers(2, VBO);

  //first buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  
  //second buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_2), g_vertex_buffer_data_2, GL_STATIC_DRAW);
  
  
  /** 
   **Same thing here but for attribute pointers and the Vertex Arrays, 
   **We bind the vertex array VAO[0] to the first buffer, we bind again VBO[0] 
   **instead of VBO[1] since this was the last one binded above, and we set up the 
   **attribute index to 0.
   **Then we set the attrib pointer which also points to the last binded buffer. 
   **with the index 0 it links the VAO[0] with the VBO[0],
   */
  
  glGenVertexArrays(2, VAO);

  glBindVertexArray(VAO[0]);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
  glBindVertexArray(VAO[1]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

}
