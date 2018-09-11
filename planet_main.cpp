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


GLFWwindow* wd; //window desciptor/handle

int frame_count = 0;
//vector <space_ship*> all_ships;
main_ship sonic(MAIN_SHIP_X, MAIN_SHIP_Y, MAIN_SHIP_SIZE, MAIN_SHIP_SPEED);
enemy_ship enemy(MAIN_SHIP_X+100, MAIN_SHIP_Y+100, ENEMY_SHIP_SIZE, ENEMY_SHIP_SPEED);
std::vector<enemy_ship> enemies;
std::vector<reg_bullet> projectiles;
std::vector<reg_bullet> graveyard;

void game_on(void) {
	sonic.display_ship();
	for (unsigned int i = 0; i < enemies.size(); ++i)
		enemies[i].display_ship();
	for (unsigned int i = 0; i < projectiles.size(); ++i)
		projectiles[i].display_bullet();
}
void quit(GLFWwindow *wd)
{
	glfwDestroyWindow(wd);
	glfwTerminate();
	exit(0);
}
void press_special(GLFWwindow* wd, int key, int scancode,int action,int mods) {
	//if (action == GLFW_RELEASE) { // function is called first on GLFW_PRESS.
	//  return;
	//}
	
	if (action == GLFW_RELEASE)
		sonic.set_is_moving(false);
	else if (action == GLFW_PRESS || action == GLFW_REPEAT)
		sonic.set_is_moving(true);

	if (key == GLFW_KEY_ESCAPE) {
		quit(wd);
	}
	else if (key == GLFW_KEY_UP) {
		sonic.set_direction(0);
		std::cout << "Key up is pressed\n";
	}
	else if (key == GLFW_KEY_RIGHT) {
		sonic.set_direction(1);
		std::cout << "Key right is pressed\n";
	}
	else if (key == GLFW_KEY_DOWN) {
		sonic.set_direction(2);
		std::cout << "Key down is pressed\n";
	}
	else if (key == GLFW_KEY_LEFT) {
		sonic.set_direction(3);
		std::cout << "Key left is pressed\n";
	}
	return;
}

void press_keys(GLFWwindow* wd, unsigned int key) {
	switch(key) {
		case ' ':
			sonic.shoot();
			break;
		case 'q':
			quit(wd);
			break;
		default:
			break;
	}
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
}

void err(int errcode, const char* desc)
{
	fprintf(stderr, "%d: %s\n", errcode, desc);
	return;
}

int main(int argc, char **argv) {
	srand(time(NULL));
	glfwSetErrorCallback(err);
	if (!glfwInit()) exit(1);
	wd = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 
						"*** PLANET DEFENSE ***", NULL, NULL);
	if (!wd) { //in case glfwCreateWindow function fails
	  glfwTerminate();
	  exit(1); }
	glfwSetWindowPos(wd, WINDOW_POS_X, WINDOW_POS_Y);

	int fbwidth, fbheight; //framebuffer width and height
	glfwGetFramebufferSize(wd, &fbwidth, &fbheight);
	glfwMakeContextCurrent(wd);
	glViewport(0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);
	//glfwSetFramebufferSizeCallback(wd, reshape); //don't think I need this
	//glfwSetWindowCloseCallback(wd, quit);
	glfwSetKeyCallback(wd, press_special); //general keyboard input
	glfwSetCharCallback(wd, press_keys); //specific character handling
	enemies.push_back(enemy);
	do { //game loop (like DisplayFunc callback in GLUT)
		//glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
		//glfwGetFramebufferSize(wd, &fbwidth, &fbheight);
		//glViewport(0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);
		
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

		idle_func();
		game_on();
		glfwSwapBuffers(wd);
		glfwPollEvents();
	} while (!glfwWindowShouldClose(wd));
	glfwTerminate();

	return 0;
}
