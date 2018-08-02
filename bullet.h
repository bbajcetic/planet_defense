#ifndef BULLET_H
#define BULLET_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <string>

enum side {ALLY, ENEMY};

class reg_bullet {
	public:
		reg_bullet(GLfloat x, GLfloat y, GLint speed, side good_bad);
		void display_bullet(void);
		void move();
		bool off_screen();
		void bullet_print();
		void reset(GLfloat x, GLfloat y, GLint speed, side good_bad);
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


#endif
