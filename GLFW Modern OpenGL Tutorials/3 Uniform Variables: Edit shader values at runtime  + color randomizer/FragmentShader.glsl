#version 330 core

in vec4 FragColor; //Same name as out vector in VS to obtain it's data.
out vec4 outputColors;

void main()
{
  outputColors = FragColor;
}