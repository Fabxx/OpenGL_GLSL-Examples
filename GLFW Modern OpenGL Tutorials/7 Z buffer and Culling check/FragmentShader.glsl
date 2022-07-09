#version 330 core
/**
 **  Note that when this fragment shader is called, this already knows the data from the VertexShader and which
 **  pixels to handle. IN this case, color will have RGBA values to color the pixels we've elaborated.
 ** the vector is declared as "out", meaning that from that vector will be outputted colored vertices 
 ** from VertexShader.glsl
 */
out vec4 color;

void main()
{
  /**
  **When we use a single vec4/vec3 vector for colors, each value represents directly an axis
  **if we use a vec4/vec3 of [3]/[4] size, we have 3/4 3D/4D vectors, each vector will represent
  **an axis, and each axis will have three RGB components instead, because we're initializing the 
  **color for the axes individually, see the Vertex Interpolation in shader/source code chapter.
  */
  color = vec4(0.0,0.5,0.7,0.0);
}