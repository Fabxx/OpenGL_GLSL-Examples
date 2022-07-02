#include "Mipmapping_filtering.hh"

/*
    What is filtering and mipmapping, and how to use them

As you can see in the screenshot above, the texture quality is not that great. This is because in loadBMP_custom, 
we wrote :

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

This means that in our fragment shader, texture() takes the texel that is at the (U,V) coordinates, 
and continues happily. There are three techniques to improve this:

-Filtering: With linear filtering, texture() also looks at the other texels around, and mixes the colours according to 
the distance to each center. This avoids the hard edges seen above.

-Anisotropic Filtering: This one approximates the part of the image that is really seen through the fragment. For instance, if the following texture is 
seen from the side, and a little bit rotated, anisotropic filtering will compute the colour contained in the blue rectangle by taking a 
fixed number of samples (the “anisotropic level”) along its main direction.

-Mipmapping:Both linear and anisotropic filtering have a problem. If the texture is seen from far away, mixing only 4 texels won’t be enough. 
Actually, if your 3D model is so far away than it takes only 1 fragment on screen, ALL the texels of the image should be averaged to produce 
the final color. This is obviously not done for performance reasons. Instead, we introduce MipMaps :

At initialisation time, you scale down your image by 2, successively, until you only have a 1x1 image (which effectively is the average of all the 
texels in the image)

When you draw a mesh, you select which mipmap is the more appropriate to use given how big the texel should be.
You sample this mipmap with either nearest, linear or anisotropic filtering
For additional quality, you can also sample two mipmaps and blend the results.

*/

void Mipmapping()
{
    // When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // Generate mipmaps, by the way.
    glGenerateMipmap(GL_TEXTURE_2D);

}