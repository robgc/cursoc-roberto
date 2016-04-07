all: juego

juego: main.o grid.o
	gcc main.o grid.o -o juego

main.o: main.c
	gcc -c main.c

grid.o: headers/grid.h grid.c
	gcc -c grid.c
