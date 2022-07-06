#include "Common_headers.hh"
#include "Update_Uniforms.hh"

//updates the uniform value in the shader
/**
 **Now we can update dinamically (or statically, depending how we program the function)
 **the uniform value in the shader, instead of having a hardcoded value
 **wich couldn't be changed at runtime in GLSL vertex shader.  
 **glUniform1f it's used to access uniform data in GLSL files, and update them.
 **Here we are updating the uniform retreived from the shader.
 **NOTE: this is equivalent to the scaling matrix, but it's more redundant to handle all the axes.
 **you need 3 float uniforms in the shader in this case if you want to edit the XYZ axis
 **with the matrix you just multiply the matrix with a vector3, and in that vector you replace
 **the float with the value you want to multiply with.
*/ 

void UpdateUniforms()
{
	//Populating uniform here
	static float scale = 0.0f;
	static float scaling_apply = 0.005f;
    
	scale += scaling_apply;

	if ((scale >= 1.0f) || (scale <= -1.0f))
	{
		scaling_apply *= -1.0f;
	}

	glUniform1f(uniform_location, scale);
}
