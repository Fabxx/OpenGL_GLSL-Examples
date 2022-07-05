#include "0Common_headers.hh"
#include "0VBO_init.hh"
#include "1Shader_Compiler.hh"
#include "2Display_Renderer_Init.hh"

GLuint VBO;
GLint Matrix_Rotation_Location;

//Matrix that rotates the camera, can be done statically or dynamically
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
	 ** We take a 4x4 matrix and init to 1.0f for all values.
	 ** we then pass the rotation matrix initialized, and we specify in degree how much we want to rotate
	 ** Then, we choose on which axis we want to rotate, if XYZ.
	 ** Here using 0.0, .1, or directly 1.0 gives the same result, since we're rotating with a 
	 ** static value anyways. In this example, i'm rotating on the Z axis, but in fact, the shape rotates on X and Y
	 ** axis, the Z remains constant, because of how the prespective works. Note that in this case rotating on X
	 ** and Y axis will produce a blank screen, because this is not a 3D object, but a simple vertex.
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