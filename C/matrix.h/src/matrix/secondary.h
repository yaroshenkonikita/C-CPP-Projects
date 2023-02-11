#include "../matrix.h"

void get_minor(matrix_t *A, matrix_t *minor, int skip_row, int skip_column);
void cpy_matrix(matrix_t *A, matrix_t *result);
int matrix_correct(matrix_t *matrix);
// double gauss_determinant(matrix_t *A /*, int flag*/);
double determinant_rek(matrix_t *A);
void algeb_dop(matrix_t *A);