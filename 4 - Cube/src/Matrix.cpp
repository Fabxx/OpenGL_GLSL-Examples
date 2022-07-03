#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Matrixes.hh"

GLuint MatrixID;
glm::mat4 View;
glm::mat4 MVPCube;

;void projection_MatrixCube(GLuint *programID)
{
	MatrixID = glGetUniformLocation(*programID, "MVPCube");
	glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	View       = glm::lookAt(
								glm::vec3(4,2,2), //camera positioning, centered cube. 
								glm::vec3(0,0,0), //centered to object
								glm::vec3(0,1,0)); //camera rotation.
	glm::mat4 Model      = glm::mat4(1.0f);
	MVPCube        = Projection * View * Model;
	
}

void MatrixCompute()
{
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVPCube[0][0]);
}