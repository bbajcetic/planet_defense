#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <ctime>
#include "globals.h"
#include "constants.h"
#include "space_ship.h"
#include "structs.h"
#include "projectile.h"
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bitmaps.h"


bool game_on = false;
bool game_over = false;
GLint score = 0;
GLint score_hundreds, score_tens, score_ones;
GLint frame_count = 0;
//vector <space_ship*> all_ships;
main_ship sonic(MAIN_SHIP_X, MAIN_SHIP_Y, MAIN_SHIP_SIZE, MAIN_SHIP_SPEED);
std::vector<enemy_ship> enemies;
std::vector<reg_bullet> projectiles;

void fill_score_vars() {
	if (score > 999)
		score = 999;
	score_hundreds = score/100;
	score_tens = (score%100)/10;
	score_ones = score%10;
}
void reshape(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
bool check_collision(hit_box bullet_hb, hit_box ship_hb) {
	bool condition1 = bullet_hb.left_x <= ship_hb.right_x;
	bool condition2 = bullet_hb.right_x >= ship_hb.left_x;
	bool condition3 = bullet_hb.bottom_y <= ship_hb.top_y;
	bool condition4 = bullet_hb.top_y >= ship_hb.bottom_y;
	return (condition1 && condition2 && condition3 && condition4);
}

void display_loop(void) {
	sonic.display_ship();
	for (unsigned int i = 0; i < enemies.size(); ++i)
		enemies[i].display_ship();
	for (unsigned int i = 0; i < projectiles.size(); ++i)
		projectiles[i].display_bullet();
}
void start_game(void);
void end_game(void);

void quit(GLFWwindow *wd)
{
	glfwSetWindowShouldClose(wd, true);
}
void press_keys(GLFWwindow* wd, int key, int scancode,int action,int mods) {
	std::map<int, int> arrows = { {262, 1}, {263, 3}, {264, 2}, {265, 0} };
	std::map<int, std::string> directions = { {0, "north"}, {1, "east"}, {2, "south"}, {3, "west"} };
	if (arrows.find(key) != arrows.end()) {
		if (action == GLFW_PRESS) {
			sonic.set_last(arrows[key]);
			sonic.set_direction(arrows[key]);
			sonic.set_arrow_state(arrows[key], true);
			//std::cout << "Key " << directions[arrows[key]] << " pressed\n";
		}
		else if (action == GLFW_RELEASE) {
			sonic.set_arrow_state(arrows[key], false);
			if (sonic.get_last(0) == arrows[key]) {
				sonic.set_direction(sonic.get_last(1));
				sonic.set_last(sonic.get_last(1));
			}
		}
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		sonic.shoot();
	}
	else if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) {
		quit(wd);
	}
	else if (key == GLFW_KEY_ENTER) {
		if (game_on == false) {
			game_on = true;
		}
	}
	return;
}

//game_loop: check collisions-> move bullets-> move ships
void game_loop(void) {
	if (frame_count % FRAMES_PER_SEC == 0)
		sonic.update_ammo();
	if (frame_count % SPAWN_RATE == 0) {
		if (enemies.size() <= MAX_NUM_ENEMIES) {
			GLint start_y = rand()%(TOP_ENEMY_SPACE-BOTTOM_ENEMY_SPACE) + BOTTOM_ENEMY_SPACE;
			GLint start_x = rand()%(WINDOW_WIDTH);
			enemy_ship enemy(start_x, start_y, ENEMY_SHIP_SIZE, ENEMY_SHIP_SPEED);
			enemies.push_back(enemy);
		}
	}
	if(sonic.get_arrow_state(sonic.get_last(0)) == true)
		sonic.move();
	for (unsigned int i = 0; i < enemies.size(); ++i) {
		if (frame_count % ENEMY_SHIP_MOVE_LENGTH == 0) {
			enemies[i].move(true);
			enemies[i].shoot();
		}
	    else {
			enemies[i].move(false);
		}
	}
	for(std::vector<reg_bullet>::iterator it = projectiles.begin(); 
										it != projectiles.end();) {
		bool bullet_destroyed = false;
		if( it->off_screen() ) {
			it = projectiles.erase(it);
			continue;
		}
		if (it->get_side() == ALLY) {
			for (std::vector<enemy_ship>::iterator it2 = enemies.begin(); 
										it2 != enemies.end();) {
				hit_box bullet_hb = it->get_hit_box();
				hit_box ship_hb = it2->get_hit_box();
				bool is_collision = check_collision(bullet_hb, ship_hb);
				if (is_collision) {
					std::cout << "Enemy hit!!!\n";
					bool enemy_dead = it2->get_shot(*it);
					it = projectiles.erase(it);
					bullet_destroyed = true;
					if (enemy_dead == true) {
						it2 = enemies.erase(it2);
						score += ENEMY_POINTS;
						std::cout << "ENEMY DESTROYED!\n";
					}
					break; //in case enemies overlap, can only kill one
				}
				else
					++it2;
			}
		}
		else if (it->get_side() == ENEMY) {
			hit_box bullet_hb = it->get_hit_box();
			hit_box ship_hb = sonic.get_hit_box();
			bool is_collision = check_collision(bullet_hb, ship_hb);
			if (is_collision) {
				std::cout << "Sonic hit!!!\n";
				bool sonic_dead = sonic.get_shot(*it);
				it = projectiles.erase(it);
				bullet_destroyed = true;
				if (sonic_dead == true) {
					game_over = true;
					fill_score_vars();
					std::cout << "GAME OVER!\n";
					std::cout << "\nSCORE = " << score << "\n\n";
				}
				//break; when looping though allies; //in case enemies overlap, can only kill one
			}
		}
		if (bullet_destroyed == true) {
			bullet_destroyed = false; //reset for next bullet
			continue;
		}
		it->move();
		++it;
	}
}

void err(int errcode, const char* desc)
{
	fprintf(stderr, "%d: %s\n", errcode, desc);
	return;
}

int main(int argc, char **argv) {
	srand(time(NULL));
	std::cout << "Press <ENTER> to start playing!\n" << std::flush;
	glfwSetErrorCallback(err);
	if (!glfwInit()) exit(1);
	GLFWwindow* wd = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 
						"*** PLANET DEFENSE ***", NULL, NULL);
	if (wd == NULL) { //in case glfwCreateWindow function fails
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(wd);
	glfwSetWindowPos(wd, WINDOW_POS_X, WINDOW_POS_Y);

	GLint fbwidth, fbheight; //framebuffer width and height
	glfwSetFramebufferSizeCallback(wd, reshape); //for resizing window
	glfwSetWindowCloseCallback(wd, quit);
	glfwSetKeyCallback(wd, press_keys); //general keyboard input

	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	while (!glfwWindowShouldClose(wd)) { //game loop
		//glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
		glfwGetFramebufferSize(wd, &fbwidth, &fbheight);
		glViewport(0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);
		//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

		//if (frame_count % 10 == 0)
		//	std::cout << "frame_count = " << frame_count << std::endl;
		if (game_on == false) {
			start_game();
		}
		else if (game_over == false) {
			game_loop();
			display_loop();
			++frame_count;
		}
		else { //(game_over == true)
			//display game_over window with game over message and score
			end_game();
		}

		glfwSwapBuffers(wd);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

void start_game(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	sonic.display_ship();
	glColor3f (1.0, 1.0, 1.0);
	GLubyte start_title = WINDOW_WIDTH/2 - 168;
	GLubyte start_letters = WINDOW_WIDTH/2 - 120;

	glRasterPos2i (start_title, WINDOW_HEIGHT-40);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigP);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigL);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigA);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigN);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigE);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigT);

	glRasterPos2i (start_title+168, WINDOW_HEIGHT-40);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigD);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigE);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigF);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigE);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigN);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigS);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigE);

	glRasterPos2i (start_letters, 20);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, P);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, R);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, E);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, S);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, S);

	glRasterPos2i (start_letters+72, 20);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, E);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, N);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, T);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, E);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, R);
	
	glRasterPos2i (start_letters+144, 20);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, T);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, O);

	glRasterPos2i (start_letters+180, 20);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, S);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, T);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, A);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, R);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, T);
}
void end_game(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	sonic.display_ship();
	glColor3f (1.0, 1.0, 1.0);
	GLubyte start_msg = WINDOW_WIDTH/2 - 108;
	GLubyte score_msg = WINDOW_WIDTH/2 - 60;

	glRasterPos2i (start_msg, WINDOW_HEIGHT/2);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigG);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigA);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigM);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigE);

	glRasterPos2i (start_msg+120, WINDOW_HEIGHT/2);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigO);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigV);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigE);
	glBitmap (32, 12, 0.0, 0.0, 24.0, 0.0, bigR);

	glRasterPos2i (score_msg, WINDOW_HEIGHT/4);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, S);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, C);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, O);
	glBitmap (16, 12, 0.0, 0.0, 12.0, 0.0, R);
	glBitmap (16, 12, 0.0, 0.0, 20.0, 0.0, E);
	glBitmap (16, 12, 0.0, 0.0, 20.0, 0.0, equals);
	glBitmap (16, 12, 0.0, 0.0, 16.0, 0.0, bitmap_nums[score_hundreds]);
	glBitmap (16, 12, 0.0, 0.0, 16.0, 0.0, bitmap_nums[score_tens]);
	glBitmap (16, 12, 0.0, 0.0, 16.0, 0.0, bitmap_nums[score_ones]);

}
