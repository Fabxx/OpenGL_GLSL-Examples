#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){

    // Output color = color of the texture at the specified UV
    color = texture( myTextureSampler, UV ).rgb;
}

/*
Three things :

The fragment shader needs UV coordinates. Seems fair.
It also needs a “sampler2D” in order to know which texture to access (you can access several texture in the same shader)
Finally, accessing a texture is done with texture(), which gives back a (R,G,B,A) vec4. We’ll see about the A shortly.
*/