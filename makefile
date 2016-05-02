.PHONY: clean
all: juego

juego: main.o grid.o
	gcc main.o grid.o -o juego

main.o: headers/grid.h headers/list.h main.c
	gcc -c -g main.c

grid.o: headers/grid.h headers/list.h grid.c
	gcc -c -g grid.c

clean:
	rm -f *.o
	rm -f juego
