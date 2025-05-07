#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

long long counter = 0;

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

struct matrix *matrix_add(const struct matrix *a, const struct matrix *b)
{
    int i, j;
    struct matrix *c = matrix_init(a->size);

    for (i = 0; i < a->size; i++) {
        for (j = 0; j < a->size; j++) {
            c->data[i][j] = a->data[i][j] + b->data[i][j];
            counter += 2;
        }
    }
    return c;
}

struct matrix *matrix_sub(const struct matrix *a, const struct matrix *b)
{
    int i, j;
    struct matrix *c = matrix_init(a->size);

    for (i = 0; i < a->size; i++) {
        for (j = 0; j < a->size; j++) {
            c->data[i][j] = a->data[i][j] - b->data[i][j];
            counter += 2;
        }
    }
    return c;
}

struct matrix *matrix_block(const struct matrix *m,
        int row, int col, int size)
{
    int i, j;
    struct matrix *blck = matrix_init(size);

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            blck->data[i][j] = m->data[row + i][col + j];
        }
    }
    return blck;
}

void matrix_set_block(struct matrix *m, const struct matrix *blck,
        int row, int col)
{
    int i, j;
    for (i = 0; i < blck->size; i++) {
        for (j = 0; j < blck->size; j++) {
             m->data[row + i][col + j] = blck->data[i][j];
        }
    }
}
