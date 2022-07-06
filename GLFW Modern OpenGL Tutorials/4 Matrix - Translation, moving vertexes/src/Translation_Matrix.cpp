#include "0Common_headers.hh"
#include "3Translation_Matrix.hh"

//Matrix that moves the vertices, can be done statically or dynamically
void TranslationMatrix()
{
	static float scale = 0.0f;
	scale -= 0.005f; //edit this value that will be used in the axis to see changes.

	if (scale >= 1.0f)
	{
		scale = 0.0f;
	}

	if (scale <= -1.0f)
	{
		scale = 0.0f;
	}

	/** FOrmula Details:
	 **The first line creates a new 4-by-4 matrix and initializes it to the identity matrix. 
	 **The glm::translate function overwrites this matrix by a position transformation of "scale" coordinate around the Y axis. 
	 **Remember that since the screen lies in the XY plane, and this is a 2D object the XY axes are the axes you want to move the camera around.
	 **If you work with a 3D object you can move on the Z axis too. If the value is positive it will go Down-leftm if it's negative  it will go up right
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
}