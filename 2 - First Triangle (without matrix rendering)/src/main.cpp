#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.hh"
#include "VertexArrayObject.hh"

int window_init()
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID); //initialize shader handler
		VertexArrayObject(); //call whatever you want to create and apply the effects over it.
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	return 1;
}


int main(void)
{
	window_init();
}