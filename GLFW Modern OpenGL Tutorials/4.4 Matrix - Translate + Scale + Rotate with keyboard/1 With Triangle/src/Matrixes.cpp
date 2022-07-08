#include "Common_headers.hh"
#include "Matrixes.hh"

void OutputMatrix(GLFWwindow *window)
{

	static float xscale = 0.0f, yscale = 0.0f;
	static float XAngle = 0.0f, YAngle = 0.0f, ZAngle = 0.0f;
	static float xtranslate = 0.0f, ytranslate = 0.0f;
	//ALWAYS INIT THE MATRIXES YOU HAVE TO MULTIPLY, PLUS A MATRIX TO CONTAIN THE MULTIPLICATION OF ALL THREE.
	glm::mat4 Translate = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);
	glm::mat4 RotateZ = glm::mat4(1.0f);
	glm::mat4 BaseMatrix = glm::mat4(1.0f);

	//Scaling params

	if (glfwGetKey(window, GLFW_KEY_D))
	{
		xscale += 0.005f;
	}

	//Note X inverted because glm::translate inverts X and Y.
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		xscale -= 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		yscale += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_S))
	{
		yscale -= 0.005f;
	}

	//Rotation param, only Z for 2D object

	if (glfwGetKey(window, GLFW_KEY_J))
	{
		ZAngle += 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_K))
	{
		ZAngle -= 0.5f;
	}
	

	//Translation params

	if (glfwGetKey(window, GLFW_KEY_KP_4))
	{
		xtranslate -= 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_6))
	{
		xtranslate += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_8))
	{
		ytranslate += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_2))
	{
		ytranslate -= 0.005f;
	}

	Translate = glm::translate(Translate, glm::vec3(xtranslate, ytranslate, 0.0f));
	Scale = glm::scale(Scale, glm::vec3(xscale, yscale, 0.0f));
	RotateZ = glm::rotate(RotateZ, glm::radians(ZAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	
	BaseMatrix = Translate * RotateZ * Scale;

	glUniformMatrix4fv(Matrix_Output_Location, 1, GL_FALSE, &BaseMatrix[0][0]);
}