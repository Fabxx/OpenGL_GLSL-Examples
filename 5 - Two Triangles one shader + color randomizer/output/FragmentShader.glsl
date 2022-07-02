/*So yeah, vec3(1,0,0) means red. This is because on computer screens,
 colour is represented by a Red, Green, and Blue triplet, in this order. So (1,0,0) means Full Red, no green and no blue.*/
#version 330 core

in vec3 FragmentColor;
out vec3 color; //out means this data will be outputted to the object.


void main()
{
    /*Color range is from 0 to 1 floating point (0.1, 0.2 ecc)*/
 color = FragmentColor;

}