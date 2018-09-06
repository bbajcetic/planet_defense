#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
//#include <ctime>
#include "globals.h"
#include "constants.h"
#include "space_ship.h"
#include "projectile.h"
#include <vector>
#include <iostream>


int frame_count = 0;
//vector <space_ship*> all_ships;
main_ship sonic(MAIN_SHIP_X, MAIN_SHIP_Y, MAIN_SHIP_SIZE, MAIN_SHIP_SPEED);
enemy_ship enemy(MAIN_SHIP_X+100, MAIN_SHIP_Y+100, ENEMY_SHIP_SIZE, ENEMY_SHIP_SPEED);
std::vector<enemy_ship> enemies;
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
	for (unsigned int i = 0; i < enemies.size(); ++i)
		enemies[i].display_ship();
	//enemy.display_ship();
	for (unsigned int i = 0; i < projectiles.size(); ++i)
		projectiles[i].display_bullet();

	glutSwapBuffers();
	glFlush();
}
void press_special(int key, int x, int y) {
	if (GLUT_KEY_RIGHT || GLUT_KEY_LEFT || GLUT_KEY_UP || GLUT_KEY_DOWN)
		sonic.set_is_moving(true);
	switch(key) {
		case GLUT_KEY_RIGHT:
			sonic.set_direction(1);
			std::cout << "Key right is pressed\n";
			break;
		case GLUT_KEY_LEFT:
			sonic.set_direction(3);
			std::cout << "Key left is pressed\n";
			break;
		case GLUT_KEY_UP:
			sonic.set_direction(0);
			std::cout << "Key up is pressed\n";
			break;
		case GLUT_KEY_DOWN:
			sonic.set_direction(2);
			std::cout << "Key down is pressed\n";
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
void release_special(int key, int x, int y) {
	//if (GLUT_KEY_RIGHT || GLUT_KEY_LEFT || GLUT_KEY_UP || GLUT_KEY_DOWN)
	if (GLUT_KEY_RIGHT && sonic.get_direction() == 1)
		sonic.set_is_moving(false);
	if (GLUT_KEY_LEFT && sonic.get_direction() == 3)
		sonic.set_is_moving(false);
	glutPostRedisplay();
}

void press_keys(unsigned char key, int x, int y) {
	switch(key) {
		case ' ':
			sonic.shoot();
			break;
		case 'q':
			if(glutGetModifiers()) //alt+q exits game 
				exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
//idle_func: check collisions-> move bullets-> move ships
void idle_func(void) {
	++frame_count;
	if(sonic.get_is_moving() == true)
		sonic.move();
	for (unsigned int i = 0; i < enemies.size(); ++i)
		if (frame_count % ENEMY_SHIP_MOVE_LENGTH == 0) {
			enemies[i].move(true);
			enemies[i].shoot();
		}
	    else {
			enemies[i].move(false);
		}
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
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	glutCreateWindow("*** PLANET DEFENSE ***");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutReshapeFunc(reshape);
	glutSpecialFunc(press_special);
	glutKeyboardFunc(press_keys);
	glutSpecialUpFunc(release_special);
	glutIdleFunc(idle_func);
	glutDisplayFunc(game_on);

	enemies.push_back(enemy);
	
	glutMainLoop();

	return 0;
}
