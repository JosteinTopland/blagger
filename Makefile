SRCDIR  = src/
SRCS    = $(wildcard $(SRCDIR)*.c)
OBJS    = $(notdir $(SRCS:.c=.o))
OUT     = blagger

CC      = gcc
CFLAGS  = $(shell sdl2-config --cflags) -Wall -std=c99 -g -pedantic
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer

#link
$(OUT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

#compile
%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(OUT)
