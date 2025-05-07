#ifndef MATRIX_H
#define MATRIX_H

struct matrix {
    int **data;
    int size;
};

struct matrix *matrix_init(int size);
void matrix_fill(struct matrix *m);
void matrix_del(struct matrix *m);
void matrix_print(const struct matrix *m);

struct matrix *matrix_add(const struct matrix *a, const struct matrix *b);
struct matrix *matrix_sub(const struct matrix *a, const struct matrix *b);
struct matrix *matrix_block(const struct matrix *m,
        int row, int col, int size);
struct matrix *matrix_mul(const struct matrix *a, const struct matrix *b);

#endif
