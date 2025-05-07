#include <stdlib.h>

#include "matrix.h"

#define BLOCKS_INIT(M)                                                       \
    do {                                                                     \
        M##11 = matrix_block(M, 0, 0, size);                                 \
        M##12 = matrix_block(M, 0, size, size);                              \
        M##21 = matrix_block(M, size, 0, size);                              \
        M##22 = matrix_block(M, size, size, size);                           \
    } while (0)

#define BLOCKS_DEL(M)                                                        \
    do {                                                                     \
        matrix_del(M##11);                                                   \
        matrix_del(M##12);                                                   \
        matrix_del(M##21);                                                   \
        matrix_del(M##22);                                                   \
        free(M##11);                                                         \
        free(M##12);                                                         \
        free(M##21);                                                         \
        free(M##22);                                                         \
    } while (0)

struct matrix *matrix_mul(const struct matrix *a, const struct matrix *b)
{
    int size = a->size / 2;
    struct matrix *c,
                  *a11, *a12, *a21, *a22,
                  *b11, *b12, *b21, *b22;
    BLOCKS_INIT(a);
    BLOCKS_INIT(b);

    /* --- */
    matrix_print(b11);
    matrix_print(b12);
    matrix_print(b21);
    matrix_print(b22);
    /* --- */

    BLOCKS_DEL(a);
    BLOCKS_DEL(b);
    return c;
}
