#include "ColorRandomizer.hh"


void gencolors(GLfloat values[])
{
   srand(time(0));
   for (size_t i = 0; i < 18; i++)
   {
        values[i] = (float)rand()/(float)(RAND_MAX/1.0f); //generates random values each time during execution.
   }
}