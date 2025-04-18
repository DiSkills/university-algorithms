#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct graph {
    int **matrix;
    int size;
};

static struct graph *graph_init(int size)
{
    int i, j;
    struct graph *g;

    g = malloc(sizeof(*g));
    g->matrix = malloc(size * sizeof(*g->matrix));
    g->size = size;

    for (i = 0; i < size; i++) {
        g->matrix[i] = malloc(size * sizeof(*g->matrix[i]));
        for (j = 0; j < size; j++) {
            g->matrix[i][j] = rand() % 2;
        }
    }
    return g;
}

static void graph_print(const struct graph *g)
{
    int i, j;
    for (i = 0; i < g->size; i++) {
        for (j = 0; j < g->size; j++) {
            printf("%d ", g->matrix[i][j]);
        }
        putchar('\n');
    }
}

static void graph_del(struct graph *g)
{
    int i;
    for (i = 0; i < g->size; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    g->matrix = NULL;
    g->size = 0;
}

int main(int argc, char **argv)
{
    struct graph *g;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    g = graph_init(atoi(argv[1]));

    graph_print(g);

    graph_del(g);
    free(g);
    return 0;
}
