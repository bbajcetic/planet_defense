
CC = g++
LIBS=-lglut -lGLU -lGL -lGLEW
CFLAGS = -g -Wall -Wno-deprecated

planet_defense: planet_main.cpp space_ship.cpp projectile.cpp space_ship.h projectile.h constants.h globals.h
	$(CC) $(CFLAGS) -o $@ planet_main.cpp space_ship.cpp projectile.cpp $(LIBS)

#sample: sample.o
#	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
#
#%.o:%.cpp
#	$(CC) $(CFLAGS) -c $<


clean: 
	rm -f *.o *~ planet_defense
