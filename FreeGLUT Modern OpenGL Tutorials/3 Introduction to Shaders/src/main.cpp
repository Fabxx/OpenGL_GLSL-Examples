#include "0Common_headers.hh"
#include "0VBO_init.hh"
#include "1Shader_Compiler.hh"
#include "2Display_Renderer_Init.hh"

GLuint VBO;

//send data to Display. In this case we don't have to do a redisplay, and we can use these functions here without any 
//other data operation. If we wanted to update the view dinamycally, the operation must be inserted here with glfuncReDIsplay() (see Folder 4).

static void RenderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

int main(void)
{
	init_window();

	CreateVertexBuffer();
	CompileShaders();
	
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//Calling DIsplay rendering after everything has been buffered.
	glutDisplayFunc(RenderSceneCallBack);
	glutMainLoop(); 

	return 0;
}