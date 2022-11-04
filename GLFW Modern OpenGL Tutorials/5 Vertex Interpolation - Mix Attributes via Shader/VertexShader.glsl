#version 330 core //minimum GL version check


 layout (location = 0) in vec3 Position;

/**Making 3 3D vectors with RGB values, each vector is a vertex for x y and z.
 **the gl_VertexID indexes the colors for each vertex into one value, making a 
 **static smooth transition. (It's the same thing as the color randomizer, but in shader.)
 **I personally preferr to generate data in code, then let the shader just handle the data.
 **Basically all it does, is to apply a color combination to each vertex. That's what the interpolation is.
 **NOTE: use ocnst to initialize vars in shaders.
 */
const vec3 colors[3] = vec3[3] (vec3(1, 0, 0),
                            vec3(0, 1, 0),
                            vec3(0, 0, 1) );
out vec3 FragColor;
 void main()
 {
     gl_Position = vec4(Position.x, Position.y, Position.z, 1.0);
    FragColor = colors[gl_VertexID];
 }
