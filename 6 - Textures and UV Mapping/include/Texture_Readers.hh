#ifndef D47EFBFA_9F7B_4C94_A499_8D44457A8CB3
#define D47EFBFA_9F7B_4C94_A499_8D44457A8CB3
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>

typedef struct texture
{
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3 where 3 is RGB color channels, alpha is discarded.
    // Actual RGB data
    unsigned char *imagedata;

} texture;

typedef struct DDSTexture
{
    unsigned int height;  
    unsigned int width;         
    unsigned int linearSize;    
    unsigned int mipMapCount; 
    unsigned int fourCC;
    unsigned int format;
    unsigned int components;
    unsigned char *buffer;
} DDSTexture;

void BMPreader(texture *data);
void texture_maker_BMP(texture *data);

void DDSReader(DDSTexture *DDSdata);
int DDS_texture_maker(DDSTexture *data);


#endif /* D47EFBFA_9F7B_4C94_A499_8D44457A8CB3 */
