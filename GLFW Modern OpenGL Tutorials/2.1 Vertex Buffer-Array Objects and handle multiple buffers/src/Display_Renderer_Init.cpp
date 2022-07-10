#include "Common_headers.hh"
#include "Buffer_Array_Object_Init.hh"
#include "Shader_Compiler.hh"
#include "Display_Renderer_Init.hh"
#include "Bind_VAO_render.hh"

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

	VertexCoordinates();
	CompileShaders();

	int VAOLoaded = 0;


	//main loop
	while(!glfwWindowShouldClose(window))
	{
		BindVAO(window, &VAOLoaded);
		glClear(GL_COLOR_BUFFER_BIT);
		//If the current binded buffer is the first VAO draw it, else the second VAO.
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
	glfwTerminate();
}
