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

#define BLOCK_DEL(T)                                                         \
    do {                                                                     \
        matrix_del(T);                                                       \
        free(T);                                                             \
    } while(0)

#define BLOCKS_TMP_DEL(T1, T2)                                               \
    do {                                                                     \
        BLOCK_DEL(T1);                                                   \
        BLOCK_DEL(T2);                                                   \
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
        BLOCK_DEL(t);                                                        \
    } while(0)

#define M5                                                                   \
    do {                                                                     \
        struct matrix *t;                                                    \
        t = matrix_sub(b12, b22);                                            \
        m5 = matrix_mul(a11, t);                                             \
        BLOCK_DEL(t);                                                        \
    } while(0)

#define M6                                                                   \
    do {                                                                     \
        struct matrix *t;                                                    \
        t = matrix_sub(b21, b11);                                            \
        m6 = matrix_mul(a22, t);                                             \
        BLOCK_DEL(t);                                                        \
    } while(0)

#define M7                                                                   \
    do {                                                                     \
        struct matrix *t;                                                    \
        t = matrix_add(a21, a22);                                            \
        m7 = matrix_mul(t, b11);                                             \
        BLOCK_DEL(t);                                                        \
    } while(0)

#define M_DEL                                                                \
    do {                                                                     \
        BLOCK_DEL(m1);                                                       \
        BLOCK_DEL(m2);                                                       \
        BLOCK_DEL(m3);                                                       \
        BLOCK_DEL(m4);                                                       \
        BLOCK_DEL(m5);                                                       \
        BLOCK_DEL(m6);                                                       \
        BLOCK_DEL(m7);                                                       \
    } while(0)

#define C11(C)                                                               \
    do {                                                                     \
        struct matrix *t1, *t2, *t3;                                         \
        t1 = matrix_add(m1, m2);                                             \
        t2 = matrix_sub(t1, m4);                                             \
        t3 = matrix_add(t2, m6);                                             \
        matrix_set_block(C, t3, 0, 0);                                       \
        BLOCKS_TMP_DEL(t1, t2);                                              \
        BLOCK_DEL(t3);                                                       \
    } while(0)

#define C12(C)                                                               \
    do {                                                                     \
        struct matrix *t;                                                    \
        t = matrix_add(m4, m5);                                              \
        matrix_set_block(C, t, 0, t->size);                                  \
        BLOCK_DEL(t);                                                        \
    } while(0)

#define C21(C)                                                               \
    do {                                                                     \
        struct matrix *t;                                                    \
        t = matrix_add(m6, m7);                                              \
        matrix_set_block(C, t, t->size, 0);                                  \
        BLOCK_DEL(t);                                                        \
    } while(0)

#define C22(C)                                                               \
    do {                                                                     \
        struct matrix *t1, *t2, *t3;                                         \
        t1 = matrix_sub(m2, m3);                                             \
        t2 = matrix_add(t1, m5);                                             \
        t3 = matrix_sub(t2, m7);                                             \
        matrix_set_block(C, t3, t3->size, t3->size);                         \
        BLOCKS_TMP_DEL(t1, t2);                                              \
        BLOCK_DEL(t3);                                                       \
    } while(0)

struct matrix *matrix_mul(const struct matrix *a, const struct matrix *b)
{
    int size = a->size / 2;
    struct matrix *c,
                  *m1, *m2, *m3, *m4, *m5, *m6, *m7,
                  *a11, *a12, *a21, *a22,
                  *b11, *b12, *b21, *b22;
    
    if (a->size == 1) {
        c = matrix_init(1);
        c->data[0][0] = a->data[0][0] * b->data[0][0];
        return c;
    }

    BLOCKS_INIT(a);
    BLOCKS_INIT(b);

    M1; M2; M3; M4; M5; M6; M7;
    c = matrix_init(a->size);
    C11(c); C12(c); C21(c); C22(c);

    M_DEL;
    BLOCKS_DEL(a);
    BLOCKS_DEL(b);
    return c;
}
