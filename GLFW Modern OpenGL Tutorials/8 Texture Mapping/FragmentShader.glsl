#version 330 core

out vec4 color;
in vec2 Texture;
uniform sampler2D Sampler; //sampler takes the texture data and outputs it. will give the colors to put on vertices.

void main()
{
  color = texture2D(Sampler, Texture); //we use texture2D function in this case.
}