#include "headers/grid.h"

void test_grid_1();
void test_grid_2();
void test_grid_3();

static const int iters = 10;
static int a;

int main(void)
{
        test_grid_1();
        test_grid_2();
        test_grid_3();

        return 0;
}

void test_grid_1()
{
        printf("******* TABLERO NO TOROIDAL *******\n");

        struct grid *tablero = grid_alloc();
        initialize_grid(tablero, false);

        tablero->cells[0][1] = true;

        tablero->cells[1][0] = true;
        tablero->cells[1][1] = true;

        tablero->cells[3][1] = true;
        tablero->cells[3][2] = true;

        tablero->cells[4][0] = true;
        tablero->cells[4][1] = true;

        for(a = 0; a < iters; a++) {
                show(tablero);
                update_grid(tablero);
                printf("\n\n");
        }
        
        free_grid(tablero);
}

void test_grid_2()
{
        printf("******* TABLERO TOROIDAL *******\n");

        struct grid *tablero = grid_alloc();
        initialize_grid(tablero, true);

        tablero->cells[0][4] = true;
        tablero->cells[0][5] = true;

        tablero->cells[5][3] = true;
        tablero->cells[5][4] = true;

        tablero->cells[6][5] = true;

        tablero->cells[7][4] = true;

        for(a = 0; a < iters; a++) {
                show(tablero);
                update_grid(tablero);
                printf("\n\n");
        }

        free_grid(tablero);
}

void test_grid_3()
{
        printf("******* OTRO TABLERO TOROIDAL *******\n");

        struct grid *tablero = grid_alloc();
        initialize_grid(tablero, true);

        tablero->is_toroidal = true;

        tablero->cells[0][7] = true;

        tablero->cells[7][0] = true;
        tablero->cells[7][1] = true;
        tablero->cells[7][7] = true;

        for(a = 0; a < iters; a++) {
                show(tablero);
                update_grid(tablero);
                printf("\n\n");
        }

        free_grid(tablero);
}
