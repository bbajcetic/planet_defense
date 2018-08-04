
CC=-lglut -lGLU -lGL -lGLEW
main: planet_main.cpp space_ship.cpp projectile.cpp space_ship.h projectile.h constants.h globals.h
	g++ -o planet_main.o planet_main.cpp space_ship.cpp projectile.cpp $(CC)

clean: 
	rm planet_main.o
