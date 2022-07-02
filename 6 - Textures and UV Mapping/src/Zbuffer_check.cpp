#include "Zbuffer_check.hh"

void check_zbuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}
    
