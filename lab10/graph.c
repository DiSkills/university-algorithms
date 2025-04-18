#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

struct graph *graph_init(int size)
{
    int i;
    struct graph *g;

    g = malloc(sizeof(*g));
    g->matrix = malloc(size * sizeof(*g->matrix));
    g->size = size;

    for (i = 0; i < size; i++) {
        g->matrix[i] = malloc(size * sizeof(*g->matrix[i]));
    }
    return g;
}

void graph_generate(struct graph *g)
{
    int i, j, size;

    size = g->size;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            g->matrix[i][j] = rand() % 2;
        }
    }
}

void graph_print(const struct graph *g)
{
    int i, j;
    for (i = 0; i < g->size; i++) {
        for (j = 0; j < g->size; j++) {
            printf("%d ", g->matrix[i][j]);
        }
        putchar('\n');
    }
}

void graph_del(struct graph *g)
{
    int i;
    for (i = 0; i < g->size; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    g->matrix = NULL;
    g->size = 0;
}

static void array_shuffle(int *arr, int size)
{
    int i;
    for (i = size - 1; i > 0; i--) {
        int tmp;
        int j = rand() % (i + 1);

        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

struct graph *graph_shuffle(const struct graph *g)
{
    struct graph *h;
    int size, i, j, *transform;

    size = g->size;
    transform = malloc(size * sizeof(*transform));
    for (i = 0; i < size; i++) {
        transform[i] = i;
    }
    array_shuffle(transform, size);

    h = graph_init(size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            h->matrix[transform[i]][transform[j]] = g->matrix[i][j];
        }
    }
    free(transform);
    return h;
}
