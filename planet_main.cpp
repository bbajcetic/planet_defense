#include <GL/glew.h>
#include <GL/glut.h>
#include "constants.h"
#include "main_ship.h"
#include "bullet.h"
#include <vector>
#include <iostream>

//vector <space_ship*> all_ships;
main_ship sonic(MAIN_SHIP_X, MAIN_SHIP_Y, MAIN_SHIP_SIZE, MAIN_SHIP_SPEED);
std::vector<reg_bullet> projectiles;
std::vector<reg_bullet> graveyard;

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}
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
			std::cout << "Key right is pressed\n";
			break;
		case GLUT_KEY_LEFT:
			sonic.move("left");
			std::cout << "Key left is pressed\n";
			break;
		case GLUT_KEY_UP:
			sonic.move("up");
			std::cout << "Key up is pressed\n";
			break;
		case GLUT_KEY_DOWN:
			sonic.move("down");
			std::cout << "Key down is pressed\n";
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
				std::cout << "GRAVEYARD BULLET\n";
			}
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
void idle_func(void) {
	for(std::vector<reg_bullet>::iterator it = projectiles.begin(); it != projectiles.end();) {
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
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
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
