#include "Common_headers.hh"
#include "ScaleMatrix.hh"

//Matrix that rotates the object, can be done statically or dynamically
/**
  **The scaling is binded to the mouse, we get the XY coordinates, and we divide them by the max 
  **width and max height to get the correct orientation. If you want to unbind it form the mouse, 
  **you can use the getkey function and bind it to the keyboard, or, simply put a statically increasing
  **value on the axis you want.
*/
void ScaleMatrixMouse(GLFWwindow *window)
{
	static int width = 0, height = 0;
	static double scalex = 0.0f;
	static double scaley = 0.0f;
	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &scalex, &scaley);
	scalex /= width;
	scaley /= height;

	glm::mat4 ScaleMatrix = glm::mat4(1.0f);
	ScaleMatrix = glm::scale(ScaleMatrix, glm::vec3((float)scalex, (float)scaley, 1.0f));

	glUniformMatrix4fv(Matrix_Scale_Location, 1, GL_FALSE, &ScaleMatrix[0][0]);
}

/** 
 **This is the scaling with keybaord, the keyboard unlike the mouse is handled statically
 **since the values increase only when we press the button. We handle the increase/decrease
 **on the x and y axes by following the standard WASD, where A and D follow X axis, W and S 
 **follow the Y axis
 
 */ 
void ScaleMatrixKeyboard(GLFWwindow *window)
{
	static float x = 0.0f, y = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_D))
	{
		x += 0.010f;
	}

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		x -= 0.010f;
	}

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		y += 0.010f;
	}

	if (glfwGetKey(window, GLFW_KEY_S))
	{
		y -= 0.010f;
	}

	glm::mat4 ScaleKeyboard = glm::mat4(1.0f);
	ScaleKeyboard = glm::scale(ScaleKeyboard, glm::vec3(x, y, 0.0f));

	glUniformMatrix4fv(Matrix_Scale_Location, 1, GL_FALSE, &ScaleKeyboard[0][0]);
}