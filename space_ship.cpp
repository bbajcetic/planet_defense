#include <iostream>
//#include <ctime>
#include "space_ship.h"
#include "globals.h"
#include "constants.h"

const GLfloat main_ship_health = 100;
const GLfloat enemy_ship_health = 25;

space_ship::space_ship(GLfloat x, GLfloat y, GLint size, GLint speed): 
	speed(speed) {}

//main_ship class functions
main_ship::main_ship(GLfloat x, GLfloat y, GLint size, GLint speed): 
	space_ship(x, y, size, speed), direction(0)
{
	set_length(4*size*6);
	set_width(4*size*8);
	set_origin(x, y, 0.0);
	set_health(main_ship_health);
	load_vertices();
}

void main_ship::load_vertices() {
	GLfloat x = get_origin(0);
	GLfloat y = get_origin(1);
	GLfloat xlines[] =  
		{x-get_width()/2, x-get_width()*3/8, x-get_width()/4, 
		 x+get_width()/4, x+get_width()*3/8, x+get_width()/2};
	GLfloat ylines[] =  
		{y+get_length()/2, y+get_length()/3, y+get_length()/6, 
		 y-get_length()/3, y-get_length()/2};

	GLfloat temp_triangles[] = 
	{x,ylines[0],0.0,xlines[2],ylines[2],0.0,xlines[3],ylines[2],0.0,
	xlines[2],ylines[2],0.0,xlines[3],ylines[2],0.0,x,ylines[3],0.0,
	xlines[3],ylines[2],0.0,x,ylines[3],0.0,xlines[5],ylines[4],0.0,
	x,ylines[3],0.0,xlines[2],ylines[2],0.0,xlines[0],ylines[4],0.0,

	xlines[1],ylines[1],0.0,xlines[2],ylines[1],0.0,xlines[1],ylines[4],0.0,
	xlines[2],ylines[1],0.0,xlines[1],ylines[4],0.0,xlines[2],ylines[4],0.0,
	xlines[3],ylines[1],0.0,xlines[4],ylines[1],0.0,xlines[3],ylines[4],0.0,
	xlines[4],ylines[1],0.0,xlines[3],ylines[4],0.0,xlines[4],ylines[4],0.0};

	for (int i = 0; i < 72; ++i)
		triangles[i] = temp_triangles[i];
}

void main_ship::move() {
	if (get_direction() == 1) {
		if (get_origin(0) + get_width()/2 + get_speed() <= WINDOW_WIDTH)
			set_origin(0, get_origin(0)+get_speed());
	}
	else if (get_direction() == 3) {
		if (get_origin(0) - get_width()/2 - get_speed() >= 0)
			set_origin(0, get_origin(0)-get_speed());
	}
	else if (get_direction() == 0) {
		;
	}
	else if (get_direction() == 2) {
		;
	}
	else //error
		std::cout << "ERROR IN MOVEMENT" << std::endl;

	load_vertices();
}

void main_ship::shoot() {
	if ( graveyard.empty() ) {
		reg_bullet temp(get_origin(0), 
				get_origin(1)+get_length()/2, ALLY);
		projectiles.push_back(temp);
	}
	else {
		reg_bullet temp = *graveyard.begin();
		graveyard.erase(graveyard.begin());
		temp.reset(get_origin(0), 
				get_origin(1)+get_length()/2, ALLY);
		projectiles.push_back(temp);
		std::cout << "GRAVEYARD BULLET\n";
	}
}

void main_ship::shrink() {
	set_width(get_width()/2);
	set_length(get_length()/2);
	set_origin(1, get_origin(1) - get_length()/2);
}

void main_ship::grow() {
	//move origin forward so that ship doesn't move below screen
	set_origin(1, get_origin(1) + get_length()/2);
	set_length(get_length()*2);
	set_width(get_width()*2);
}

void main_ship::display_ship(void) {
	glColor3f(0.7, 0.7, 0.7);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, triangles);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei) 24);
}

//enemy_ship class functions
enemy_ship::enemy_ship(GLfloat x, GLfloat y, GLint size, GLint speed): 
	space_ship(x, y, size, speed), direction(0)
{
	set_length(4*size*4);
	set_width(4*size*8);
	set_origin(x, y, 0.0);
	set_health(enemy_ship_health);
	load_vertices();
}

void enemy_ship::load_vertices() {
	GLfloat x = get_origin(0);
	GLfloat y = get_origin(1);
	GLfloat xlines[] =  
		{x-get_width()/2, x-get_width()*3/8, x-get_width()/4, 
		 x-get_width()/8, x+get_width()/8,
		 x+get_width()/4, x+get_width()*3/8, x+get_width()/2};
	GLfloat ylines[] =  
		{y-get_length()/2, y-get_length()/4, y+get_length()/4};

	GLfloat temp_triangles[] = 
	{x,ylines[0],0.0,xlines[2],ylines[1],0.0,xlines[5],ylines[1],0.0,
	xlines[2],y,0.0,xlines[1],ylines[1],0.0,xlines[0],ylines[2],0.0,
	xlines[5],y,0.0,xlines[6],ylines[1],0.0,xlines[7],ylines[2],0.0};
	GLfloat temp_quads[] = 
	{xlines[1],ylines[1],0.0,xlines[1],y,0.0,
	xlines[6],y,0.0,xlines[6],ylines[1],0.0,
	xlines[2],ylines[1],0.0,xlines[2],ylines[2],0.0,
	xlines[3],ylines[2],0.0,xlines[3],ylines[1],0.0,
	xlines[5],ylines[1],0.0,xlines[5],ylines[2],0.0,
	xlines[4],ylines[2],0.0,xlines[4],ylines[1],0.0};

	for (int i = 0; i < 27; ++i)
		triangles[i] = temp_triangles[i];
	for (int i = 0; i < 36; ++i)
		quads[i] = temp_quads[i];
}

void enemy_ship::move(bool change) {
	if (change)	
		set_direction(rand()%4);
	if (get_direction() == 1) { //go right
		if (get_origin(0) + get_width()/2 + get_speed() <= WINDOW_WIDTH)
			set_origin(0, get_origin(0)+get_speed());
		else {
			set_origin(0, get_origin(0)-get_speed());
			set_direction(3);
		}
	}
	else if (get_direction() == 3) { //go left
		if (get_origin(0) - get_width()/2 - get_speed() >= 0)
			set_origin(0, get_origin(0)-get_speed());
		else {
			set_origin(0, get_origin(0)+get_speed());
			set_direction(1);
		}
	}
	else if (get_direction() == 0) { //go up
		if (get_origin(1) + get_length()/2 + get_speed() <= WINDOW_HEIGHT)
			set_origin(1, get_origin(1)+get_speed());
		else {
			set_origin(1, get_origin(1)-get_speed());
			set_direction(2);
		}
	}
	else if (get_direction() == 2) { //go down
		if (get_origin(1) - get_length()/2 - get_speed() >= BOTTOM_ENEMY_SPACE)
			set_origin(1, get_origin(1)-get_speed());
		else {
			set_origin(1, get_origin(1)+get_speed());
			set_direction(0);
		}
	}
	else //error
		std::cout << "ERROR IN MOVEMENT" << std::endl;

	load_vertices();
}

void enemy_ship::shoot() {
	if ( graveyard.empty() ) {
		reg_bullet temp(get_origin(0), 
				get_origin(1)-get_length()/2, ENEMY);
		projectiles.push_back(temp);
	}
	else {
		reg_bullet temp = *graveyard.begin();
		graveyard.erase(graveyard.begin());
		temp.reset(get_origin(0), 
				get_origin(1)-get_length()/2, ENEMY);
		projectiles.push_back(temp);
		std::cout << "GRAVEYARD BULLET\n";
	}
}

hit_box main_ship::get_hit_box() {
	hit_box hb;
	hb.left_x = get_origin(0) - get_width()*3/8;
	hb.right_x = get_origin(0) + get_width()*3/8;
	hb.bottom_y = get_origin(1) - get_length()*1/3;
	hb.top_y = get_origin(1) + get_length()*1/3;
	return hb;
}

hit_box enemy_ship::get_hit_box() {
	hit_box hb;
	hb.left_x = get_origin(0) - get_width()*3/8;
	hb.right_x = get_origin(0) + get_width()*3/8;
	hb.bottom_y = get_origin(1) - get_length()/4;
	hb.top_y = get_origin(1) + get_length()/4;
	return hb;
}

void enemy_ship::display_ship(void) {
	glColor3f(0.7, 0.7, 0.7);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, triangles);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei) 9);
	glVertexPointer(3, GL_FLOAT, 0, quads);
	glDrawArrays(GL_QUADS, 0, (GLsizei) 12);
}

