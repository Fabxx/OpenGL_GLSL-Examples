#version 330 core 


 layout (location = 0) in vec3 Position;
 uniform mat4 TransformMatrix; //4x4 matrix

 void main()
 {
    //updating 4D vector position with 4X4 Matrix values, which represent on it's own a 4D vector as well.
    //!MULTIPLY IN THIS ORDER, NEVER OTHER WAY AROUND.
     gl_Position = TransformMatrix * vec4(Position, 1.0);
 }