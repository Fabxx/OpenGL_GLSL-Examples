#include "Common_headers.hh"
#include "ScaleMatrix.hh"

//Matrix that scales the object, can be done statically or dynamically
void ScaleMatrix()
{
	static float scale = 0.0f;

	scale += 0.005f;
	
	if ((scale >= 1.3f) || (scale <= -1.3f))
	{
		scale *= -1.0f; //invert triangle on rendering to make inverse scaling.
	}
	
	/** FOrmula Details:
	 **The first line creates a new 4-by-4 matrix and initializes it to the identity matrix. 
	 **The glm::scale function multiplies the 4x4 mat with a vec3 with a scale value. 
	 **If we scale only one axis, this is called "Non uniform scaling", because the axes don't match their coordinates.
	 **If we scale the axes all at the same time, we get a "Uniform scaling". 
	 **Scale applies a simple matrix multiplication with the vector:
	 **mat4 Result;
	 **Result[0] = m[0] * v[0]; x
	 **Result[1] = m[1] * v[1]; y
	 **Result[2] = m[2] * v[2]; z
	 **Result[3] = m[3]; w
	 */
	glm::mat4 ScaleMatrix = glm::mat4(1.0f);
	ScaleMatrix = glm::scale(ScaleMatrix, glm::vec3(scale, scale, 1.0f));

	glUniformMatrix4fv(Matrix_Scale_Location, 1, GL_TRUE, &ScaleMatrix[0][0]);
}
