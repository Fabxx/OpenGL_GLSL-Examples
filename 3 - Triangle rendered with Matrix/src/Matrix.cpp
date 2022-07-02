#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Matrixes.hh"

/*
Homogeneous coordinates

Until then, we only considered 3D vertices as a (x,y,z) triplet. Let’s introduce w. We will now have (x,y,z,w) vectors.

This will be more clear soon, but for now, just remember this :

    If w == 1, then the vector (x,y,z,1) is a position in space.
    If w == 0, then the vector (x,y,z,0) is a direction.

(In fact, remember this forever.)

What difference does this make ? Well, for a rotation, it doesn’t change anything. When you rotate a point or a direction, you get the same result. 
However, for a translation (when you move the point in a certain direction), things are different. What could mean “translate a direction” ? 
Not much.

Homogeneous coordinates allow us to use a single mathematical formula to deal with these two cases. We simply use a multiplication with matrixes.

In 3D graphics we will mostly use 4x4 matrices. They will allow us to transform our (x,y,z,w) vertices. 
This is done by multiplying the vertex with the matrix :

Matrix x Vertex (in this order !!) = TransformedVertex whichi is done with column element by row element.

a b c d		x  multiplication = ax by cz
e f g h		y			        ex fy gz
		    z
*/

/*
Translation matrices

These are the most simple tranformation matrices to understand. A translation matrix look like this :

where X,Y,Z are the values that you want to add to your position.

So if we want to translate the vector (10,10,10,1) of 10 units in the X direction, we get:

1 0 0 10	x  multiplication = 1*x + 0*y + 0*z + 10*w --> 1x + 0y + 0z + 10w  --> 11
0 0 1 0		y					0*x + 0*y + 1*z + 0*w	   0x + 0y + 1z + 0w	   1	
0 1 0 0		z			        0*x + 1*y + 0*z + 0*w      0x + 1y + 0z + 0q       1
0 0 0 1		w					0*x + 0*y + 0*z + 1*w 	   0x + 0y + 0z + 1w       1
			

			*/

/*This is a projection matrix that basically includes all the scale/rotation/camera matrixes, following the same calculation logic.
  WHat this matrix does, is handling the output rendering based on the camera prespective setted here, instead of just rendering the triangle
  on full screen with the classic gl_Position.xyz and w. If you want to render multiple shapes in different positions, you have to use Geometry Shaders*/

// Get a handle for our "MVP" uniform
;void projection_Matrix(GLuint *programID)
{
	GLuint MatrixID = glGetUniformLocation(*programID, "MVP");

	// Projection matrix : first patameter is Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//The matrix modifies the view prespective of the VertexArrayObject we've created, so first the object is rendered, then adjusted.
	//The radians parameter moves the camera on the Z axis, moving the camera ahead or behind. 5.0 is in DEGREE. then converted to RAD
	glm::mat4 Projection = glm::perspective(glm::radians(5.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	// Or, for an ortho camera (the prespective is more far on the Z axis) :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(20,10,10), //this handles the camera positioning on XYZ screen coords.
								glm::vec3(0,0,0), // and looks at the origin, camera is centerd to screen.
								glm::vec3(0,-1,0)  // Head is up (set to 0,-1,0 to look upside-down)
												  /*this handles camera rotation on XYZ, value orientation:
													 negative x = left, positive x = right. 
													 negative y = upside down, positive y = normal view.
													 negative z = behind the object, positive z = ahead object
													 in World Space. NOTE: on x movement to right, the object might look squeezed,
													 that's because it the camera prespective moving to the right*/
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}
