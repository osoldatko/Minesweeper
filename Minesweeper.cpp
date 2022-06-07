#include "stdafx.h"

#include "Constants.h"
#include "Game.h"
_Game Game;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Game.Draw();
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			Game.Check(x, y);
			break;

		case GLUT_RIGHT_BUTTON:
			Game.Flag(x, y);
			break;

		default:
			break;
		}
}

void timer(int = 0)
{
	display();
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

int main(int argc, char** argv)
{
	//Initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - Width / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - Height / 2);
	glutCreateWindow("Minesweeper");
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Width, Height, 0, -1, 1);
	//Functions
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	//Timers
	timer();
	//Main Loop
	glutMainLoop();
}