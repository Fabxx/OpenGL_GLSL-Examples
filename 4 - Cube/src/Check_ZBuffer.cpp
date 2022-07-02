#include <GL/glew.h>

void check_zbuffer()
{
// Enable Z depth test, Accept fragment if it closer to the camera than the former one
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}