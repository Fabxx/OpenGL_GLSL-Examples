#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.hh"
#include "Check_ZBuffer.hh"
#include "VertexArrayObjects.hh"
#include "ColorBuffer.hh"
#include "Matrixes.hh"

;int main(void)
{
	glewExperimental = true;
	if (!glfwInit())
	{
		fprintf(stderr, "Failed GLFW init\n");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	GLFWwindow *window;
	window = glfwCreateWindow(800, 600, "First Window", NULL, NULL);

	if (window == NULL)
	{
		fprintf(stderr, "Window failed!\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to init GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	GLuint programID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl");
	
	do 
	{
		/*It overdraws the “near” one, even though it’s supposed to be behind it ! This is what happens with our cube : 
		some faces are supposed to be hidden, but since they are drawn last, they are visible. 
		Let’s call the Z-Buffer to the rescue ! 
		The solution to this problem is to store the depth (i.e. “Z”) component of each fragment in a buffer, 
		and each and every time you want to write a fragment, you first check if you should 
		(i.e the new fragment is closer than the previous one).*/
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID); //initialize shader handler
		check_zbuffer();
		VertexArrayObjects(); //!HAS TO BE DONE BEFORE CALLING OTHER FUNCTIONS TO INIT THE BUFFERS.
		colorBuffer();
		projection_MatrixCube(&programID);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; draw 12*3 vertices total -> 12 triangles
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1); //!disabling the extra attribute.
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	return 0;
}