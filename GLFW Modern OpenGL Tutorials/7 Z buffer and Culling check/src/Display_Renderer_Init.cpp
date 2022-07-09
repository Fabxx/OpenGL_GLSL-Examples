#include "Common_headers.hh"
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

	/** 
	 **Our Z buffer check and culling. Z is the depth buffer, and avoids that the vertices try to render on the same
	**buffer coordinates and cause glitchy graphics. Also avoids that vertices are drawed on top of each other.
	**The culling is used to calculate which vertices to render based on the camera visibility, if we can't see them
	**those are not rendered. This is usually used with 3D objects.
	*/
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glDepthFunc(GL_LESS);
	//glCullFace(GL_BACK); enable these functions to hide the triangle, saw as a back face.
	CreateVertexBuffer();
	CompileShaders();

	//main loop, put the final window rendering here.
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
	glfwTerminate();
}
