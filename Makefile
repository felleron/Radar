CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I/usr/include/SDL2
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer -lm

all: radar

radar: main.o
	$(CC) $^ -o $@ $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f radar main.o

