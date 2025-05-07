#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"

int main(int argc, char **argv)
{
    int size;
    struct matrix *a;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    srand(time(NULL));

    size = atoi(argv[1]);

    a = matrix_init(size);
    matrix_fill(a);

    matrix_print(a);

    matrix_del(a);
    free(a);
    return 0;
}
