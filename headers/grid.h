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
        bool cells[MAX_X][MAX_Y];
        /*Array bidimensional temporal del siguiente estado*/
        bool tmp_cells[MAX_X][MAX_Y];
        unsigned int generation;
        bool is_toroidal;
};

/*Devuelve el número de vecinos de una célula dada su posición en
*el tablero
*/
char get_number_of_neighbours(int x, int y,
                              const struct grid *tablero);

/*Devuelve el próximo estado de una célula determinada por su posición*/
bool check_rule(int x, int y,
                 const struct grid *tablero);

/*Comprueba si una célula vecina esta viva o muerta*/
bool check_cell(int x, int y,
                const struct grid *tablero);

/*Imprime el tablero por pantalla*/
void show(struct grid *tablero);

/*Inicializa el tablero y el array temporal*/
void initialize_grid(struct grid *tablero);

/*Actualiza el estado del tablero*/
void update_grid(struct grid *tablero);

#endif
