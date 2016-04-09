#include "headers/grid.h"

int main(void) {
        /*Numero de iteraciones*/
        int iters = 10;
        int a;

        /*Inicialización del tablero*/
        printf("******* TABLERO NO TOROIDAL *******\n");

        struct grid tablero;
        initialize_grid(&tablero);
        (&tablero)->is_toroidal = false;

        /*Introducimos células en el tablero*/
        (&tablero)->cells[0][1] = true;

        (&tablero)->cells[1][0] = true;
        (&tablero)->cells[1][1] = true;

        (&tablero)->cells[3][1] = true;
        (&tablero)->cells[3][2] = true;

        (&tablero)->cells[4][0] = true;
        (&tablero)->cells[4][1] = true;

        for(a = 0; a < iters; a++) {
                show(&tablero);
                update_grid(&tablero);
                printf("\n\n");
        }

        printf("******* TABLERO TOROIDAL *******\n");

        initialize_grid(&tablero);
        (&tablero)->is_toroidal = true;

        (&tablero)->cells[0][4] = true;
        (&tablero)->cells[0][5] = true;

        (&tablero)->cells[5][3] = true;
        (&tablero)->cells[5][4] = true;

        (&tablero)->cells[6][5] = true;

        (&tablero)->cells[7][4] = true;

        for(a = 0; a < iters; a++) {
                show(&tablero);
                update_grid(&tablero);
                printf("\n\n");
        }

        printf("******* OTRO TABLERO TOROIDAL *******\n");

        initialize_grid(&tablero);
        (&tablero)->is_toroidal = true;

        (&tablero)->cells[0][7] = true;

        (&tablero)->cells[7][0] = true;
        (&tablero)->cells[7][1] = true;
        (&tablero)->cells[7][7] = true;

        for(a = 0; a < iters; a++) {
                show(&tablero);
                update_grid(&tablero);
                printf("\n\n");
        }
        return 0;
}
