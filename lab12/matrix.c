#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

struct matrix *matrix_init(int size)
{
    int i;
    struct matrix *m = malloc(sizeof(*m));

    m->size = size;
    m->data = malloc(sizeof(*m->data) * size);
    for (i = 0; i < size; i++) {
        m->data[i] = malloc(sizeof(*m->data[i]) * size);
    }
    return m;
}

void matrix_fill(struct matrix *m)
{
    int i, j;
    for (i = 0; i < m->size; i++) {
        for (j = 0; j < m->size; j++) {
            m->data[i][j] = rand() % 100;
        }
    }
}

void matrix_del(struct matrix *m)
{
    int i;
    for (i = 0; i < m->size; i++) {
        free(m->data[i]);
    }
    free(m->data);
    m->data = NULL;
    m->size = 0;
}

void matrix_print(const struct matrix *m)
{
    int i, j;
    for (i = 0; i < m->size; i++) {
        for (j = 0; j < m->size; j++) {
            printf(" %5d", m->data[i][j]);
        }
        printf("\n");
    }
}

#if 0
static matrix_t matrix_add(const matrix_t a, const matrix_t b, int size)
{
    int i, j;

    matrix_t c = matrix_init(size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

static matrix_t matrix_sub(const matrix_t a, const matrix_t b, int size)
{
    int i, j;

    matrix_t c = matrix_init(size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

static matrix_t matrix_block(const matrix_t m, int size,
        int row, int col, int s)
{
    int i, j;
    for (i = row; i < row + s; i++) {
        for (j = col; j < col + s; j++) {
        }
    }
}
#endif
