//Let’s write our vertex shader first. The first line tells the compiler that we will use OpenGL 3’s syntax.

#version 330 core

//The second line declares the input data :

/*
Let’s explain this line in detail :

“vec3” is a vector of 3 components in GLSL. It is similar (but different) to the glm::vec3 we used to declare our triangle. 
The important thing is that if we use 3 components in C++, we use 3 components in GLSL too.
“layout(location = 0)” refers to the buffer we use to feed the vertexPosition_modelspace attribute. 
Each vertex can have numerous attributes : A position, one or several colours, one or several texture coordinates, lots of other things. 
OpenGL doesn’t know what a colour is : it just sees a vec3. So we have to tell him which buffer corresponds to which input. 
We do that by setting the layout to the same value as the first parameter to glVertexAttribPointer. The value “0” is not important, 
it could be 12 (but no more than glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v) ), the important thing is that it’s the same number on both sides.
“vertexPosition_modelspace” could have any other name. It will contain the position of the vertex for each run of the vertex shader.
“in” means that this is some input data. Soon we’ll see the “out” keyword.
*/

layout(location = 0) in vec3 vertexPosition_modelspace;

//function for each vertex
/*
Our main function will merely set the vertex’ position to whatever was in the buffer. So if we gave (1,1), the triangle would have one of 
its vertices at the top right corner of the screen. We’ll see in the next tutorial how to do some more interesting computations on the input position.
*/

/*Basically the vertex shader occupies to put data on the screen, handling positions etc, Fragment shader handles
the ATTRIBUTES of the shader, textures, colors given, etc */

void main()
{
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
    
   //gl_Position is one of the few built-in variables : you *have *to assign some value to it. Everything else is optional; we’ll see what “everything 
}
