#version 330 core 

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 colors;
out vec3 FragColor;
uniform float scaling; 
//A constant variable input data into the shader, which can be modified at runtime via source code.
//DON'T PUT UNDERSCORES IN NAMES OR THE GLGETUNIFORM WILL FAIL

void main()
 {
     gl_Position = vec4(scaling * Position.x, scaling * Position.y, Position.z, 1.0);
     //alternative writing: gl_Position.xyzw = vec4(scaling * Position, 1.0);
     FragColor = colors;
 }
