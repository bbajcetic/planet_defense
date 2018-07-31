#include <stdio.h>
//#include <iostream>
#include <string>

extern const GLint WINDOW_HEIGHT;
extern const GLint WINDOW_WIDTH;

enum side {ALLY, ENEMY};

class reg_bullet {
	public:
		reg_bullet(GLfloat x, GLfloat y, GLint _speed, side _good_bad);
		void display_bullet(void);
		void move();
	private:
		GLint speed; //negative or positive depending on direction
		GLfloat origin[3];
		GLfloat length = 8;
		GLfloat width = 2;
		GLfloat triangles[2];
		side good_bad;
		bool exists = true;
		void load_vertices();
		GLfloat quad[12];
};

void queue_bullet(reg_bullet _bullet) {
	;
}

void check_enemy_hit(GLfloat[], GLfloat length, GLfloat width) {
	;
}

void check_ally_hit(GLfloat[], GLfloat length, GLfloat width) {
	;
}
//give (x, y) position of the middle of the back end of the bullet
reg_bullet::reg_bullet(GLfloat x, GLfloat y, GLint _speed, side _good_bad):
	speed(_speed), origin{x, y+length/2, 0.0}, good_bad(_good_bad) 
{
	load_vertices();
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
	origin[1] += speed;
	printf("New origin.y is %f\n", origin[1]);
	if (good_bad == ALLY && (origin[1]+length/2) <= WINDOW_HEIGHT) {
		check_enemy_hit(origin, length, width);
	}
	else if (good_bad == ALLY) {//past window_height
		exists = false;
		queue_bullet(*this);
	}
	else if (good_bad == ENEMY && (origin[1]-length/2) <= 0) {
		check_ally_hit(origin, length, width);
	}
	else {//if (good_bad == ENEMY) and past bottom of window
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
