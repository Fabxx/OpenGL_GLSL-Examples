#version 330 core

layout (location = 0) in vec3 Vertices;

void main()
{
    gl_Position = vec4(Vertices, 1.0);
}