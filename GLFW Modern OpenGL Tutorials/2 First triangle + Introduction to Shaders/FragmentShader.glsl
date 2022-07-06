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
  **If using one vector for color output, we give one color for XYZ.
  **If we use one vector for each axis, we give three different colors in XYZ-
  **see Vertex Interpolation chapter.
  */
  color = vec4(0.0,0.5,0.7,0.0);
}
