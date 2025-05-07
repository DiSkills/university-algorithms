#ifndef MATRIX_H
#define MATRIX_H

typedef int **matrix_t;

matrix_t matrix_init(int size);
void matrix_fill(matrix_t matrix, int size);
void matrix_del(matrix_t matrix, int size);
void matrix_print(const matrix_t matrix, int size);

#endif
