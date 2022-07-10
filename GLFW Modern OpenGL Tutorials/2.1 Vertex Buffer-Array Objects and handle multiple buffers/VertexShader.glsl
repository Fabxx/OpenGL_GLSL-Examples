#version 330 core 

 layout (location = 0) in vec3 Vertex_Coordinates;

 const vec3 colors[3] = vec3[3](vec3(1.0, 0.0, 0.0),
                                vec3(0.0, 1.0, 0.0),
                                vec3(0.0, 0.0, 1.0));

out vec3 color;

 
 void main()
 {
     gl_Position = vec4(Vertex_Coordinates, 1.0);
     color = colors[gl_VertexID];
 }