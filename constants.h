//constants file
#ifndef CONSTANTS_H
#define CONSTANTS_H

//window variables
const GLint WINDOW_HEIGHT = 500;
const GLint WINDOW_WIDTH = 500;
const GLint WINDOW_POS_X = 200;
const GLint WINDOW_POS_Y = 100;

//other
const GLint FRAMES_PER_SEC = 60;
const GLint PRJ_PER_SEC = 2; //how many bullets main_ship gets per sec

//starting variables for main ship
const GLfloat MAIN_SHIP_X = WINDOW_WIDTH/2;
const GLfloat MAIN_SHIP_Y = 100;
const GLint MAIN_SHIP_SIZE = 1;
const GLint MAIN_SHIP_SPEED = 3;
const GLfloat MAIN_SHIP_HEALTH = 100;
const GLint MAIN_SHIP_START_AMMO = 10;
const GLint MAIN_SHIP_INIT_MAX_AMMO = 50;
const GLint TOP_ALLY_SPACE = 150;
const GLint BOTTOM_ALLY_SPACE = 50;

//starting variables for enemy ship
const GLint ENEMY_SHIP_SIZE = 1;
const GLint ENEMY_SHIP_SPEED = 3;
const GLfloat ENEMY_SHIP_HEALTH = 50;
const GLint ENEMY_SHIP_MOVE_LENGTH = 25;
const GLint TOP_ENEMY_SPACE = WINDOW_HEIGHT;
const GLint BOTTOM_ENEMY_SPACE = 150;
const GLint SPAWN_RATE = 5*FRAMES_PER_SEC;

//starting variables for reg_bullet
const GLint REG_BULLET_LENGTH = 8;
const GLint REG_BULLET_WIDTH = 2;
const GLint ALLY_BULLET_SPEED = 10;
const GLint ENEMY_BULLET_SPEED = 5;
const GLint REG_BULLET_DAMAGE = 10;



#endif
