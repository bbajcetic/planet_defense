#include <iostream>
#include "space_ship.h"
#include "constants.h"

const GLfloat main_ship_health = 100;

space_ship::space_ship(GLfloat x, GLfloat y, GLint size, GLint speed): 
	speed(speed) {}

main_ship::main_ship(GLfloat x, GLfloat y, GLint size, GLint speed): 
	space_ship(x, y, size, speed) 
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

void main_ship::move(std::string direction) {
	if (direction == "right") {
		if (get_origin(0) + get_width()/2 + get_speed() <= WINDOW_WIDTH)
			set_origin(0, get_origin(0)+get_speed());
	}
	else if (direction == "left") {
		if (get_origin(0) - get_width()/2 - get_speed() >= 0)
			set_origin(0, get_origin(0)-get_speed());
	}
	else if (direction == "up") {
		;
	}
	else if (direction == "down") {
		;
	}
	else //error
		std::cout << "ERROR IN MOVEMENT" << std::endl;

	load_vertices();
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

