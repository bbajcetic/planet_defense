#include <iostream>
#include "projectile.h"
#include "constants.h"


void queue_bullet(reg_bullet _bullet) {
	;
}

void check_enemy_hit(GLfloat[], GLfloat length, GLfloat width) {
	;
}

void check_ally_hit(GLfloat[], GLfloat length, GLfloat width) {
	;
}

reg_bullet::reg_bullet(GLfloat x, GLfloat y, GLint speed, side good_bad):
	speed(speed), origin{x, y+length/2, 0.0}, good_bad(good_bad) 
{
	load_vertices();
}

bool reg_bullet::off_screen() {
	if (good_bad == ALLY && (origin[1]+length/2) > WINDOW_HEIGHT) 
		return true;
	else if (good_bad == ENEMY && (origin[1]-length/2) <= 0) 
		return true;
	else
		return false;
}

void reg_bullet::load_vertices() {
	GLfloat temp_quad[] = 
	{origin[0]-width/2, origin[1]+length/2, 0.0, 
	 origin[0]+width/2, origin[1]+length/2, 0.0, 
	 origin[0]+width/2, origin[1]-length/2, 0.0, 
	 origin[0]-width/2, origin[1]-length/2, 0.0};
	for (int i = 0; i < 12; ++i)
		quad[i] = temp_quad[i];
}

void reg_bullet::move() {
	/*if(good_bad == ALLY)
		printf("beginning: ALLY bullet\n");
	else if (good_bad == ENEMY)
		printf("beginning: ENEMY bullet\n");
	else
		printf("bollocks bullet\n\n");
	*/
	
	origin[1] += speed;
	//printf("New origin.y is %f\n", origin[1]);
	if (good_bad == ALLY && (origin[1]+length/2) <= WINDOW_HEIGHT) {
		//printf("check1\n");
		check_enemy_hit(origin, length, width);
	}
	else if (good_bad == ALLY) {//past window_height
		//printf("check2\n");
		exists = false;
		queue_bullet(*this);
	}
	else if (good_bad == ENEMY && (origin[1]-length/2) <= 0) {
		//printf("check3\n");
		check_ally_hit(origin, length, width);
	}
	else {//if (good_bad == ENEMY) and past bottom of window
		//printf("check4\n");
		if(good_bad == ALLY)
			;//printf("end: ALLY\n");
		else if (good_bad == ENEMY)
			;//printf("end: ENEMY\n");
		else
			;//printf("bollocks\n\n");
		exists = false;
		queue_bullet(*this);
	}
	load_vertices();
}

void reg_bullet::display_bullet(void) {
	glColor3f(1.0, 1.0, 1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, quad);
	glDrawArrays(GL_QUADS, 0, (GLsizei) 4);
	//glDisableClientState(GL_VERTEX_ARRAY);
}

void reg_bullet::reset(GLfloat x, GLfloat y, GLint speed, side good_bad) {
	origin[0] = x;
	origin[1] = y;
	this->speed = speed;
	this->good_bad = good_bad;
}

void reg_bullet::bullet_print() {
	std::cout << "speed = " << speed << std::endl;
	std::cout << "origin = " << origin[0] << " " << origin[1] 
		<< " " << origin[2] << std::endl; 
	std::cout << "length = " << length << std::endl;
	std::cout << "width = " << width << std::endl;
	if (good_bad == ALLY)
		std::cout << "good_bad = ALLY\n";
	else if (good_bad == ENEMY)
		std::cout << "good_bad = ENEMY\n";
	else
		std::cout << "NEITHER\n";
}
