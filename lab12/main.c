#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"

int main(int argc, char **argv)
{
    int size;
    struct matrix *a, *b, *c;

    if (argc != 2) {
        fprintf(stderr, "Expected: %s <size>\n", argv[0]);
        return 1;
    }
    srand(time(NULL));

    size = atoi(argv[1]);

    a = matrix_init(size);
    matrix_fill(a);
    b = matrix_init(size);
    matrix_fill(b);

    c = matrix_mul(a, b);
    matrix_del(c);
    free(c);

    printf("%lld\n", counter);

    matrix_del(a);
    free(a);
    matrix_del(b);
    free(b);
    return 0;
}
