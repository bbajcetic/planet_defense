
CC = g++
LIBS=-lglut -lGLU -lGL -lGLEW
GLFWLIBS = -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread
CFLAGS = -g -Wall -Wno-deprecated

planet_defense: planet_main.cpp space_ship.cpp projectile.cpp space_ship.h projectile.h constants.h globals.h bitmaps.h
	$(CC) $(CFLAGS) -o $@ planet_main.cpp space_ship.cpp projectile.cpp $(LIBS) $(GLFWLIBS)

#sample: sample.o
#	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
#
#%.o:%.cpp
#	$(CC) $(CFLAGS) -c $<


clean:
	rm -f *.o *~ planet_defense
