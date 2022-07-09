#version 330 core 

 layout (location = 0) in vec3 Vertex_Coordinates;
 layout (location = 1) in vec2 TextureData; //2D texture with XY coordinates.
 
 out vec2 Texture;
 
 void main()
 {
     gl_Position = vec4(Vertex_Coordinates, 1.0);
     Texture = TextureData;
 }