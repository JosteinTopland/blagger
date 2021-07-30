CC=gcc
CFLAGS=`sdl2-config --cflags` -Wall
LDFLAGS=`sdl2-config --libs` -lSDL2_mixer

all: blagger

blagger: blagger.o render.o input.o update.o globals.o level.o
	$(CC) $(LDFLAGS) -o blagger blagger.o render.o input.o update.o globals.o level.o

blagger.o: blagger.c render.h types.h input.h globals.h
	$(CC) $(CFLAGS) -c blagger.c

render.o: render.c render.h types.h
	$(CC) $(CFLAGS) -c render.c

input.o: input.c input.h types.h
	$(CC) $(CFLAGS) -c input.c

update.o: update.c update.h types.h globals.h
	$(CC) $(CFLAGS) -c update.c

globals.o: globals.c globals.h types.h
	$(CC) $(CFLAGS) -c globals.c

level.o: level.c level.h types.h
	$(CC) $(CFLAGS) -c level.c

clean:
	rm -f blagger *.o
