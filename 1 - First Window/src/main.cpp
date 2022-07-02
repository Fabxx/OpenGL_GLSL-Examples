#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

int main(void)
{
	//First step: GLFW init.
	glewExperimental = true;
	if (!glfwInit())
	{
		fprintf(stderr, "Failed GLFW init\n");
		return -1;
	}

	//Creating the first window
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context

	GLFWwindow *window; //global for simplicity
	//actual window creation.
	window = glfwCreateWindow(800, 600, "First Window", NULL, NULL);

	if (window == NULL)
	{
		fprintf(stderr, "Window failed!\n");
		glfwTerminate();
		return -1;
	}
	//creating context by getting window
	glfwMakeContextCurrent(window);
	glewExperimental = true; //required by core.

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to init GLEW\n");
		return -1;
	}

	//window will close, we need to wait user input to make it close, in this example we check for input on keyboard with STICK keys.
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do 
	{
		//Clear the screen for each frame.
		glClear(GL_COLOR_BUFFER_BIT);

		//swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		//then check if the key is pressed or the window closed
	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}