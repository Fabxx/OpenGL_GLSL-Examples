#include "Buffer_Array_Object_Init.hh"

void CreateVertexBuffer()
{
	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f, 
		1.0f, -1.0f, 0.0f,
   		0.0f,  1.0f, 0.0f 
	};
  
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void CreateColorBuffer()
{
  /** Explaination
   **Remember when we did the interpolation via Shader? it's basically the equivalent of
   **Creating a buffer of colors, where for each vertex we have a RGB value. Then we bind the buffer
   **to an index, and we pass it to the shader via "layout", just like a vertex buffer. 
   **NOTE: for the colors it's not necessary a Color Array object, because these are not vertices to be drawed
   **but just float RGB values to be applies on the drawed vertices via shader.
   **DO NOT bind the colors on a VAO, or else the verices will be discarded. only one VAO buffer
   **can be loaded during runtime, and having colors without vertices doesn't make any sense.
   **/
   
   /**
   **If we have 1 triangles, and a triangle has 3 vertices, and each vertex has 3 RGB values:
   **3x3 = 9 RGB values for 1 triangle. 
   **For a cube: 12*3 = 36 Vertices, 36*3 RGB values = 108.
   */

  static GLfloat g_vertex_color_buffer[] =  
  {
    1.0f, 0.0f, 0.0f, //x is setted to RED RGB
    0.0f, 1.0f, 0.0f, //y is setted to GREEN RGB
    0.0f, 0.0f, 1.0f  //z is setted to BLUE RGB
  };

  glGenBuffers(1, &CBO);
  glBindBuffer(GL_ARRAY_BUFFER, CBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_color_buffer), g_vertex_color_buffer, GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
