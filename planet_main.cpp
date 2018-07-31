#include <GL/glew.h>
#include <GL/glut.h>
#include "main_ship.h"
#include <vector>

const GLint WINDOW_HEIGHT = 500;
const GLint WINDOW_WIDTH = 500;
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

//vector <space_ship*> all_ships;
main_ship sonic(WINDOW_WIDTH/2, 50, 1);
//width/2 b/c start in middle of screen
void game_on(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	sonic.display_ship();

	glutSwapBuffers();
	glFlush();
}
void move_ship(int key, int x, int y) {
	unsigned int micros = 100000;
	switch(key) {
		case GLUT_KEY_RIGHT:
			sonic.move("right");
			printf("Key right is pressed\n");
			break;
		case GLUT_KEY_LEFT:
			sonic.move("left");
			printf("Key left is pressed\n");
			break;
		case GLUT_KEY_UP:
			sonic.move("up");
			printf("Key up is pressed\n");
			break;
		case GLUT_KEY_DOWN:
			sonic.move("down");
			printf("Key down is pressed\n");
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
//void another_func(unsigned char key, int x, int y) {}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("*** PLANET DEFENSE ***");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutReshapeFunc(reshape);
	glutSpecialFunc(move_ship);
	//glutKeyboardFunc(another_func);
	glutDisplayFunc(game_on);
	
	glutMainLoop();

	return 0;
}
