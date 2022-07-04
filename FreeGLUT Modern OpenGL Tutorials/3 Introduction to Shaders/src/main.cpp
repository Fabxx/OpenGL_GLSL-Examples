#include "0Common_headers.hh"
#include "0VBO_init.hh"
#include "1Shader_Compiler.hh"
#include "2Display_Renderer_Init.hh"

//Retreive buffer data
static void RenderBufferObject(VertexBuffer *data)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, data->VBO); //converting pointer to normal int just for reference pass.
}

//send data to Display.
static void RenderDisplay()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

int main(void)
{
	VertexBuffer data;
	init_window();
	CreateVertexBuffer(&data);
	CompileShaders();
	RenderBufferObject(&data);
	glutDisplayFunc(RenderDisplay);
	glutMainLoop(); 

	return 0;
}