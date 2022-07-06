#include "0Common_headers.hh"
#include "0VBO_init.hh"
#include "1Shader_Compiler.hh"
#include "2Display_Renderer_Init.hh"

GLuint VBO;
GLint Matrix_Rotation_Location;

//Matrix that rotates the vertices, can be done statically or dynamically
static void RotationMatrix()
{
	static float AngleinRadians = 0.0f;
	static float angle = 0.500f;
	AngleinRadians += angle;

	if((AngleinRadians >= 90.0f) || (AngleinRadians <= -90.0f))
	{
		angle *= -1.0f;
	}

	/** FOrmula Details:
	 **The first line creates a new 4-by-4 matrix and initializes it to the identity matrix. 
	 **The glm::rotate function multiplies this matrix by a rotation transformation of "AngleinRadians" degrees around the Z axis. 
	 **Remember that since the screen lies in the XY plane, the Z axis is the axis you want to rotate points around.
	 **When you rotate the object, you have to keep XY positions unaltered, and just rotate the object via Z direction with a 2D object. 
	 **Draw a XY cartesian graph and add a Z axis in between,then draw a circle around the graph starting from the Z axis line, 
	 **you'll understand this better. 
	 */
	
	glm::mat4 RotationMatrix = glm::mat4(1.0f);
	RotationMatrix = glm::rotate(RotationMatrix, glm::radians(AngleinRadians), glm::vec3(0.0f, 0.0f, 1.0f));


	glUniformMatrix4fv(Matrix_Rotation_Location, 1, GL_TRUE, &RotationMatrix[0][0]);

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
	glutDisplayFunc(RotationMatrix);
	glutMainLoop(); 

	return 0;
}
