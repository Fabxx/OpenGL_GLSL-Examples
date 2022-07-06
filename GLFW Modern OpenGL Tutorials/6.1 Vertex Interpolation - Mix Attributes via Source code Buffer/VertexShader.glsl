#version 330 core //minimum GL version check

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 colors;

out vec3 FragColor;
 void main()
 {
     gl_Position = vec4(Position.x, Position.y, Position.z, 1.0);
    FragColor = colors;
 }