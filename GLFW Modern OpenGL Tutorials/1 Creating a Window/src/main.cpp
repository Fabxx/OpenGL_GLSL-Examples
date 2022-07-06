#include <iostream>
#include <GLFW/glfw3.h>

//The main rendering we're gonna loop.
static void RenderSceneCB()
{
	//colors clamped by the system, with 0.0 to 1.0 Range, these apply the background color
	//use these if you want to cahnge the RGBA values individually and display only one color.
	//GLclampf Red = 0.0f, Green = 0.5f, Blue = 0.7f, Alpha = 0.0f;
	//glClearColor(Red, Green, Blue, Alpha);

	static GLclampf RGBA = 0.0f;
	glClearColor(0, 0.5, RGBA, 0);
	
	//To cover all range colors, standard RGBA is 8 bit, 2^8 = 256 combinations. 
	RGBA += 1.0f / 256.0f;

	if (RGBA >= 0.7f) //You can regulate this range how you want, higher the value is, more combinations will be displayed.
	{
		RGBA = 0.0f;
	}
	//cleans the screen to avoid junk and starts rendering again.
	glClear(GL_COLOR_BUFFER_BIT);
}

//To keep GLFW viewport in buffer while moving/resizing.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//main loop, put the final window rendering here.
	while(!glfwWindowShouldClose(window))
	{
		RenderSceneCB(); //our output looped.
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
	glfwTerminate();
}

int main(void)
{
	WindowInitRender();
	return 0;
}