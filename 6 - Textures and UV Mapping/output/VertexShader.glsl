//The vertex shader is simple too, you just have to pass the UVs to the fragment shader :

#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 Triangle1;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  Triangle1 * vec4(vertexPosition_modelspace,1);

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}
