#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Matrixes.hh"

GLuint MatrixID;
glm::mat4 View;
glm::mat4 Model;
glm::mat4 MVP;


;void projection_Matrix(GLuint *programID)
{
	MatrixID = glGetUniformLocation(*programID, "Triangle1");
	glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	
	 View = glm::lookAt(glm::vec3(4,2,2), glm::vec3(0,0,0), glm::vec3(2,4,4));
												 
	 Model      = glm::mat4(1.0f);

	 MVP        = Projection * View * Model;
	
}

void MatrixCompute()
{
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}
