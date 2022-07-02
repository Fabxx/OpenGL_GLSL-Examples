/*So yeah, vec3(1,0,0) means red. This is because on computer screens,
 colour is represented by a Red, Green, and Blue triplet, in this order. So (1,0,0) means Full Red, no green and no blue.*/
#version 330 core

in vec3 fragmentColor; //out means this data will be outputted to the object.
out vec3 color;

void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    color = fragmentColor;

}