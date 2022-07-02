#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.hh"
#include "Zbuffer_check.hh"
#include "VertexArrayObjects.hh"
#include "Matrixes.hh"
#include "Texture_Readers.hh"
#include "Mipmapping_filtering.hh"


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
	texture data;
	DDSTexture data2;

	do 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID); //initialize shader handler
		check_zbuffer();
		VertexArrayObjects();
		VertexUVMapping();
		DDSReader(&data2);
		//BMPreader(&data); use if working with BMP image
		DDS_texture_maker(&data2);
		//Mipmapping(); use with BMP
		projection_Matrix(&programID);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	return 0;
}