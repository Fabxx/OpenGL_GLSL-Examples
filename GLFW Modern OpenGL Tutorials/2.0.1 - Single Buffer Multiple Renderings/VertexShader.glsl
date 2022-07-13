#version 330 core

layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec3 Colors;

out vec3 color;

void main()
{
    gl_Position = vec4(Vertices, 1.0);

    color = Colors;
}