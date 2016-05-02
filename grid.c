#include "headers/grid.h"

#define ATTR_SET(flags, attr) ((flags) |= (1 << (attr)))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))

struct grid {
        /* Falso -> muerta Cierto -> viva*/
        bool *cells;
        unsigned int generation;
        bool is_toroidal;
        unsigned int height;
        unsigned int width;
        struct list_head alive_cells;
        uint8_t flags;
};

struct list_cell {
        int x;
        int y;
        struct list_head list;
};

enum grid_attr {
        GRID_CELLS,
        GRID_GENERATION,
        GRID_IS_TOROIDAL,
        GRID_HEIGHT,
        GRID_WIDTH,
        GRID_ALIVE_CELLS
};

struct grid *grid_alloc(int height, int width)
{
        struct grid *game_grid;
        game_grid = (struct grid *)malloc(sizeof(struct grid));

        if (!game_grid) {
                printf("\nERROR: No se ha podido reservar memoria \
                        para el tablero\n");
                exit(-2);
        }

        game_grid->flags = 0;

        /*Reservamos memoria para un array tridimensional*/

        game_grid->cells = (bool *)malloc(2 * height * width
                                          * sizeof(bool));

        if (!game_grid->cells) {
                printf("\nERROR: No se pudo reservar memoria para las \
                        casillas del tablero");
                exit(-3);
        }

        game_grid->height = height;
        game_grid->width = width;

        ATTR_SET(game_grid->flags, GRID_CELLS);
        ATTR_SET(game_grid->flags, GRID_HEIGHT);
        ATTR_SET(game_grid->flags, GRID_WIDTH);

        return game_grid;
}

struct list_cell *grid_list_cell_alloc(int x, int y)
{
        struct list_cell *lc;
        lc = (struct list_cell *)malloc(sizeof(struct list_cell));

        if(!lc) {
                printf("\nERROR: No se pudo reservar memoria para una \
                       célula para la lista de análisis\n");
                exit(-4);
        }

        lc->x = x;
        lc->y = y;

        return lc;
}

void grid_free(struct grid *game_grid)
{
        struct list_cell *lc;
        struct list_cell *tmp;
        if (ATTR_IS_SET(game_grid->flags, GRID_CELLS))
                free(game_grid->cells);
        if (ATTR_IS_SET(game_grid->flags, GRID_ALIVE_CELLS))
                grid_clean_list(&(game_grid->alive_cells));

        free(game_grid);
}

void grid_fix_crds(int *x_in, int *y_in,
                   const struct grid *game_grid)
{
        if (*x_in < 0)
                *x_in = game_grid->height - 1;
        else if (*x_in == game_grid->height)
                *x_in = 0;

        if (*y_in < 0)
                *y_in = game_grid->width - 1;
        else if (*y_in == game_grid->width)
                *y_in = 0;
}

bool grid_check_cell(int x, int y, const struct grid *game_grid)
{
        grid_check(game_grid);
        bool res = false;
        int x_fixed = x;
        int y_fixed = y;

        if (game_grid->is_toroidal) {
                grid_fix_crds(&x_fixed, &y_fixed, game_grid);
                res = grid_get_cell(x_fixed, y_fixed, game_grid);
        } else if (x >= 0 && x < game_grid->height && y >= 0
                   && y < game_grid->width)
                res = grid_get_cell(x, y, game_grid);

        return res;
}

char grid_get_number_of_neighbours(int x, int y,
                                   const struct grid *game_grid)
{
        char res = 0;
        int x_fixed = x;
        int y_fixed = y;

        if (game_grid->is_toroidal)
                grid_fix_crds(&x_fixed, &y_fixed, game_grid);

        res += grid_check_cell(x_fixed - 1, y_fixed - 1, game_grid);
        res += grid_check_cell(x_fixed - 1, y_fixed, game_grid);
        res += grid_check_cell(x_fixed - 1, y_fixed + 1, game_grid);
        res += grid_check_cell(x_fixed, y_fixed - 1, game_grid);
        res += grid_check_cell(x_fixed, y_fixed + 1, game_grid);
        res += grid_check_cell(x_fixed + 1, y_fixed - 1, game_grid);
        res += grid_check_cell(x_fixed + 1, y_fixed, game_grid);
        res += grid_check_cell(x_fixed + 1, y_fixed + 1, game_grid);
        return res;
}

bool grid_check_rule(int x, int y,
                     const struct grid *game_grid)
{
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
        for (i = 0; i < game_grid->height; i++) {
                printf("|");
                for (j = 0; j < game_grid->width; j++) {
                        printf("%s", grid_get_cell(i, j, game_grid)?
                               "x|" : " |");
                }
                printf("\n");
        }

        printf("Generation: %u\n\n\n", game_grid->generation);
}

void grid_init(struct grid *game_grid, bool toroidal)
{
        int i, j;
        game_grid->generation = 0;
        game_grid->is_toroidal = toroidal;

        memset(game_grid->cells, 0, game_grid->height * game_grid->width);
        grid_init_cell_list(game_grid);

        ATTR_SET(game_grid->flags, GRID_GENERATION);
        ATTR_SET(game_grid->flags, GRID_IS_TOROIDAL);
        ATTR_SET(game_grid->flags, GRID_ALIVE_CELLS);
}

void grid_update(struct grid *game_grid)
{
        grid_check(game_grid);

        int i, j;
        struct list_cell *lc;

        game_grid->generation++;

        grid_update_cell_list(game_grid);

}

void grid_check(const struct grid *game_grid)
{
        if (!ATTR_IS_SET(game_grid->flags, GRID_CELLS) ||
            !ATTR_IS_SET(game_grid->flags, GRID_GENERATION) ||
            !ATTR_IS_SET(game_grid->flags, GRID_IS_TOROIDAL) ||
            !ATTR_IS_SET(game_grid->flags, GRID_HEIGHT) ||
            !ATTR_IS_SET(game_grid->flags, GRID_WIDTH) ||
            !ATTR_IS_SET(game_grid->flags, GRID_ALIVE_CELLS)) {
                    printf("\nNo se puede operar con un tablero incompleto\n");
                    exit(-1);
            }
}

void grid_set_cell(int x, int y, bool value, struct grid *game_grid)
{
        struct list_cell *lc;

        if (game_grid->generation == 0 && value)
                grid_add_cell_to_list(x, y, &(game_grid->alive_cells),
                                      game_grid);

        *(game_grid->cells + x * game_grid->width + y) = value;
}

bool grid_get_cell(int x, int y, const struct grid *game_grid)
{
        int x_fixed = x;
        int y_fixed = y;
        bool res = false;

        if (game_grid->is_toroidal) {
                grid_fix_crds(&x_fixed, &y_fixed, game_grid);
                res = *(game_grid->cells + x_fixed * game_grid->width
                         + y_fixed);
        } else if (x >= 0 && x < game_grid->height && y >= 0
                   && y < game_grid->width)
                res = *(game_grid->cells + x * game_grid->width
                         + y);

        return res;
}

bool grid_get_is_toroidal(const struct grid *game_grid)
{
        grid_check(game_grid);

        return game_grid->is_toroidal;
}

int grid_get_generation(const struct grid *game_grid)
{
        grid_check(game_grid);

        return game_grid->generation;
}

void grid_init_cell_list(struct grid *game_grid)
{
        INIT_LIST_HEAD(&(game_grid->alive_cells));
}

void grid_update_cell_list(struct grid *game_grid)
{
        struct list_cell *lc;
        struct list_cell *tmp;
        struct list_head to_kill;
        struct list_head to_revive;
        bool a, b, c = false;

        INIT_LIST_HEAD(&to_kill);
        INIT_LIST_HEAD(&to_revive);

        list_for_each_entry_safe(lc, tmp, &(game_grid->alive_cells), list) {
                /*Si no sobrevive se mueve a la lista de matar*/
                if (!grid_check_rule(lc->x, lc->y, game_grid))
                        list_move_tail(&lc->list, &to_kill);
                /*Revisamos las vecinas*/
                for (int i = -1; i <= 1; i++) {
                        for (int j = -1; j <= 1; j++) {
                                a = !(i == 0 && j == 0);
                                b = !grid_get_cell(lc->x + i, lc->y + j,
                                                   game_grid);
                                c = grid_check_rule(lc->x + i, lc->y + j,
                                                   game_grid);
                                if (a && b && c) {
                                        grid_add_cell_to_list(lc->x + i,
                                                              lc->y + j,
                                                              &to_revive,
                                                              game_grid);
                                }
                        }
                }
        }

        list_for_each_entry_safe(lc, tmp, &to_kill, list) {
                grid_set_cell(lc->x, lc->y, false, game_grid);
                list_del(&lc->list);
                free(lc);
        }

        list_for_each_entry_safe(lc, tmp, &to_revive, list) {
                if (!grid_get_cell(lc->x, lc->y, game_grid)) {
                        grid_set_cell(lc->x, lc->y, true, game_grid);
                        list_move_tail(&lc->list, &(game_grid->alive_cells));
                } else {
                        list_del(&lc->list);
                        free(lc);
                }
        }
}

void grid_add_cell_to_list(int x, int y, struct list_head *in_list,
                           struct grid *game_grid)
{
        struct list_cell *lc;
        int x_fixed = x;
        int y_fixed = y;

        if (game_grid->is_toroidal) {
                grid_fix_crds(&x_fixed, &y_fixed, game_grid);
        }

        lc = grid_list_cell_alloc(x_fixed, y_fixed);
        list_add_tail(&(lc->list), in_list);
}

void grid_clean_list(struct list_head *in_list)
{
        struct list_cell *lc;
        struct list_cell *tmp;
        list_for_each_entry_safe(lc, tmp, in_list, list) {
                list_del(&(lc->list));
                free(lc);
        }
}
