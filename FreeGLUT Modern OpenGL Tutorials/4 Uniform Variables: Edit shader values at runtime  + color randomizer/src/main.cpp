#include "0Common_headers.hh"
#include "0CBO_init.hh"
#include "0VBO_init.hh"
#include "1Shader_Compiler.hh"
#include "2Display_Renderer_Init.hh"

GLuint VBO;
GLuint CBO;
GLint uniform_location;

//updates the uniform value in the shader
/**
 **Now we can update dinamically (or statically, depending how we program the function)
 **the uniform value in the shader, instead of having a hardcoded value
 **wich couldn't be changed at runtime in GLSL vertex shader.  
 **glUniform1f it's used to access uniform data in GLSL files, and update them.
 **Here we are updating the uniform retreived from the shader.
*/ 

static void UpdateUniforms()
{
	//Populating uniform here
	static float scale = 0.0f;
	static float scaling_apply = 0.005f;
    
	scale += scaling_apply;

	if ((scale >= 1.0f) || (scale <= -1.0f))
	{
		scaling_apply *= -1.0f;
	}

	glUniform1f(uniform_location, scale);
	CreateColorBuffer(); //overwriting buffer in loop for new colors at runtime.
	

	/** 
	 **If you want to loop an output, you have to put these functions with redisplay 
	 **inside the function you have to pass to glutDIsplayFunc,
	 ** DO NOT CALL THIS FUNCTION IN MAIN  EVEN IF YOU DON'T LOOP, JUST PASS IT TO THE DISPLAY 
	 ** OR ELSE YOU'LL DO IT TWICE!
	*/
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutPostRedisplay();
	glutSwapBuffers();
}

int main(void)
{
	//!DO NOT BIND THE BUFFERS AGAIN IN HERE, BIND THEM ONLY WHERE YOU INITIALIZE THEM (see VBO_init.cpp)
	init_window();
	CreateVertexBuffer();
	CompileShaders();
	glutDisplayFunc(UpdateUniforms);
	glutMainLoop(); 
	
	return 0;
}