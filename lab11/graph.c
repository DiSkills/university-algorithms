#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

long long counter = 0;

#define SWAP(A, B)                                                           \
    do {                                                                     \
        int tmp = (A);                                                       \
        (A) = (B);                                                           \
        (B) = tmp;                                                           \
    } while (0);

struct graph *graph_init(int size)
{
    int i, j;
    struct graph *g;

    g = malloc(sizeof(*g));
    g->matrix = malloc(size * sizeof(*g->matrix));
    g->size = size;

    for (i = 0; i < size; i++) {
        g->matrix[i] = malloc(size * sizeof(*g->matrix[i]));
        for (j = 0; j < size; j++) {
            g->matrix[i][j] = 0;
        }
    }
    return g;
}

void graph_input(struct graph *g)
{
    int i, j;
    for (i = 0; i < g->size; i++) {
        for (j = 0; j < g->size; j++) {
            scanf("%d", &g->matrix[i][j]);
        }
    }
}

void graph_generate(struct graph *g, int m, int n)
{
    int i, j;

    /* the first row */
    for (i = 0; i < n - 1; i++) {
        g->matrix[i][i + 1] = 1;
        g->matrix[i + 1][i] = 1;
    }

    /* the first column */
    for (i = 0; i < m - 1; i++) {
        g->matrix[i * n][i * n + n] = 1;
        g->matrix[i * n + n][i * n] = 1;
    }

    for (i = 1; i < m - 1; i++) {
        for (j = 1; j < n - 1; j++) {
            int v= i * n + j;

            g->matrix[v][v + 1] = 1;
            g->matrix[v][v - 1] = 1;
            g->matrix[v][v - n] = 1;
            g->matrix[v][v + n] = 1;

            g->matrix[v + 1][v] = 1;
            g->matrix[v - 1][v] = 1;
            g->matrix[v - n][v] = 1;
            g->matrix[v + n][v] = 1;
        }
    }

    /* the last column */
    for (i = 0; i < m - 1; i++) {
        g->matrix[i * n + n - 1][i * n + 2 * n - 1] = 1;
        g->matrix[i * n + 2 * n - 1][i * n + n - 1] = 1;
    }

    /* the last row */
    for (i = 0; i < n - 1; i++) {
        g->matrix[i + m * n - n][i + m * n - n + 1] = 1;
        g->matrix[i + m * n - n + 1][i + m * n - n] = 1;
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
        int j = rand() % (i + 1);
        SWAP(arr[i], arr[j]);
    }
}

static int *transform_init(int size)
{
    int i, *transform;
    transform = malloc(size * sizeof(*transform));
    for (i = 0; i < size; i++) {
        transform[i] = i;
    }
    return transform;
}

struct graph *graph_shuffle(const struct graph *g)
{
    int i, j;
    struct graph *h;
    int size, *transform;

    size = g->size;
    transform = transform_init(size);
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

static int graph_equals(const struct graph *g,
        const struct graph *h, int *transform)
{
    int i, j;
    for (i = 0; i < g->size; i++) {
        for (j = 0; j < g->size; j++) {
            counter++;
            if (g->matrix[i][j] != h->matrix[transform[i]][transform[j]]) {
                counter++;
                return 0;
            }
        }
    }
    counter++;
    return 1;
}

static int permute(const struct graph *g, const struct graph *h,
        int *transform, int l, int r)
{
    int i;

    counter++;
    if (l == r) { counter++;
        return graph_equals(g, h, transform);
    }
    for (i = l; i <= r; i++) {
        int res;

        SWAP(transform[l], transform[i]); counter += 3;
        res = permute(g, h, transform, l + 1, r); counter += 2;

        counter++;
        if (res) { counter++;
            return 1;
        }

        SWAP(transform[l], transform[i]); counter += 3;
    }
    counter++;
    return 0;
}

int graph_is_isomorphic(const struct graph *g, const struct graph *h)
{
    int *transform, size, res;

    counter++;
    if (h->size != g->size) { counter++;
        return 0;
    }
    size = g->size; counter++;

    transform = transform_init(size); counter += size;
    res = permute(g, h, transform, 0, size - 1); counter += 2;
    free(transform);
    return res;
}
