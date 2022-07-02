//Let’s write our vertex shader first. The first line tells the compiler that we will use OpenGL 3’s syntax.

#version 330 core

// Input vertex data, different for all executions of this shader.
// If color attribute is 1, then the shader should treat this vector on the layout 1 with the color data.
layout(location = 1) in vec3 vertexColor;
layout(location = 0) in vec3 vertexPosition_modelspace;
out vec3 fragmentColor;
uniform mat4 MVPCube;

void main() {
	gl_Position = MVPCube * vec4(vertexPosition_modelspace,1);
	fragmentColor = vertexColor;
}