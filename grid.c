#include "headers/grid.h"

bool check_cell(int x, int y, const struct grid *tablero)
{
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
        char neighbours = get_number_of_neighbours(x, y, tablero);
        if (tablero->cells[x][y]) {
                return (neighbours == 2 || neighbours == 3);
        } else {
                return neighbours == 3;
        }
}

void show(struct grid *tablero)
{
        int i, j;
        for (i = 0; i < MAX_X; i++) {
                for (j = 0; j < MAX_Y; j++) {
                        if (tablero->cells[i][j])
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
        for (i = 0; i < MAX_X; i++) {
                for (j = 0; j < MAX_Y; j++) {
                        tablero->cells[i][j] = false;
                        tablero->tmp_cells[i][j] = false;
                }
        }
}

void update_grid(struct grid *tablero)
{
        int i, j;
        for (i = 0; i < MAX_X; i++)
                for (j = 0; j < MAX_Y; j++)
                        tablero->tmp_cells[i][j] = check_rule(i, j, tablero);

        for (i = 0; i < MAX_X; i++)
                for (j = 0; j < MAX_Y; j++)
                        tablero->cells[i][j] = tablero->tmp_cells[i][j];
}
