#version 330 core //minimum GL version check

/** PROFILE ARGUMENT
 ** LAYOUT: Takes the vertex attrib pointer we initialized to the 0 index, so it loads the attributes of 0.
**  Position: our first attribute of the vertexes.
**  "in" indicates this 3D vector take data in input
    It is better to retreive the index from the compiled shader to make it more generic, instead of binding everything
    to 0.
 */

 layout (location = 0) in vec3 Position;


 void main()
 {
    /** DETAIL:
    ** gl_Position is a built-in function to calculate the position attribute
    ** vec4 is used to store x, y, z and w, the first three are the vertices coordinates,
    ** if w = 1, it indicates that it's a position on screen, if w = 0, it's a direction.
    ** The position axes are filled via the VBO which contains the float values of the three axis, 
    ** retreived via the GL_ARRAY_BUFFER on vertex buffer attrib pointer on 0.
    ** The GL_ARRAY_BUFFER took these from the VBO:
    ** Vertices[x] =   {1.0f, -1.0f, 0.0f};
    ** Vertices[y] =   {-1.0f, 1.0f, 0.0f};
    ** Vertices[z] =   {0.0f, 1.0f, 0.0f};
    ** THen the rasterizer look into gl_Position to calculate the visible pixels on screen.
    
    */
     gl_Position = vec4(Position.x, Position.y, Position.z, 1.0);
 }