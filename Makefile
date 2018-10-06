CC = g++
LIBS=-lGLU -lGL -lGLEW
GLFWLIBS = -lglfw3 -lGL -lm -lrt -lXrandr -lXi -lX11 -lXinerama -lXcursor -lXxf86vm -lpthread -ldl
CFLAGS = -g -Wall -std=c++11 -Wno-deprecated

planet_defense: planet_main.o space_ship.o projectile.o
	$(CC) $(CFLAGS) -o $@ planet_main.o space_ship.o projectile.o $(LIBS) $(GLFWLIBS)

planet_main.o: space_ship.h projectile.h globals.h constants.h bitmaps.h structs.h
space_ship.o: space_ship.h globals.h constants.h
projectile.o: projectile.h globals.h constants.h

clean:
	rm -f *.o *~ planet_defense
