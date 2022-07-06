#include "0Common_headers.hh"
#include "0VBO_init.hh"
#include "1Shader_Compiler.hh"
#include "2Display_Renderer_Init.hh"

GLuint VBO;
GLint Matrix_Translation_Location;

//Matrix that moves the vertices, can be done statically or dynamically
static void TranslationMatrix()
{
	static float move = 0.0f;
	static float multiplier = 0.005f;
	move += multiplier; //edit this value that will be used in the axis to see changes.

	if (move >= 1.0f)
	{
		move = 0.0f;
	}

	/** FOrmula Details:
	 **The first line creates a new 4-by-4 matrix and initializes it to the identity matrix. 
	 **The glm::translate function overwrites this matrix by a position transformation of "move" coordinate around the XY axis. 
	 **NOTE: glm::translate inverts the XY axes orientation, If the value is positive it will go Down-left if it's negative it will go up right. 
	 **see the glUniformMatrix4fv below.
	 **Remember that since the screen lies in the XY plane, and this is a 2D object the XY axes are the axes you want to move the object around.
	 **If you work with a 3D object you can move on the Z axis too. 
	 */

	glm::mat4 ViewMatrix = glm::mat4(1.0f);
	ViewMatrix = glm::translate(ViewMatrix, glm::vec3(scale, scale, 0.0f));

	/**Gives matrix to shader, in detail:
	 **glUniformMatrix4vf: gives to the shader a 4x4 matrix with float values
	 **Matrix_Translation_Location updates the matrix in the shader, just like the uniform. 
	 **1 number of matrixes that we send to the shader
	 **GL_TRUE indicates if we give the values in ROW order or COLUMN order. So the read order of
	 **the values changes with this orientation. FALSE reads by column, TRUE Reads by row.
	 **Memory address of the Matrix array. tells the start point of where it should load the 4x4 float values.
	 **NOTE: Setting to FALSE since glm::translate inverts the X and Y axis
	 */
	glUniformMatrix4fv(Matrix_Translation_Location, 1, GL_FALSE, &ViewMatrix[0][0]);

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutPostRedisplay();
	glutSwapBuffers();
}

int main(void)
{
	init_window();

	CreateVertexBuffer();
	CompileShaders();
	//Rendering matrix as main display.
	glutDisplayFunc(TranslationMatrix);
	glutMainLoop(); 

	return 0;
}
