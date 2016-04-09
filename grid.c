#include "headers/grid.h"

bool check_cell(int x, int y, const struct grid *tablero)
{
        bool res = false;
        if (tablero->is_toroidal) {
                if (x < 0) {
                        if (y < 0)
                                res = tablero->cells[MAX_Y-1][MAX_X-1];
                        else if (y == MAX_Y)
                                res = tablero->cells[0][MAX_X-1];
                        else
                                res = tablero->cells[y][MAX_X-1];
                } else if (x == MAX_X) {
                        if(y < 0)
                                res = tablero->cells[MAX_Y-1][0];
                        else if (y == MAX_Y)
                                res = tablero->cells[0][0];
                        else
                                res = tablero->cells[y][0];
                } else {
                        if (y < 0)
                                res = tablero->cells[MAX_Y-1][x];
                        else if (y == MAX_Y)
                                res = tablero->cells[0][x];
                        else
                                res = tablero->cells[y][x];
                }
        } else if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y)
                res = tablero->cells[y][x];
        return res;
}

char get_number_of_neighbours(int x, int y, const struct grid *tablero)
{
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
        bool res;
        char neighbours = get_number_of_neighbours(x, y, tablero);
        if (tablero->cells[y][x]) {
                if (neighbours < 2 || neighbours > 3)
                        res = false;
                else
                        res = true;
        } else {
                if (neighbours == 3)
                        res = true;
                else
                        res = false;
        }
        return res;
}

void show(struct grid *tablero)
{
        int i, j;
        for (j = 0; j < MAX_Y; j++) {
                for (i = 0; i < MAX_X; i++) {
                        if (tablero->cells[j][i])
                                printf("|x|");
                        else
                                printf("| |");
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
                        tablero->tmp_cells[j][i] = false;
                }
        }
}

void update_grid(struct grid *tablero)
{
        int i, j;
        for (j = 0; j < MAX_Y; j++)
                for (i = 0; i < MAX_X; i++)
                        tablero->tmp_cells[j][i] = check_rule(i, j, tablero);

        for (j = 0; j < MAX_Y; j++)
                for (i = 0; i < MAX_X; i++)
                        tablero->cells[j][i] = tablero->tmp_cells[j][i];
}
