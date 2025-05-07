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

#define BLOCK_TMP_DEL(T)                                                     \
    do {                                                                     \
        matrix_del(T);                                                       \
        free(T);                                                             \
    } while(0)

#define BLOCKS_TMP_DEL(T1, T2)                                               \
    do {                                                                     \
        BLOCK_TMP_DEL(T1);                                                   \
        BLOCK_TMP_DEL(T2);                                                   \
    } while (0)

#define M1                                                                   \
    do {                                                                     \
        struct matrix *t1, *t2;                                              \
        t1 = matrix_sub(a12, a22);                                           \
        t2 = matrix_add(b21, b22);                                           \
        m1 = matrix_mul(t1, t2);                                             \
        BLOCKS_TMP_DEL(t1, t2);                                              \
    } while(0)

#define M2                                                                   \
    do {                                                                     \
        struct matrix *t1, *t2;                                              \
        t1 = matrix_add(a11, a22);                                           \
        t2 = matrix_add(b11, b22);                                           \
        m2 = matrix_mul(t1, t2);                                             \
        BLOCKS_TMP_DEL(t1, t2);                                              \
    } while(0)

#define M3                                                                   \
    do {                                                                     \
        struct matrix *t1, *t2;                                              \
        t1 = matrix_sub(a11, a21);                                           \
        t2 = matrix_add(b11, b12);                                           \
        m3 = matrix_mul(t1, t2);                                             \
        BLOCKS_TMP_DEL(t1, t2);                                              \
    } while(0)

#define M4                                                                   \
    do {                                                                     \
        struct matrix *t;                                                    \
        t = matrix_add(a11, a12);                                            \
        m4 = matrix_mul(t, b22);                                             \
        BLOCK_TMP_DEL(t);                                                    \
    } while(0)

#define M5                                                                   \
    do {                                                                     \
        struct matrix *t;                                                    \
        t = matrix_sub(b12, b22);                                            \
        m5 = matrix_mul(a11, t);                                             \
        BLOCK_TMP_DEL(t);                                                    \
    } while(0)

#define M6                                                                   \
    do {                                                                     \
        struct matrix *t;                                                    \
        t = matrix_sub(b21, b11);                                            \
        m6 = matrix_mul(a22, t);                                             \
        BLOCK_TMP_DEL(t);                                                    \
    } while(0)

#define M7                                                                   \
    do {                                                                     \
        struct matrix *t;                                                    \
        t = matrix_add(a21, a22);                                            \
        m7 = matrix_mul(t, b11);                                             \
        BLOCK_TMP_DEL(t);                                                    \
    } while(0)

struct matrix *matrix_mul(const struct matrix *a, const struct matrix *b)
{
    int size = a->size / 2;
    struct matrix *c, *m1, *m2, *m3, *m4, *m5, *m6, *m7,
                  *a11, *a12, *a21, *a22,
                  *b11, *b12, *b21, *b22;
    BLOCKS_INIT(a);
    BLOCKS_INIT(b);

    /* --- */
    M1; M2; M3; M4; M5; M6; M7;
    /* --- */

    BLOCKS_DEL(a);
    BLOCKS_DEL(b);
    return c;
}
