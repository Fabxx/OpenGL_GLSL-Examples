#include "Texture_Readers.hh"
#include <GLFW/glfw3.h>
//NOTE: This example was made with bitmap files, for other headers read the documentations.

/*
When texturing a mesh, you need a way to tell to OpenGL which part of the image has to be used for each triangle. 
This is done with UV coordinates. (Where U is based on X axis and V on Y axis)

Each vertex can have, on top of its position, a couple of floats, U and V. These coordinates are used to access the 
texture by making a 45 degree angle, and access the top and bottom texture side, and apply the texture over.
*/

/*
Loading .BMP images yourself

Knowing the BMP file format is not crucial : plenty of libraries can load BMP files for you. 
But it’s very simple and can help you understand how things work under the hood. So we’ll write a BMP file loader 
from scratch, so that you know how it works, and never use it again.
Here is the declaration of the loading function : */

void BMPreader(texture *data)
{
   const GLchar BMPtexture[] = {"texture.bmp"};

 /*Let’s see how to read a BMP file, then.

First, we’ll need some data. These variable will be set when reading the file.
*/
    FILE * file = fopen(BMPtexture,"rb");
    if (!file)
    {
        printf("Image could not be opened\n"); 
        exit(0);
    }

    if (fread(data->header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    exit(0);
}

/*The header always begins by BM. As a matter of fact, here’s what you get when you open a .BMP 
  file in a hexadecimal editor : So we have to check that the two first bytes are really ‘B’ and ‘M’ : */

if (data->header[0]!='B' || data->header[1]!='M' ){
    printf("Not a correct BMP file\n");
    exit(0);
}
    //now we can read the size of the image, the location of the data in the file, etc :

    // Read ints from the byte array, converting char pointers to int*
    data->dataPos    = *(int*)&(data->header[0x0A]);
    data->imageSize  = *(int*)&(data->header[0x22]);
    data->width      = *(int*)&(data->header[0x12]);
    data->height     = *(int*)&(data->header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (data->imageSize==0)    data->imageSize=data->width*data->height*3; // 3 : one byte for each Red, Green and Blue component
    if (data->dataPos==0)      data->dataPos=54; // The BMP header is done that way

   //Now that we know the size of the image, we can allocate some memory to read the image into, and read :

    // Create a buffer
    data->imagedata = new unsigned char [data->imageSize];

    // Read the actual data from the file into the buffer
    fread(data->imagedata,1,data->imageSize,file);

    //Everything is in memory now, the file can be closed
    fclose(file);
}

void texture_maker_BMP(texture *data)
{
    /*We arrive now at the real OpenGL part. Creating textures is very similar to creating vertex buffers : 
    Create a texture, bind it, fill it, and configure it.
    In glTexImage2D, the GL_RGB indicates that we are talking about a 3-component color, and GL_BGR says how exactly it 
    is represented in RAM. As a matter of fact, BMP does not store Red->Green->Blue but Blue->Green->Red, 
    so we have to tell it to OpenGL. */

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, data->width, data->height, 0, GL_BGR, GL_UNSIGNED_BYTE, data->imagedata);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/*At this point, you’re probably wondering how to load JPEG files instead of TGA.

Short answer : don’t. GPUs can’t understand JPEG. So you’ll compress your original image in JPEG, 
and decompress it so that the GPU can understand it. You’re back to raw images, but you lost image 
quality while compressing to JPEG.
There’s a better option.*/

//Same reader but for DDS textures

/*
Load a Power-Of-Two texture in it (128x128/256x256/512x512 ecc).
Generate mipmaps so that you won’t have to do it on runtime (avoids using glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); )
Compress it in DXT1, DXT3 or in DXT5 (more about the differences between the various formats on Wikipedia) : 

At this point, your image is compressed in a format that is directly compatible with the GPU. Whenever calling texture() in a shader, 
it will uncompress it on-the-fly. This can seem slow, but since it takes a LOT less memory, less data needs to be transferred. 
But memory transfers are expensive; and texture decompression is free (there is dedicated hardware for that). Typically, using 
texture compression yields a 20% increase in performance. So you save on performance and memory, at the expense of reduced quality.*/

void DDSReader(DDSTexture *data)
{
    const GLchar DDSTexture[] = {"texture_DXT3.dds"};
    unsigned char header[124];

    FILE *fp;

    /* try to open the file */
    fp = fopen(DDSTexture, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to load DDS image\n");
        exit(0);
    }
        
    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fprintf(stderr, "Not a valid DDS file\n");
        system("pause");
        fclose(fp);
        exit(0);
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp); 

    data->height = *(unsigned int*)&(header[8 ]);
    data->width  = *(unsigned int*)&(header[12]);
    data->linearSize = *(unsigned int*)&(header[16]);
    data->mipMapCount = *(unsigned int*)&(header[24]);
    data->fourCC  = *(unsigned int*)&(header[80]);

    //After the header is the actual data : all the mipmap levels, successively. We can read them all in one batch :

    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = data->mipMapCount > 1 ? data->linearSize * 2 : data->linearSize;
    data->buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(data->buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    //Here we’ll deal with 3 different formats : DXT1, DXT3 and DXT5. 
    //We need to convert the “fourCC” flag into a value that OpenGL understands.
    //FourCC values documentation: https://docs.microsoft.com/en-us/previous-versions/windows/desktop/bb152176(v=vs.85)

    #define DXT5 894720068 	
    #define DXT4 877942852 	
    #define DXT3 861165636	
    #define DXT2 844388420
    #define DXT1 827611204

    data->components  = (data->fourCC == DXT1) ? 3 : 4; //if 3 else 4

    switch(data->fourCC)
    {
    case DXT1:
        data->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case DXT3:
        data->format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case DXT5:
        data->format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(data->buffer);
        fprintf(stderr, "No compression was recognized");
        exit(0);
    }
}

 /*
    Another very important point BOTH BMP AND DDS :** use power-of-two textures !**
    good : 128*128, 256*256, 1024*1024, 2*2…
    bad : 127*128, 3*5, …
    okay but weird : 128*256
    */

int DDS_texture_maker(DDSTexture *data)
{
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    //And now, we just have to fill each mipmap one after another :

    unsigned int blockSize = (data->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < data->mipMapCount && (data->width || data->height); ++level)
    {
        unsigned int size = ((data->width+3)/4)*((data->height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, data->format, data->width, data->height, 
            0, size, data->buffer + offset);

        offset += size;
        data->width  /= 2;
        data->height /= 2;
    }
    free(data->buffer); 
    return textureID;
}

/*
Inversing the UVs

DXT compression comes from the DirectX world, where the V texture coordinate is inversed compared to
 OpenGL. So if you use compressed textures, you’ll have to use ( coord.u, 1.0-coord.v) to fetch the correct 
 texel. You can do this whenever you want : in your export script, in your loader, in your shader…*/



