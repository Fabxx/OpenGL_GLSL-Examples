#include "0Common_headers.hh"
#include "3ScaleMatrix.hh"

//Matrix that Scales the object, can be done statically or dynamically
void ScaleMatrix()
{
	static float ScalingValue = 0.0f;
	static float scale = 0.005f;
	ScalingValue -= scale;

	if (ScalingValue >= 90.0f)
	{
		scale *= -1.0f;
	}

	/** FOrmula Details:
	 **The first line creates a new 4-by-4 matrix and initializes it to the identity matrix. 
	 **The glm::scale function applies a "scale"  transformation of "ScalingValue" on one of the three axes. 
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
	ScaleMatrix = glm::scale(ScaleMatrix, glm::vec3(ScalingValue, 0.0f, 0.0f));

	glUniformMatrix4fv(Matrix_Scale_Location, 1, GL_TRUE, &ScaleMatrix[0][0]);
}