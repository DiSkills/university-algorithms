#ifndef MATRIX_H
#define MATRIX_H

struct matrix {
    int **data;
    int size;
};

extern long long counter; /* Bad, very bad... I hate myself!!! */
/* https://www.youtube.com/watch?v=lIX3hecWFAY */

struct matrix *matrix_init(int size);
void matrix_fill(struct matrix *m);
void matrix_del(struct matrix *m);
void matrix_print(const struct matrix *m);

struct matrix *matrix_add(const struct matrix *a, const struct matrix *b);
struct matrix *matrix_sub(const struct matrix *a, const struct matrix *b);
struct matrix *matrix_block(const struct matrix *m,
        int row, int col, int size);
void matrix_set_block(struct matrix *m, const struct matrix *blck,
        int row, int col);
struct matrix *matrix_mul(const struct matrix *a, const struct matrix *b);

#endif
