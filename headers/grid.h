#ifndef _GRID_H_
#define _GRID_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* Definición del tablero */
struct grid;

/* Estructura para la lista de células */
struct list_cell;

/* Reserva memoria para el tablero */
struct grid *grid_alloc(int height, int width);

/* Reserva memoria */
struct list_cell *grid_list_cell_alloc(int x, int y);

/* Libera la memoria reservada previamente para el tablero */
void grid_free(struct grid *game_grid);

/*
* Devuelve el número de vecinos de una célula dada su posición en
* el tablero
*/
char grid_get_number_of_neighbours(int x, int y,
                                   const struct grid *game_grid);

/* Devuelve el próximo estado de una célula determinada por su posición */
bool grid_check_rule(int x, int y,
                     const struct grid *game_grid);

/* Imprime el tablero por pantalla */
void grid_show(const struct grid *game_grid);

/* Inicializa el tablero y el array temporal */
void grid_init(struct grid *game_grid, bool toroidal);

/* Actualiza el estado del tablero */
void grid_update(struct grid *game_grid);

/* Comprueba si los atributos han sido establecidos */
void grid_check(const struct grid *game_grid);

/* Establece el estado de una célula en concreto */
void grid_set_cell(int x, int y,
                   bool value, struct grid *game_grid);

/* Devuelve el estado de una célula en concreto */
bool grid_get_cell(int x, int y,
                   const struct grid *game_grid);

/* Indica si el tablero es o no toroidal */
bool grid_get_is_toroidal(const struct grid *game_grid);

/*
* Devuelve la generación en la que se encuentra el tablero
* (comenzando desde 0)
*/
int grid_get_generation(const struct grid *game_grid);

/* Inicializa la lista de células vivas */
void grid_init_cell_list(struct grid *game_grid);

/* Actualiza la lista de células vivas */
void grid_update_cell_list(struct grid *game_grid);

/* Añade una célula a la lista */
void grid_add_cell_to_list(int x, int y,
                           struct list_head *in_list,
                           struct grid *game_grid);

/* Elimina el contenido de una lista */
void grid_clean_list(struct list_head *in_list);

/* Corrige las coordenadas si el tablero es toroidal */
void grid_fix_crds(int *x_in, int *y_in,
                   const struct grid *game_grid);

/* Inicia el juego a partir de un archivo de texto */
void grid_read_file(const char *file_name, struct grid *game_grid);

/* Devuelve el número de células en el estado actual del tablero */
unsigned int grid_get_num_of_alive_cells(const struct grid *game_grid);

/*
* Escribe en un archivo un historial del número de células vivas
* por cada estado
*/
void grid_write_output(const struct grid *game_grid);

/* Crea un archivo que almacena el último estado del mundo */
void grid_save_state(const struct grid *game_grid);

#endif
