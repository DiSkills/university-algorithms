#include <stdio.h>
#include <stdlib.h>

typedef int **matrix_t;

static matrix_t matrix_init(int size)
{
    int i, j;

    matrix_t matrix = malloc(sizeof(*matrix) * size);
    for (i = 0; i < size; i++) {
        matrix[i] = malloc(sizeof(*matrix[i]) * size);

        for (j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
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

static void matrix_print(const matrix_t matrix, int size)
{
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf(" %5d", matrix[i][j]);
        }
        printf("\n");
    }
}

static int graph_is_simple_cycle(const matrix_t matrix, int size)
{
    int i, j, count, vertex;
    for (i = 0; i < size; i++) {
        int sum[2] = { 0, 0 };
        for (j = 0; j < size; j++) {
            sum[0] += matrix[i][j];
            sum[1] += matrix[j][i];
        }
        if (sum[0] != 1 || sum[1] != 1) {
            return 0;
        }
    }

    vertex = 0;
    count = 0;
    do {
        for (j = 0; j < size; j++) {
            if (matrix[vertex][j]) {
                vertex = j;
                count++;
                break;
            }
        }
    } while (vertex != 0);
    return count == size ? 1 : 0;
}

int main(int argc, char **argv)
{
    int n, is_simple;
    matrix_t matrix;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);

    matrix = matrix_init(n);
    matrix_print(matrix, n);
    is_simple = graph_is_simple_cycle(matrix, n);
    printf("%d\n", is_simple);
    matrix_del(matrix, n);
    return 0;
}
