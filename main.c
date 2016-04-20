#include "headers/grid.h"

void test_grid_1();
void test_grid_2();
void test_grid_3();
void get_output(struct grid *game_grid);

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
        grid_initialize(tablero, false);

        grid_set_cell(1,0,true,tablero);
        grid_set_cell(1,1,true,tablero);

        grid_set_cell(3,1,true,tablero);
        grid_set_cell(3,2,true,tablero);

        grid_set_cell(4,0,true,tablero);
        grid_set_cell(4,1,true,tablero);

        for(a = 0; a < iters; a++) {
                get_output(tablero);
        }

        grid_free(tablero);
}

void test_grid_2()
{
        printf("******* TABLERO TOROIDAL *******\n");

        struct grid *tablero = grid_alloc();
        grid_initialize(tablero, true);

        grid_set_cell(0,4,true,tablero);
        grid_set_cell(0,5,true,tablero);

        grid_set_cell(5,3,true,tablero);
        grid_set_cell(5,4,true,tablero);

        grid_set_cell(6,5,true,tablero);

        grid_set_cell(7,4,true,tablero);

        for(a = 0; a < iters; a++) {
                get_output(tablero);
        }

        grid_free(tablero);
}

void test_grid_3()
{
        printf("******* OTRO TABLERO TOROIDAL *******\n");

        struct grid *tablero = grid_alloc();
        grid_initialize(tablero, true);

        grid_set_cell(0,7,true,tablero);

        grid_set_cell(7,0,true,tablero);
        grid_set_cell(7,1,true,tablero);
        grid_set_cell(7,7,true,tablero);

        for(a = 0; a < iters; a++) {
                get_output(tablero);
        }

        grid_free(tablero);
}

void get_output(struct grid *game_grid)
{
        grid_show(game_grid);
        grid_update(game_grid);
        printf("\n\n");
}
