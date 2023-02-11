#include "secondary.h"

int calc_complements(matrix_t *A, matrix_t *result) {
  int res = matrix_correct(A);
  if (res || !result) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != A->rows || A->columns < 2) {
    res = WRONG_MATRIX;
  } else {
    res = create_matrix(A->rows, A->columns, result);
    if (!res) {
      for (int i = 0; i < A->rows && !res; i++) {
        for (int j = 0; j < A->columns && !res; j++) {
          matrix_t buff_dec = {0};
          res = create_matrix(A->rows - 1, A->columns - 1, &buff_dec);
          if (!res) {
            get_minor(A, &buff_dec, i, j);
            double buff_dbl = 0;
            determinant(&buff_dec, &buff_dbl);
            result->matrix[i][j] = buff_dbl;
            remove_matrix(&buff_dec);
          }
        }
      }
      if (res) {
        remove_matrix(result);
      } else {
        algeb_dop(result);
      }
    }
  }
  return res;
}
