#version 330 core

in vec4 FragColor; //copying color from Vertex Shader.
out vec4 interpolatedColors;

void main()
{
  interpolatedColors = FragColor;
}