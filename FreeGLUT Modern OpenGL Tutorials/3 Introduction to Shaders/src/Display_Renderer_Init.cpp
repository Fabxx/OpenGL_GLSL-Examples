#include "0Common_headers.hh"
#include "2Display_Renderer_Init.hh"

void init_window()
{
    int argc; char *argv[] = {};
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