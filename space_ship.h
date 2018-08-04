#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <string>

class space_ship {
	public:
		space_ship(GLfloat x, GLfloat y, GLint size, GLint speed);
		//getter functions
		GLfloat get_origin(int coor) { return origin[coor]; }
		GLfloat get_length() { return length; }
		GLfloat get_width() { return width; }
		GLint get_health() { return health; }
		GLint get_speed() { return speed; }
		//setter functions
		void set_origin(GLfloat valx, GLfloat valy, GLfloat valz)
		{ origin[0] = valx; origin[1] = valy; origin[2] = valz; }
		void set_origin(int coor, GLfloat new_val) 
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
		void shoot();
	private:
		void grow();
		void shrink();
		void load_vertices();
	    GLfloat triangles[72];
};

class enemy_ship : public space_ship {
	public:
		enemy_ship(GLfloat x, GLfloat y, GLint size, GLint speed);
		void display_ship(void); 
		void move(bool change);
		GLint get_direction() { return direction; }
		void set_direction(GLint new_direction) 
			{ direction = new_direction; }
	private:
		int direction;
		void load_vertices();
	    GLfloat triangles[27]; 
		GLfloat quads[36];
};

#endif
