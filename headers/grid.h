#ifndef _GRID_H_
#define _GRID_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/*Tamaño del tablero:*/
#define MAX_X 8
#define MAX_Y 8

/*Definición del tablero*/
struct grid;

struct grid *grid_alloc();

void grid_free(struct grid *game_grid);

/*Devuelve el número de vecinos de una célula dada su posición en
*el tablero
*/
char grid_get_number_of_neighbours(int x, int y,
                              const struct grid *game_grid);

/*Devuelve el próximo estado de una célula determinada por su posición*/
bool grid_check_rule(int x, int y,
                 const struct grid *game_grid);

/*Comprueba si una célula vecina esta viva o muerta*/
bool grid_check_cell(int x, int y,
                const struct grid *game_grid);

/*Imprime el tablero por pantalla*/
void grid_show(const struct grid *game_grid);

/*Inicializa el tablero y el array temporal*/
void grid_initialize(struct grid *game_grid, bool toroidal);

/*Actualiza el estado del tablero*/
void grid_update(struct grid *game_grid);

/*Comprueba si los atributos han sido establecidos*/
void grid_check(const struct grid *game_grid);

/*Establece el estado de una célula en concreto*/
void grid_set_cell(int x, int y, bool value, struct grid *game_grid);

/*Devuelve el estado de una célula en concreto*/
bool grid_get_cell(int x, int y, const struct grid *game_grid);

/*Indica si el tablero es o no toroidal*/
bool grid_get_is_toroidal(const struct grid *game_grid);

/*Devuelve la generación en la que se encuentra el tablero
(comenzando desde 0)*/
unsigned int grid_get_generation(const struct grid *game_grid);

#endif
