#include "headers/grid.h"

int main(void) {
        int iters = 20;
        int a;
        struct grid tablero;
        initialize_grid(&tablero);
        (&tablero)->cells[0][1] = true;
        (&tablero)->cells[1][1] = true;
        (&tablero)->cells[1][0] = true;
        (&tablero)->cells[3][1] = true;
        (&tablero)->cells[3][2] = true;
        (&tablero)->cells[4][1] = true;
        (&tablero)->cells[4][0] = true;
        for(a = 0; a < iters; a++) {
                show(&tablero);
                update_grid(&tablero);
                printf("\n\n");
        }
        return 0;
}
