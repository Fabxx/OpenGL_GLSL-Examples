#include "0Common_headers.hh"

static void ColorRandomizer(GLfloat values[])
{
    srand(time(0));

    for (size_t i = 0; i < 9; ++i)
    {
        values[i] = (float)rand()/(float)(RAND_MAX/1.0f);
        
    }
}

void CreateColorBuffer()
{
    static GLfloat g_vertex_color_buffer[9];
    
    ColorRandomizer(g_vertex_color_buffer);

    glGenBuffers(1, &CBO);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_color_buffer), g_vertex_color_buffer, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
