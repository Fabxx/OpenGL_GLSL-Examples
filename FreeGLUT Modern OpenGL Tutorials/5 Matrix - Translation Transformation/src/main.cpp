#include "0Common_headers.hh"
#include "0VBO_init.hh"
#include "1Shader_Compiler.hh"
#include "2Display_Renderer_Init.hh"

GLuint VBO;
GLint Matrix_Translation_Location;

//Matrix that moves the camera, can be done statically or dynamically
static void TranslationMatrix()
{
	static float scale = 0.0f;
	static float multiplier = 0.005f;
	scale += multiplier; //edit this value that will be used in the axis to see changes.

	if (scale >= 1.0f)
	{
		scale = 0.0f;
	}

	glm::mat4 Matrix = 
	glm::mat4
	(
		1.0f, 0.0f, 0.0f, 0.0f, //x camera (left/right)
		0.0f, 1.0f, 0.0f, scale *2, //y camera (ahead/behind)
		0.0f, 0.0f, 1.0f, 0.0f, //z camera (up/down), 0.0 = 2D view, only left, right ahead, behind.
		0.0f, 0.0f, 0.0f, 1.0f  //w camera, always set at 1.0f
	);

	/**Gives matrix to shader, in detail:
	 **glUniformMatrix4vf: gives to the shader a 4x4 matrix with float values
	 **Matrix_Translation_Location updates the matrix in the shader, just like the uniform. 
	 **1 number of matrixes that we send to the shader
	 **GL_TRUE indicates if we give the values in ROW order or COLUMN order. So the read order of
	 **the values changes with this orientation. FALSE reads by column, TRUE Reads by row.
	 **Memory address of the Matrix array. tells the start point of where it should load the 4x4 float values.
	 */
	glUniformMatrix4fv(Matrix_Translation_Location, 1, GL_TRUE, &Matrix[0][0]);

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