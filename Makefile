
CC=-lglut -lGLU -lGL -lGLEW
main: planet_main.cpp main_ship.cpp bullet.cpp main_ship.h bullet.h
	g++ -o planet_main.o planet_main.cpp main_ship.cpp bullet.cpp $(CC)

clean: 
	rm planet_main.o
