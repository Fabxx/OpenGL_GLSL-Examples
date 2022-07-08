#include "Common_headers.hh"
#include "Matrixes.hh"

/** 
 **WIth a cube we need to change our camera prespective, or else we will always see it in front, like a 2D object.
 */
void CameraAngle(GLFWwindow *window)
{
	static float x = 0.0f, y = 0.0f, z = 0.0f, angle = 45.0f;
	glm::mat4 View = glm::mat4(1.0f);
	glm::mat4 Projection = glm::mat4(1.0f); 
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 Camera = glm::mat4(1.0f);

	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		y += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		y -= 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		x += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		x -= 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_PAGE_UP))
	{
		z += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
	{
		z -= 0.005f;
	}

	Projection = glm::perspective(glm::radians(angle), 16.0f / 9.0f, 0.1f, 100.0f);
	View = glm::lookAt(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(x, y, z));
	Camera = Projection * View * Model; //Always follow this multiplication order for camera.

	glUniformMatrix4fv(Matrix_Camera_Location, 1, GL_FALSE, &Camera[0][0]);
	
}

void OutputMatrix(GLFWwindow *window)
{

	static float xscale = 0.0f, yscale = 0.0f, zscale = 0.0f;
	static float XAngle = 0.0f, YAngle = 0.0f, ZAngle = 0.0f;
	static float xtranslate = 0.0f, ytranslate = 0.0f;
	//ALWAYS INIT THE MATRIXES YOU HAVE TO MULTIPLY, PLUS A MATRIX TO CONTAIN THE MULTIPLICATION OF ALL THREE.
	glm::mat4 Translate = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);
	glm::mat4 RotateX = glm::mat4(1.0f);
	glm::mat4 RotateY = glm::mat4(1.0f);
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

	if (glfwGetKey(window, GLFW_KEY_Z))
	{
		zscale += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_Q))
	{
		zscale -= 0.005f;
	}


	//Rotation param, XYZ for 3D

	if (glfwGetKey(window, GLFW_KEY_I))
	{
		XAngle += 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_O))
	{
		XAngle -= 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_P))
	{
		YAngle += 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_L))
	{
		YAngle -= 0.5f;
	}

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
	Scale = glm::scale(Scale, glm::vec3(xscale, yscale, zscale));
	RotateZ = glm::rotate(RotateZ, glm::radians(ZAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	RotateX = glm::rotate(RotateX, glm::radians(XAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	RotateY = glm::rotate(RotateY, glm::radians(YAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	
	BaseMatrix = Translate * RotateX * RotateY * RotateZ * Scale;

	glUniformMatrix4fv(Matrix_Output_Location, 1, GL_FALSE, &BaseMatrix[0][0]);
}