#include "headers/grid.h"

#define ATTR_SET(flags, attr) ((flags) |= (1 << (attr)))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))

enum grid_attr {
        GRID_CELLS,
        GRID_TMP_CELLS,
        GRID_GENERATION,
        GRID_IS_TOROIDAL
};

struct grid *grid_alloc()
{
        struct grid *tablero;
        tablero = (struct grid *)malloc(sizeof(struct grid));

        if (!tablero) {
                printf("\nERROR: No se ha podido reservar memoria \
                        para el tablero\n");
                exit(-2);
        }

        tablero->flags = 0;
        return tablero;
}

void free_grid(struct grid *tablero)
{
        free(tablero);
}

bool check_cell(int x, int y, const struct grid *tablero)
{
        check_grid(tablero);
        bool res = false;
        if (tablero->is_toroidal) {
                if (x < 0) {
                        if (y < 0)
                                res = tablero->cells[MAX_X-1][MAX_Y-1];
                        else if (y == MAX_Y)
                                res = tablero->cells[MAX_X-1][0];
                        else
                                res = tablero->cells[MAX_X-1][y];
                } else if (x == MAX_X) {
                        if(y < 0)
                                res = tablero->cells[0][MAX_Y-1];
                        else if (y == MAX_Y)
                                res = tablero->cells[0][0];
                        else
                                res = tablero->cells[0][y];
                } else {
                        if (y < 0)
                                res = tablero->cells[x][MAX_Y-1];
                        else if (y == MAX_Y)
                                res = tablero->cells[x][0];
                        else
                                res = tablero->cells[x][y];
                }
        } else if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y)
                res = tablero->cells[x][y];
        return res;
}

char get_number_of_neighbours(int x, int y, const struct grid *tablero)
{
        check_grid(tablero);

        char res = 0;
        res += check_cell(x-1,y-1,tablero);
        res += check_cell(x-1,y,tablero);
        res += check_cell(x-1,y+1,tablero);
        res += check_cell(x,y-1,tablero);
        res += check_cell(x,y+1,tablero);
        res += check_cell(x+1,y-1,tablero);
        res += check_cell(x+1,y,tablero);
        res += check_cell(x+1,y+1,tablero);
        return res;
}

bool check_rule(int x, int y,
                const struct grid *tablero)
{
        check_grid(tablero);
        char neighbours = get_number_of_neighbours(x, y, tablero);
        if (tablero->cells[x][y]) {
                return (neighbours == 2 || neighbours == 3);
        } else {
                return neighbours == 3;
        }
}

void show(struct grid *tablero)
{
        check_grid(tablero);

        int i, j;
        for (i = 0; i < MAX_X; i++) {
                for (j = 0; j < MAX_Y; j++) {
                        if (tablero->cells[i][j] && j == 0)
                                printf("|x|");
                        else if (tablero->cells[i][j] && j != 0)
                                printf("x|");
                        else if (!(tablero->cells[i][j]) && j == 0)
                                printf("| |");
                        else
                                printf(" |");
                }
                printf("\n");
        }

        tablero->generation++;
        printf("Generation: %u\n\n\n", tablero->generation);
}

void initialize_grid(struct grid *tablero, bool toroidal)
{
        int i, j;
        tablero->generation = 0;
        tablero->is_toroidal = toroidal;

        for (i = 0; i < MAX_X; i++) {
                for (j = 0; j < MAX_Y; j++) {
                        tablero->cells[i][j] = false;
                        tablero->tmp_cells[i][j] = false;
                }
        }

        ATTR_SET(tablero->flags, GRID_CELLS);
        ATTR_SET(tablero->flags, GRID_TMP_CELLS);
        ATTR_SET(tablero->flags, GRID_GENERATION);
        ATTR_SET(tablero->flags, GRID_IS_TOROIDAL);
}

void update_grid(struct grid *tablero)
{
        check_grid(tablero);

        int i, j;
        for (i = 0; i < MAX_X; i++)
                for (j = 0; j < MAX_Y; j++)
                        tablero->tmp_cells[i][j] = check_rule(i, j, tablero);

        for (i = 0; i < MAX_X; i++)
                for (j = 0; j < MAX_Y; j++)
                        tablero->cells[i][j] = tablero->tmp_cells[i][j];
}

void check_grid(const struct grid *tablero)
{
        if (!ATTR_IS_SET(tablero->flags, GRID_CELLS) ||
            !ATTR_IS_SET(tablero->flags, GRID_TMP_CELLS) ||
            !ATTR_IS_SET(tablero->flags, GRID_GENERATION) ||
            !ATTR_IS_SET(tablero->flags, GRID_IS_TOROIDAL)) {
                    printf("\nNo se puede operar con un tablero incompleto\n");
                    exit(-1);
            }
}
