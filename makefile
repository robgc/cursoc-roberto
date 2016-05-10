.PHONY: clean
all: gol

gol: main.o grid.o
	gcc main.o grid.o -o gol

main.o: headers/grid.h main.c
	gcc -c -g main.c

grid.o: headers/grid.h headers/list.h grid.c
	gcc -c -g grid.c

clean:
	rm -f *.o
	rm -f gol
	rm -f output.txt
	rm -f state.txt
