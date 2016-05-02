#ifndef _GRID_H_
#define _GRID_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*Definición del tablero*/
struct grid;

/*Estructura para la lista de células*/
struct list_cell;

/*Reserva memoria para el tablero*/
struct grid *grid_alloc(int height, int width);

/*Reserva memoria */
struct list_cell *grid_list_cell_alloc(int x, int y);

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
void grid_init(struct grid *game_grid, bool toroidal);

/*Actualiza el estado del tablero*/
void grid_update(struct grid *game_grid);

/*Comprueba si los atributos han sido establecidos*/
void grid_check(const struct grid *game_grid);

/*Establece el estado de una célula en concreto*/
void grid_set_cell(int x, int y,
                   bool value, struct grid *game_grid);

/*Devuelve el estado de una célula en concreto*/
bool grid_get_cell(int x, int y,
                   const struct grid *game_grid);

/*Indica si el tablero es o no toroidal*/
bool grid_get_is_toroidal(const struct grid *game_grid);

/*Devuelve la generación en la que se encuentra el tablero
(comenzando desde 0)*/
int grid_get_generation(const struct grid *game_grid);

/*Inicializa la lista de células vivas*/
void grid_init_cell_list(struct grid *game_grid);

/*Actualiza la lista de células vivas*/
void grid_update_cell_list(struct grid *game_grid);

/*Añade una célula a la lista*/
void grid_add_cell_to_list(int x, int y,
                           struct list_head *in_list,
                           struct grid *game_grid);

void grid_clean_list(struct list_head *in_list);

struct list_head grid_get_list_cell(struct grid *game_grid);

void grid_fix_crds(int *x_in, int *y_in,
                   const struct grid *game_grid);

#endif
