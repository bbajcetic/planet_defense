#ifndef MAIN_SHIP_H
#define MAIN_SHIP_H

#include <stdio.h>
//#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

extern const GLint WINDOW_HEIGHT;
extern const GLint WINDOW_WIDTH;

class space_ship {
	public:
		space_ship(GLfloat x, GLfloat y, GLint size, GLint speed);
		void display_ship(void);
		//void move(std::string direction);
		GLfloat get_origin(int coor) { return origin[coor]; }
		GLfloat get_length() { return length; }
		GLfloat get_width() { return width; }
		GLint get_health() { return health; }
		GLint get_speed() { return speed; }

		GLfloat set_origin(int coor, GLfloat new_val) 
			{ origin[coor] = new_val; }
		void set_length(GLfloat new_length) 
			{ length = new_length; }
		void set_width(GLfloat new_width) 
			{ width = new_width; }
		void set_health(GLint new_health) 
			{ health = new_health; }
		void set_speed(GLint new_speed) 
			{ speed = new_speed; }


	private:
		GLfloat origin[3];
		GLfloat length;
		GLfloat width;
		GLint health;
		GLint speed;
};

class main_ship : public space_ship {
    public:
		main_ship(GLfloat x, GLfloat y, GLint size, GLint speed);
		void display_ship(void); 
		void move(std::string direction);
	private:
		/*GLint health;
		GLint speed;
		GLfloat origin[3];
		GLfloat length;
		GLfloat width;*/
		void grow();
		void shrink();
		void load_vertices();
	    GLfloat triangles[72];
};

#endif
