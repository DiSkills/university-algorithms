#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

matrix_t matrix_init(int size)
{
    int i;

    matrix_t matrix = malloc(sizeof(*matrix) * size);
    for (i = 0; i < size; i++) {
        matrix[i] = malloc(sizeof(*matrix[i]) * size);
    }
    return matrix;
}

void matrix_fill(matrix_t matrix, int size)
{
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void matrix_del(matrix_t matrix, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
}

void matrix_print(const matrix_t matrix, int size)
{
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf(" %5d", matrix[i][j]);
        }
        printf("\n");
    }
}

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
