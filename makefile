CFLAGS = -Wall -Error

.PHONY : all clean

all : game_of_life

game_of_life : main.o gol.o
	gcc main.o gol.o -o game_of_life

main.o : main.c gol.h
	gcc -c main.c

gol.o : gol.c gol.h
	gcc -c gol.c

clean: 
	rm *.o
	rm game_of_life