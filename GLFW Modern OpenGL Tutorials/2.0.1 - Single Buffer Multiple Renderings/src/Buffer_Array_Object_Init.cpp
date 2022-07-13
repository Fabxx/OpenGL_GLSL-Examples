#include "Buffer_Array_Object_Init.hh"

static void RandomizeColor(GLfloat values[])
{
	srand(time(0));

	for (size_t i = 0; i < 27; ++i)
	{
		values[i] = (float)rand()/(float)(RAND_MAX/1.0f);
	}
}

void ColorValues()
{
	static GLfloat g_color_buffer[27];

	RandomizeColor(g_color_buffer);

	glGenBuffers(1, &CBO);

	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer), g_color_buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

static void RandomizeVertex(GLfloat values[])
{
	srand(time(0));
	for (size_t i = 0; i < 9; ++i)
	{
		values[i] = (float)rand()/(float)(RAND_MAX/1.0f);
	}
}

void VertexCoordinates()
{
	static GLfloat g_vertex_buffer_data[9];

	RandomizeVertex(g_vertex_buffer_data);

  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  glGenVertexArrays(1, &VAO);
  /** 
   **since the vertex array will be binded here we won't have to do it in main like the 2.1 example.
   **But in this case i want to change the triangles each time to update the same buffer, instead of having multiple buffers
   **So i update in the loop when i press the A key.
   **NOTE: I't sbetter to work with multiple buffers once we understand how the Pipeline works, to improve the speed of the program.
   */
  glBindVertexArray(VAO);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
