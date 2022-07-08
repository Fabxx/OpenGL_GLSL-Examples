#include "CameraMatrix.hh"

void CameraMatrix(GLFWwindow *window)
{
	/**
	**In Details:
	**We first initialize a projection matrix, which contains this data:
	**-Field of View = increased/decreases the visibility field
	**-Aspect Ratio (4:3, 16:9 etc)
	**-Number of units that can be saw.
 */
	//Camera Prespective Setup.
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	/** 
	**Then we have the View Matrix:
	**-We first set the position on screen of the camera
	**-We Center it to the screen.
	**-The final vector handles the camera movement on XYZ.
 */
	// Camera matrix
	static float x = 0.0f, y = 0.0f, z = 0.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_6))
	{
		x += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_4))
	{
		x -= 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_8))
	{
		y += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_2))
	{
		y -= 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_9))
	{
		z += 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_7))
	{
		z -= 0.1f;
	}

	glm::mat4 View = glm::lookAt(
		glm::vec3(5,5,5), 
		glm::vec3(0,0,0), 
		glm::vec3(x, 0.1f + y,z)  //+0.1 to  make the cube appear on the initial view
		);
	
	/** 
	 **Next, the model matrix, a simple matrix initialized at 1.0f, that will be multiplied
 	 **with the vertices vector in shader.
 */
	// Model matrix 
	glm::mat4 Model = glm::mat4(1.0f);

	// Our ModelViewProjection (aka Final Camera) : multiplication of our 3 matrices
	glm::mat4 ModelViewProjection = Projection * View * Model; // Remember, matrix multiplication is the other way around

	glUniformMatrix4fv(Matrix_Camera_Location, 1, GL_FALSE, &ModelViewProjection[0][0]);
}