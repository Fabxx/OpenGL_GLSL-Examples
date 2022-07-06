#include "Common_headers.hh"
#include "Buffer_Array_Object_Init.hh"
#include "Shader_Compiler.hh"
#include "Display_Renderer_Init.hh"

GLuint VBO; //Vertex Buffer Object to be passed to openGL
GLuint VAO; //Vertex Array Object which tells OpenGL how to interpret the data.

int main(void)
{
	WindowInitRender();
	return 0;
}