#version 330 core
/**
 **  Note that when this fragment shader is called, this already knows the data from the VertexShader and which
 **  pixels to handle. IN this case, color will have RGBA values to color the pixels we've elaborated.
 ** the vector is declared as "out", meaning that from that vector will be outputted colored vertices 
 ** from VertexShader.glsl
 */
in vec4 FragColor;
out vec4 interpolatedColors;
void main()
{
  interpolatedColors = FragColor;
}