CC = g++
LIBS=-lGLU -lGL -lGLEW
GLFWLIBS = -lglfw3 -lGL -lm -lrt -lXrandr -lXi -lX11 -lXinerama -lXcursor -lXxf86vm -lpthread -ldl
CFLAGS = -g -Wall -std=c++11 -Wno-deprecated

planet_defense: planet_main.o space_ship.o projectile.o
	$(CC) $(CFLAGS) -o $@ planet_main.o space_ship.o projectile.o $(LIBS) $(GLFWLIBS)

planet_main.o: planet_main.cpp space_ship.h projectile.h globals.h constants.h bitmaps.h structs.h
	$(CC) -c planet_main.cpp

space_ship.o: space_ship.cpp space_ship.h globals.h constants.h
	$(CC) -c space_ship.cpp

projectile.o: projectile.cpp projectile.h globals.h constants.h
	$(CC) -c projectile.cpp

#planet_defense: planet_main.cpp space_ship.cpp projectile.cpp space_ship.h projectile.h constants.h globals.h bitmaps.h
#	$(CC) $(CFLAGS) -o $@ planet_main.cpp space_ship.cpp projectile.cpp $(LIBS) $(GLFWLIBS)
#
##sample: sample.o
##	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
##
##%.o:%.cpp
##	$(CC) $(CFLAGS) -c $<
#
#
clean:
	rm -f *.o *~ planet_defense
