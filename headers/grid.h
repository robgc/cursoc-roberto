#ifndef _GRID_H_
#define _GRID_H_

#include <stdio.h>
#include <stdbool.h>

/*Tamaño del tablero:*/

#define MAX_X 8
#define MAX_Y 8

/*Definición del tablero*/
struct grid {
        /* Falso -> muerta Cierto -> viva*/
        bool cells[MAX_Y][MAX_X];
        unsigned int generation;
};

/*Array bidimensional temporal del siguiente estado*/

bool tmp_cells[MAX_Y][MAX_X];

/*Devuelve el número de vecinos de una célula dada su posición en
*el tablero
*/
char get_number_of_neighbours(const int *x, const int *y,
                              const struct grid *tablero);
/*Devuelve el próximo estado de una célula determinada por su posición*/
bool update_cell(const int *x, const int *y,
                 struct grid *tablero);

/*Imprime el tablero por pantalla*/
void show(struct grid *tablero);

/*Inicializa el tablero y el array temporal*/
void initialize_grid(struct grid *tablero);

/*Actualiza el estado del tablero*/
void update_grid(struct grid *tablero);

#endif
