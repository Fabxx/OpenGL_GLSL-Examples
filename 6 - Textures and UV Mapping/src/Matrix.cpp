#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Matrixes.hh"

;void projection_Matrix(GLuint *programID)
{
	GLuint MatrixID = glGetUniformLocation(*programID, "Triangle1");
	glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	
	glm::mat4 View = glm::lookAt(glm::vec3(4,2,2), glm::vec3(0,0,0), glm::vec3(2,4,4));
												 
	glm::mat4 Model      = glm::mat4(1.0f);

	glm::mat4 MVP        = Projection * View * Model; 

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}
