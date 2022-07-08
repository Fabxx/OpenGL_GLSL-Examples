#include "Buffer_Array_Object_Init.hh"
#include "Shader_Compiler.hh"
#include "Display_Renderer_Init.hh"
#include "Matrixes.hh"

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
	CreateColorBuffer();
	CompileShaders();
	//Checking for Z depth buffer to avoid triangles to be drawn on each other. ANd check for culling to not draw only non visible vertices on the back.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);


	//main loop
	while(!glfwWindowShouldClose(window))
	{
		CameraAngle(window);
		OutputMatrix(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glfwSwapBuffers(window);
		glfwPollEvents();    
		
	}
	glfwTerminate();
}