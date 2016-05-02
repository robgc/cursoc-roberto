#include "headers/grid.h"
#include <getopt.h>

void test_grid_1();
void get_output(struct grid *game_grid);

void get_input(int argc, char **argv);

static const int iters = 10;
static int a;
static bool g_toroidal;
static unsigned int g_height;
static unsigned int g_width;

int main(int argc, char **argv)
{
        get_input(argc, argv);
        test_grid_1();

        exit(0);
}

void get_input(int argc, char **argv)
{
        bool toroidal = false;
        int width, height, c;

        int option_index = 0;

        static struct option long_options[] =
        {
                {"width", required_argument, 0, 'w'},
                {"height", required_argument, 0, 'h'},
                {"toroidal", no_argument, 0, 't'},
                {0, 0, 0, 0}
        };

        while ((c = getopt_long(argc, argv, "h:w:t", long_options,
                &option_index)) != -1) {
                switch (c) {
                case 'w':
                        width = strtol(optarg, NULL, 0);
                        break;
                case 'h':
                        height = strtol(optarg, NULL, 0);
                        break;
                case 't':
                        toroidal = true;
                        break;
                case '?':
                        break;
                default:
                        printf("Error\n");
                        exit(EXIT_FAILURE);
                }
        }

        for (int i = optind; i < argc; i++)
                printf("Unknown argument: \"%s\"\n", argv[i]);

        g_height = height;
        g_width = width;
        g_toroidal = toroidal;
}

void test_grid_1()
{
        printf("******* TABLERO NO TOROIDAL *******\n");

        struct grid *g_grid = grid_alloc(g_height, g_width);
        grid_init(g_grid, g_toroidal);

        grid_set_cell(0, 2, true, g_grid);

        grid_set_cell(1, 0, true, g_grid);
        grid_set_cell(1, 6, true, g_grid);
        grid_set_cell(1, 7, true, g_grid);

        grid_set_cell(2, 0, true, g_grid);

        grid_set_cell(3, 7, true, g_grid);

        grid_set_cell(5, 1, true, g_grid);
        grid_set_cell(5, 2, true, g_grid);
        grid_set_cell(5, 3, true, g_grid);

        grid_set_cell(6, 7, true, g_grid);

        grid_set_cell(7, 0, true, g_grid);

        for(a = 0; a < iters; a++)
                get_output(g_grid);

        grid_free(g_grid);
}

void get_output(struct grid *game_grid)
{
        grid_show(game_grid);
        grid_update(game_grid);
        printf("\n\n");
}
