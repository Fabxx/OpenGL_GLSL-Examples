#include <iostream>
#include <GL/freeglut.h>

static void RenderSceneCB()
{
	//colors clamped by the system, with 0.0 to 1.0 Range, these apply the background color
	//use these if you want to cahnge the RGBA values individually and display only one color.
	//GLclampf Red = 0.0f, Green = 0.5f, Blue = 0.7f, Alpha = 0.0f;
	//glClearColor(Red, Green, Blue, Alpha);

	static GLclampf RGBA = 0.0f;
	glClearColor(0, 0.5, RGBA, 0);
	
	//To cover all range colors, standard RGBA is 8 bit, 2^8 = 256 combinations. 
	RGBA += 1.0f / 256.0f;

	if (RGBA >= 0.7f) //You can regulate this range how you want, higher the value is, more combinations will be displayed.
	{
		RGBA = 0.0f;
	}
	//cleans the screen to avoid junk and starts rendering again.
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay(); //Forces the color changer to be looped. by default GLUT calls this only when necessary.
	glutSwapBuffers();
	
}

int main(int argc, char *argv[])
{
	//GLut extracts it's data from argc in memory. This is the display and window init.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	int width = 800, height = 600;
	glutInitWindowSize(width, height);

	//window position, centering it.
	int x = 800/2, y = 600/2;
	glutInitWindowPosition(x, y);
	
	int win = glutCreateWindow("First Window");
	printf("Window id:%d\n", win);
	
	//Hooking into system events the window, this one handles the rendering. 
	glutDisplayFunc(RenderSceneCB);
	//puts iwndow in loop to not let it close instantly.
	glutMainLoop(); 
}