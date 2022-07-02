//Let’s write our vertex shader first. The first line tells the compiler that we will use OpenGL 3’s syntax.

#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

// Values that stay constant for the whole mesh.
uniform mat4 Triangle1;
out vec3 FragmentColor;

void main() {

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  Triangle1 * vec4(vertexPosition_modelspace,1);
	FragmentColor = vertexColor;
}