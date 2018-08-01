#include <GL/glew.h>
#include <GL/glut.h>
#include "main_ship.h"
#include "bullet.h"
#include <vector>
//#include <list>

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
std::vector<reg_bullet> projectiles;
std::vector<reg_bullet> graveyard;
reg_bullet bully(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 20, ALLY);
//width/2 b/c start in middle of screen
void game_on(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	sonic.display_ship();
	for (int i = 0; i < projectiles.size(); ++i)
		projectiles[i].display_bullet();
	//bully.display_bullet();

	glutSwapBuffers();
	glFlush();
}
void press_special(int key, int x, int y) {
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
void press_keys(unsigned char key, int x, int y) {
	switch(key) {
		case ' ':
			if ( graveyard.empty() ) {
				reg_bullet temp(sonic.get_origin(0), 
						sonic.get_origin(1)+sonic.get_length()/2, 5, ALLY);
				projectiles.push_back(temp);
			}
			else {
				reg_bullet temp = *graveyard.begin();
				graveyard.erase(graveyard.begin());
				temp.reset(sonic.get_origin(0), 
						sonic.get_origin(1)+sonic.get_length()/2, 5, ALLY);
				projectiles.push_back(temp);
				printf("GRAVEYARD BULLET\n");
			}
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
void idle_func(void) {
	std::vector<reg_bullet>::iterator it = projectiles.begin();
	while(it != projectiles.end()) {
		if( it->off_screen() ) {
			reg_bullet temp = *it;
			it = projectiles.erase(it);
			graveyard.push_back(temp);
		}
		else {
			it->move();
			++it;
		}
	}

	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("*** PLANET DEFENSE ***");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutReshapeFunc(reshape);
	glutSpecialFunc(press_special);
	glutKeyboardFunc(press_keys);
	glutIdleFunc(idle_func);
	glutDisplayFunc(game_on);
	
	glutMainLoop();

	return 0;
}
