#include "Buffer_Array_Object_Init.hh"
#include "Shader_Compiler.hh"
#include "Display_Renderer_Init.hh"

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0,width, height);
}

void WindowInitRender()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window;
    
	window = glfwCreateWindow(800, 600, "First Window", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Our non looping functions.
	CreateVertexBuffer();
	CreateIndexBuffer();
	CompileShaders();

	//main loop
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		/**
		 **2 is number of elemnts to draw. 
		 **Specifies the type of the values in indices. Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT. 
		 **0 is pointer to index buffer.
		 */
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();    
		
	}
	glfwTerminate();
}