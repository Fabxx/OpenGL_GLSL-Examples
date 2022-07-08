#version 330 core

layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec3 colors;

uniform mat4 Output;
uniform mat4 Camera;
out vec3 FragColor;

void main()
{
    gl_Position = Camera * Output * vec4(Vertices, 1.0);
    FragColor = colors;
}