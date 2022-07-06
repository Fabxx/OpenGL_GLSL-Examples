#include "Common_headers.hh"
#include "Buffer_Array_object_init.hh"
#include "Shader_Compiler.hh"
#include "Display_Renderer_Init.hh"
#include "Update_Uniforms.hh"

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

	//Our non looping functions
	CreateVertexBuffer();
	CompileShaders();

	//main loop
	while(!glfwWindowShouldClose(window))
	{
		UpdateUniforms();

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
	glfwTerminate();
}