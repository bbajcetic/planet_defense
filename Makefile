
CC=-lglut -lGLU -lGL -lGLEW
main: planet_main.cpp main_ship.h 
	g++ -o planet_main.o planet_main.cpp $(CC)

clean: 
	rm planet_main.o