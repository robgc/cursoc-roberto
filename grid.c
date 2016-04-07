#include "headers/grid.h"

char get_number_of_neighbours(const int *x,
                              const int *y, const struct grid *tablero)
{
        char res = 0;
        char i, j;
        if (*x >= MAX_X || *x < 0 || *y >= MAX_Y || *y < 0) {
                res = 0;
        } else {
                for (j = (*y) - 1; j <= (*y) + 1; j++) {
                        for (i = (*x) - 1; i <= (*x) + 1; i++) {
                                if (i >= 0 && i < MAX_X
                                    && j >= 0 && j < MAX_Y
                                    && !(i == (*x) && j == (*y))) {
                                        if(tablero->cells[j][i]) {
                                                res++;
                                        }
                                }
                        }
                }
        }
        return res;
}

bool update_cell(const int *x, const int *y,
                 struct grid *tablero)
{
        bool res;
        char neighbours = get_number_of_neighbours(x, y, tablero);
        if (tablero->cells[*y][*x]) {
                if (neighbours < 2 || neighbours > 3) {
                        res = false;
                } else {
                        res = true;
                }
        } else {
                if (neighbours == 3) {
                        res = true;
                } else {
                        res = false;
                }
        }
        return res;
}

void show(struct grid *tablero)
{
        int i, j;
        for (j = 0; j < MAX_Y; j++) {
                for (i = 0; i < MAX_X; i++) {
                        if (tablero->cells[j][i]) {
                                printf("|x|");
                        } else {
                                printf("| |");
                        }
                }
                printf("\n");
        }
        tablero->generation++;
        printf("Generation: %u\n\n\n", tablero->generation);
}

void initialize_grid(struct grid *tablero)
{
        int i, j;
        tablero->generation = 0;
        for (j = 0; j < MAX_Y; j++) {
                for (i = 0; i < MAX_X; i++) {
                        tablero->cells[j][i] = false;
                        tmp_cells[j][i] = false;
                }
        }
}

void update_grid(struct grid *tablero)
{
        int i, j;
        for (j = 0; j < MAX_Y; j++) {
                for (i = 0; i < MAX_X; i++) {
                        tmp_cells[j][i] = update_cell(&i, &j, tablero);
                }
        }
        for (j = 0; j < MAX_Y; j++) {
                for (i = 0; i < MAX_X; i++) {
                        tablero->cells[j][i] = tmp_cells[j][i];
                }
        }
}
