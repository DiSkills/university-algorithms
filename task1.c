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

static matrix_t matrix_multiply(matrix_t a, matrix_t b, int size)
{
    int i, j, k;

    matrix_t c = malloc(sizeof(*c) * size);
    for (i = 0; i < size; i++) {
        c[i] = malloc(sizeof(*c[i]) * size);

        for (j = 0; j < size; j++) {
            c[i][j] = 0;
            for (k = 0; k < size; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

int main(int argc, char **argv)
{
    int size;
    matrix_t a, b, c;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    size = atoi(argv[1]);

    srand(time(NULL));
    a = matrix_init(size);
    b = matrix_init(size);

    matrix_print(a, size);
    printf("\n");
    matrix_print(b, size);
    printf("\n");

    c = matrix_multiply(a, b, size);
    matrix_print(c, size);

    matrix_del(a, size);
    free(a);
    matrix_del(b, size);
    free(b);
    matrix_del(c, size);
    free(c);
    return 0;
}
