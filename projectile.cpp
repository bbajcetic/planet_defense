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

projectile::projectile(GLfloat x, GLfloat y, good_bad side):
	speed(REG_BULLET_SPEED), side(side) {}

reg_bullet::reg_bullet(GLfloat x, GLfloat y, good_bad side):
	projectile(x, y, side)
{
	set_length(REG_BULLET_LENGTH);
	set_width(REG_BULLET_WIDTH);
    set_origin(x, y+REG_BULLET_LENGTH/2, 0.0);
	load_vertices();
}

bool reg_bullet::off_screen() {
	if (get_side() == ALLY && (get_origin(1)+get_length()/2) > WINDOW_HEIGHT) 
		return true;
	else if (get_side() == ENEMY && (get_origin(1)-get_length()/2) <= 0) 
		return true;
	else
		return false;
}

void reg_bullet::load_vertices() {
	GLfloat temp_quad[] = 
	{get_origin(0)-get_width()/2, get_origin(1)+get_length()/2, 0.0, 
	 get_origin(0)+get_width()/2, get_origin(1)+get_length()/2, 0.0, 
	 get_origin(0)+get_width()/2, get_origin(1)-get_length()/2, 0.0, 
	 get_origin(0)-get_width()/2, get_origin(1)-get_length()/2, 0.0};
	for (int i = 0; i < 12; ++i)
		quad[i] = temp_quad[i];
}

void reg_bullet::move() {
	/*if(get_side() == ALLY)
		printf("beginning: ALLY bullet\n");
	else if (get_side() == ENEMY)
		printf("beginning: ENEMY bullet\n");
	else
		printf("bollocks bullet\n\n");
	*/
	set_origin(1, get_origin(1)+get_speed());
	if (get_side() == ALLY && (off_screen() == false)) {
		//check_enemy_hit(origin, get_length(), get_width());
	}
	else if (get_side() == ALLY && (off_screen() == true)) {//above height 
		exists = false;
		queue_bullet(*this);
	}
	else if (get_side() == ENEMY && (off_screen() == false)) {
		//check_ally_hit(origin, get_length(), get_width());
	}
	else if (get_side() == ENEMY && (off_screen() == true)) {//below bottom 
		exists = false;
		queue_bullet(*this);
	}
	else
	    std::cout << "ERROR: projectile has no good_bad side\n";

	load_vertices();
}

void reg_bullet::display_bullet(void) {
	glColor3f(1.0, 1.0, 1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, quad);
	glDrawArrays(GL_QUADS, 0, (GLsizei) 4);
	//glDisableClientState(GL_VERTEX_ARRAY);
}

void reg_bullet::reset(GLfloat x, GLfloat y, good_bad side) {
	set_origin(0, x);
	set_origin(1, y);
	set_speed(REG_BULLET_SPEED);
	set_side(side);
}

void reg_bullet::bullet_print() {
	std::cout << "speed = " << get_speed() << std::endl;
	std::cout << "origin = " << get_origin(0) << " " << get_origin(1)
		<< " " << get_origin(2) << std::endl; 
	std::cout << "length = " << get_length() << std::endl;
	std::cout << "width = " << get_width() << std::endl;
	if (get_side() == ALLY)
		std::cout << "side = ALLY\n";
	else if (get_side() == ENEMY)
		std::cout << "side = ENEMY\n";
	else
	    std::cout << "ERROR: projectile has no good_bad side\n";
}
