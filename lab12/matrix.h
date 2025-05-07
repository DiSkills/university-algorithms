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

#endif
