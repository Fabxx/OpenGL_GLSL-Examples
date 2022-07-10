#include "Bind_VAO_render.hh"

/*After the VAO and VBO bindings, we tell him again to rebind the vertex arrays when we want, and it will be linked with it's VBO
  This is handled by openGL itself.*/
void BindVAO(GLFWwindow *window, int *VAOLoaded)
{
    if (glfwGetKey(window, GLFW_KEY_KP_1))
    {
        *VAOLoaded = 0;
        glBindVertexArray(VAO[0]); 
    }

    if (glfwGetKey(window, GLFW_KEY_KP_2))
    {
        *VAOLoaded = 1;
        glBindVertexArray(VAO[1]);
    }
}