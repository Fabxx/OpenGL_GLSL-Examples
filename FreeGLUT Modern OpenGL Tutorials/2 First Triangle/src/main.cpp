#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

GLuint VBO; //Vertex Buffer to store vertices

/*Each parameter in here indicates to GL that we are going to use the stuff that we create*/
static void RenderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

//Contains the vertex coordinates
static void CreateVertexBuffer()
{
 /**loads the attributes of our vertexes into the VBO.
  In Detail:
  ** GL_ARRAY_BUFFER: Target that was binded before
  ** Size of the buffer in bytes
  ** Pointer to the buffer
  ** GL_STATIC_DRAW: populate the buffer once, and use it multiple times
  **/

  //Vector of 3 float values, can contain only 3 float for each position.
  static const GLfloat g_vertex_buffer[] =
  {
	-1.0f, -1.0f, 0.0f, //bottom left
	0.0f, 1.0f, 0.0f, //bottom right
	1.0f, -1.0f, 0.0f //top, these coordinates are based on xyz positions.
  };
  
  //allocating memory to the vertex buffer object which will contain the vertex data.
  glGenBuffers(1, &VBO);

  //Bind the buffer in the GPU memory that will be used, with the vertex attributes.
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer), g_vertex_buffer, GL_STATIC_DRAW);
	
//enable vertex attributes with index 0 (must match index into shader)
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
/** In Detail:

** 0 is the index given before
** 3 is the size of the vector (3 for 3D, 2 for 2D etc)
** GL_FLOAT Indicates that we have float values in the buffer, and must be interpreted like so.
** GL_FALSE Tells GL to NOT normalize the data to 0 to 1 or -1
** 0 Is the Stride, number of bytes to the next occurrence of this attribute
** 0 Pointer, treated as integer, offset from the beginning of the buffer to the first instance of the attribute

EXAMPLE STRIDE
**OFFSET 0 (position of vertices): [][][]  
**OFFSET 12 (texture coordinates) [][][]
**OFFSET 20 (color) [][]  

**each block is 4 bytes, the coordinates start at byte 12, color at byte 20. the stride will be at 32 bytes total
**and the distance number from the offset to the stride will be 32 in the last pointer, this one will increase at runtime,
**when we have an occurrency of the vertex attributes.
**We put stride to 0 since in our case, we start with the attribs from the beginning of the buffer.
**/ 

/*
Draw points, pass data from the buffer to the pipeline via shading units and goes to the reasterizer.
*The rasterizer checks that the vertex position is in a visible part of the screen, and it maps it to the correspondent pixels
In Detail:
*GL_TRIANGLES: Tells to GL how to interprete the primitive type, in this case a single triangle, which is made by three vertices
			*(here we have a triangle with XYZ vertices)

*Index of the vertex to draw, tells from which vertex we have to start to draw
*Number of vertices to draw (in this case 3) */

}

void init_window(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	int width = 800, height = 600, x = 800/2, y = 600/2;

	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	
	int win = glutCreateWindow("First Window");
	printf("Window id:%d\n", win);
	
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "GLEW not initialized");
		exit(0);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int main(int argc, char *argv[])
{
	init_window(argc, argv);
	CreateVertexBuffer();
	glutDisplayFunc(RenderSceneCallBack);
	glutMainLoop(); 
}