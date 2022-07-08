#version 330 core

layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec3 Colors;

out vec3 FragColor;
uniform mat4 Camera;
                    
void main()
{
    gl_Position = Camera * vec4(Vertices, 1.0);
    FragColor = Colors;
}