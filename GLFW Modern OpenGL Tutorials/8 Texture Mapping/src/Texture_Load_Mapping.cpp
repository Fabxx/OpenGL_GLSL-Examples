#define STB_IMAGE_IMPLEMENTATION
#include "Texture_Load_Mapping.hh"
#include <stb/stb_image.h>

/** 
 ** NOTE: it is not recommended to use jpg, use BMP or DDS instead.
 ** We first set the flip from STBI, because open GL reads texture from bottom to top,
 **while STBI reads the images from top to bottom.
 **-Width and height indicate the texture resolution (Must be a power of 2 resolution, 64x64, 128x128, 256x256, 512x512 etc.)
 **-Bytes per pixel indicates the color depth on the textures (1 bbp = 1 = 8 bit color depth - 2bbp = 16 bit depth - 3bbp = 24 bit depth
 ** 4bbp = 32 bit depth - 5bbp = 40 bit depth. and so on.)
 **-Stbi_load gets the image data from the given file.
 **
 */


/** 
**glTexImage2D generates the 2D texture in the buffer we binded, with these parameters:
**-target: the texture type
**-Levels: if mipmaps are included, we have to put the mipmap number
**-Color Palette chose to be loaded in GPU: most of the times it's RGBA8 (the number varies on the bbp used for colors)
**-width and height of the texture
**-Border: must be 0
**-Color palette of the original texture
**-GL_UNSIGNED_BYTE: Telling to GL how to store this data in the GPU.
**-For a better reference on formats, use: https://www.khronos.org/opengl/wiki/Image_Format)
**-Pointer to the texture data to be elaborated.
*/

void VertexTexture(GLenum target, const char *filename)
{
    stbi_set_flip_vertically_on_load(1);
    int width, height, bytes_per_pixel;

    void *image_data = stbi_load(filename, &width, &height, &bytes_per_pixel, 0);
    
    if (!image_data)
    {
        fprintf(stderr, "Cannot open texture image.\n");
    }

    //*Next, we generate a texture buffer, like the VBO. in this case we use glGenTextures and BindTextures.

    glGenTextures(1, &TBO);
    glBindTexture(target, TBO);

    if (target == GL_TEXTURE_2D)
    {
        //Works with BMP, JPG, PNG
        glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    }
    else
    {
        fprintf(stderr, "Not a 2D texture image.\n");
    }

    /** 
     ** Next we have the mipmapping handling, if we have 0 mipmaps, we set the filters to NEAREST.
     ** the mipmapping  adds extra details to the texture when zooming in,
     ** But doing this in GL results in a performance consumption into the GPU, this is usually used with 
     ** Textures that don't have mipmaps in them (BMP for example). 
     **With DDS format this is not necessary if you generate the mipmaps with a exporter tool,
     ** the more mipmaps we have, the higher has to be the second number in glteximage2D. 
     **/
    
    glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    
   
   
    //freeing pointer with image data.
    stbi_image_free(image_data);
   
    //use the texture in buffer.
    glActiveTexture(target);

    //Enabling the attributes for texture to pass in shader, as always with every vertex attribute.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

