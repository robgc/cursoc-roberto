#include "headers/grid.h"

#define ATTR_SET(flags, attr) ((flags) |= (1 << (attr)))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))

struct grid {
        /* Falso -> muerta Cierto -> viva*/
        bool *cells;
        unsigned int generation;
        bool is_toroidal;
        uint8_t flags;
};

enum grid_attr {
        GRID_CELLS,
        GRID_GENERATION,
        GRID_IS_TOROIDAL
};

struct grid *grid_alloc()
{
        struct grid *game_grid;
        game_grid = (struct grid *)malloc(sizeof(struct grid));

        if (!game_grid) {
                printf("\nERROR: No se ha podido reservar memoria \
                        para el tablero\n");
                exit(-2);
        }

        /*Reservamos memoria para un array tridimensional*/

        game_grid->cells = (bool *)malloc(2 * MAX_X * MAX_Y
                                          * sizeof(bool));

        if (!game_grid->cells) {
                printf("\nERROR: No se pudo reservar memoria para las \
                        casillas del tablero");
                exit(-3);
        }

        game_grid->flags = 0;
        return game_grid;
}

void grid_free(struct grid *game_grid)
{
        if (ATTR_IS_SET(game_grid->flags, GRID_CELLS))
                free(game_grid->cells);
        free(game_grid);
}

bool grid_check_cell(int x, int y, const struct grid *game_grid)
{
        grid_check(game_grid);
        bool res = false;
        int x_fixed;
        int y_fixed;

        if (game_grid->is_toroidal) {
                if (x < 0)
                        x_fixed = MAX_X - 1;
                else if (x == MAX_X)
                        x_fixed = 0;
                else
                        x_fixed = x;

                if (y < 0)
                        y_fixed = MAX_Y - 1;
                else if (y == MAX_Y)
                        y_fixed = 0;
                else
                        y_fixed = y;

                res = grid_get_cell(x_fixed, y_fixed, game_grid);
        } else if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y)
                res = grid_get_cell(x, y, game_grid);

        return res;
}

char grid_get_number_of_neighbours(int x, int y, const struct grid *game_grid)
{
        char res = 0;
        res += grid_check_cell(x-1, y-1, game_grid);
        res += grid_check_cell(x-1, y, game_grid);
        res += grid_check_cell(x-1, y+1, game_grid);
        res += grid_check_cell(x, y-1, game_grid);
        res += grid_check_cell(x, y+1, game_grid);
        res += grid_check_cell(x+1, y-1, game_grid);
        res += grid_check_cell(x+1, y, game_grid);
        res += grid_check_cell(x+1, y+1, game_grid);
        return res;
}

bool grid_check_rule(int x, int y,
                const struct grid *game_grid)
{
        grid_check(game_grid);
        char neighbours = grid_get_number_of_neighbours(x, y, game_grid);
        if (grid_get_cell(x, y, game_grid))
                return (neighbours == 2 || neighbours == 3);
        else
                return neighbours == 3;

}

void grid_show(const struct grid *game_grid)
{
        grid_check(game_grid);

        int i, j;
        for (i = 0; i < MAX_X; i++) {
                for (j = 0; j < MAX_Y; j++) {
                        if (grid_get_cell(i, j, game_grid) && j == 0)
                                printf("|x|");
                        else if (grid_get_cell(i, j, game_grid) && j != 0)
                                printf("x|");
                        else if (!grid_get_cell(i, j, game_grid) && j == 0)
                                printf("| |");
                        else
                                printf(" |");
                }
                printf("\n");
        }

        printf("Generation: %u\n\n\n", game_grid->generation + 1);
}

void grid_initialize(struct grid *game_grid, bool toroidal)
{
        int i, j;
        game_grid->generation = 0;
        game_grid->is_toroidal = toroidal;

        for (i = 0; i < MAX_X; i++) {
                for (j = 0; j < MAX_Y; j++) {
                        *(game_grid->cells + i * MAX_Y + j) = false;
                        *(game_grid->cells + MAX_X * MAX_Y
                          + i * MAX_Y + j) = false;
                }
        }

        ATTR_SET(game_grid->flags, GRID_CELLS);
        ATTR_SET(game_grid->flags, GRID_GENERATION);
        ATTR_SET(game_grid->flags, GRID_IS_TOROIDAL);
}

void grid_update(struct grid *game_grid)
{
        grid_check(game_grid);

        int i, j, v;
        v = (game_grid->generation + 1) % 2;
        for (i = 0; i < MAX_X; i++)
                for (j = 0; j < MAX_Y; j++)
                        *(game_grid->cells + v * MAX_X * MAX_Y
                          + i * MAX_Y + j) = grid_check_rule(i, j, game_grid);

        game_grid->generation++;
}

void grid_check(const struct grid *game_grid)
{
        if (!ATTR_IS_SET(game_grid->flags, GRID_CELLS) ||
            !ATTR_IS_SET(game_grid->flags, GRID_GENERATION) ||
            !ATTR_IS_SET(game_grid->flags, GRID_IS_TOROIDAL)) {
                    printf("\nNo se puede operar con un tablero incompleto\n");
                    exit(-1);
            }
}

void grid_set_cell(int x, int y, bool value, struct grid *game_grid)
{
        grid_check(game_grid);

        int act = game_grid->generation % 2;
        *(game_grid->cells + act * MAX_X * MAX_Y + x * MAX_Y + y) = value;
}

bool grid_get_cell(int x, int y, const struct grid *game_grid)
{
        grid_check(game_grid);

        int act = game_grid->generation % 2;

        return *(game_grid->cells + act * MAX_X * MAX_Y + x * MAX_Y + y);
}

bool grid_get_is_toroidal(const struct grid *game_grid)
{
        grid_check(game_grid);

        return game_grid->is_toroidal;
}

unsigned int grid_get_generation(const struct grid *game_grid)
{
        grid_check(game_grid);

        return game_grid->generation;
}
