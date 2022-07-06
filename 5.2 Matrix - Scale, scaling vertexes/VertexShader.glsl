#version 330 core 


 layout (location = 0) in vec3 Position;
 uniform mat4 ScaleMatrix; 

 void main()
 {
     gl_Position = ScaleMatrix * vec4(Position, 1.0);
 }