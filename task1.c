#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int **matrix_t;

static matrix_t matrix_init(int size)
{
    int i, j;

    matrix_t matrix = malloc(sizeof(*matrix) * size);
    for (i = 0; i < size; i++) {
        matrix[i] = malloc(sizeof(*matrix[i]) * size);

        for (j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}

static void matrix_del(matrix_t matrix, int size)
{
    int i;

    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
}

#ifdef PRINT
static void matrix_print(matrix_t matrix, int size)
{
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf(" %5d", matrix[i][j]);
        }
        printf("\n");
    }
}
#endif

static int matrix_multiplication_cost(matrix_t a, matrix_t b, int size)
{
    int i, j, k;
    int counter = 0;

    matrix_t c = malloc(sizeof(*c) * size);
    for (i = 0; i < size; i++) {
        c[i] = malloc(sizeof(*c[i]) * size);

        for (j = 0; j < size; j++) {
            c[i][j] = 0; counter++;

            for (k = 0; k < size; k++) {
                c[i][j] += a[i][k] * b[k][j]; counter += 3;
            }
        }
    }

#ifdef PRINT
    matrix_print(c, size);
#endif

    matrix_del(c, size); free(c);
    return counter;
}

int main(int argc, char **argv)
{
    int size, cost;
    matrix_t a, b;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    size = atoi(argv[1]);

    srand(time(NULL));
    a = matrix_init(size);
    b = matrix_init(size);

#ifdef PRINT
    matrix_print(a, size);
    printf("\n");
    matrix_print(b, size);
    printf("\n");
#endif

    cost = matrix_multiplication_cost(a, b, size);
#ifndef PRINT
    printf("%d\n", cost);
#endif

    matrix_del(a, size); free(a);
    matrix_del(b, size); free(b);
    return 0;
}
